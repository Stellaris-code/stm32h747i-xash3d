#include <iostream>

#include "libserialport/libserialport.h"

#include <SDL_net.h>

#define FOREACH_PACKET_TYPE(PACKET_TYPE) \
    PACKET_TYPE(NET_PACKET_TYPE_SYN) \
    PACKET_TYPE(NET_PACKET_TYPE_ACK) \
    PACKET_TYPE(NET_PACKET_TYPE_REJECTED) \
    PACKET_TYPE(NET_PACKET_TYPE_KEEPALIVE) \
    PACKET_TYPE(NET_PACKET_TYPE_WAITING_DATA) \
    PACKET_TYPE(NET_PACKET_TYPE_GAMESTART) \
    PACKET_TYPE(NET_PACKET_TYPE_GAMEDATA) \
    PACKET_TYPE(NET_PACKET_TYPE_GAMEDATA_ACK) \
    PACKET_TYPE(NET_PACKET_TYPE_DISCONNECT) \
    PACKET_TYPE(NET_PACKET_TYPE_DISCONNECT_ACK) \
    PACKET_TYPE(NET_PACKET_TYPE_RELIABLE_ACK) \
    PACKET_TYPE(NET_PACKET_TYPE_GAMEDATA_RESEND) \
    PACKET_TYPE(NET_PACKET_TYPE_CONSOLE_MESSAGE) \
    PACKET_TYPE(NET_PACKET_TYPE_QUERY) \
    PACKET_TYPE(NET_PACKET_TYPE_QUERY_RESPONSE) \
    PACKET_TYPE(NET_PACKET_TYPE_LAUNCH)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,


enum packet_type_enum {
    FOREACH_PACKET_TYPE(GENERATE_ENUM)
    PACKET_TYPE_COUNT
};

static const char *packet_type_strings[] = {
    FOREACH_PACKET_TYPE(GENERATE_STRING)
};

#define NET_RELIABLE_PACKET (1 << 15)

#define DEFAULT_PORT 2342

static int port = DEFAULT_PORT;

static UDPsocket udpsocket;
static UDPpacket *recvpacket;

void AddrToString(IPaddress* ip, char *buffer, int buffer_len)
{
    uint32_t host;
    uint16_t port;

    host = SDLNet_Read32(&ip->host);
    port = SDLNet_Read16(&ip->port);

    snprintf(buffer, buffer_len, "%i.%i.%i.%i:%i",
               (host >> 24) & 0xff, (host >> 16) & 0xff,
               (host >> 8) & 0xff, host & 0xff, port);
}

struct serial_com_packet_t
{
    uint32_t data_len;
    uint32_t data_checksum;
    uint32_t ip;
    uint32_t port;
    uint8_t data[];
} __attribute__((packed));

static void udp_init()
{
    SDLNet_Init();

    udpsocket = SDLNet_UDP_Open(0);

    if (udpsocket == NULL)
    {
        fprintf(stderr, "NET_SDL_InitClient: Unable to open a socket!");
    }

    recvpacket = SDLNet_AllocPacket(1500);
}

static void udp_send(IPaddress ip, uint8_t* data, size_t len)
{
    char buf[80];
    AddrToString(&ip, buf, 80);

    uint16_t type = SDLNet_Read16(data);
    type &= ~NET_RELIABLE_PACKET;

    const char* type_name = "UNKNOWN";
    if (type < PACKET_TYPE_COUNT)
        type_name = packet_type_strings[type];

    printf("sent %s %x bytes to %s\n", type_name, len, buf);

    UDPpacket sdl_packet;

    sdl_packet.channel = 0;
    sdl_packet.data = data;
    sdl_packet.len = len;
    sdl_packet.address = ip;


    if (!SDLNet_UDP_Send(udpsocket, -1, &sdl_packet))
    {
        fprintf(stderr, "NET_SDL_SendPacket: Error transmitting packet: %s",
                SDLNet_GetError());
    }
}

static bool udp_receive()
{
    int result;

    result = SDLNet_UDP_Recv(udpsocket, recvpacket);

    if (result < 0)
    {
        fprintf(stderr, "NET_SDL_RecvPacket: Error receiving packet: %s",
                SDLNet_GetError());
    }

    if (result == 0)
        return false;

    char buf[80];
    AddrToString(&recvpacket->address, buf, 80);

    uint16_t type = SDLNet_Read16(recvpacket->data);
    type &= ~NET_RELIABLE_PACKET;

    const char* type_name = "UNKNOWN";
    if (type < PACKET_TYPE_COUNT)
        type_name = packet_type_strings[type];

    printf("received %s %x bytes from %s\n", type_name, recvpacket->len, buf);

    return true;
}

uint8_t data_buffer[65536];

extern bool kbhit();

int main(int argc, char* argv[])
{
    struct sp_port *com_port;
    serial_com_packet_t* rcv_pckt = (serial_com_packet_t*)malloc(65536);

    const char* portname = "COM4";
    if (argc > 1)
        portname = argv[1];
    auto err=sp_get_port_by_name(portname,&com_port);

reset:

    if (err==SP_OK)
        err=sp_open(com_port,SP_MODE_READ_WRITE);
    if (err!=SP_OK)
    {
        fprintf(stderr,"Can't open port %s\n",argv[1]);
        exit(2);
    }

    sp_set_baudrate(com_port, 11520);
    //sp_set_flowcontrol(com_port, SP_FLOWCONTROL_RTSCTS);

    udp_init();

    printf("Ready to receive\n");

    while (1)
    {
        char c;
        if (sp_input_waiting(com_port))
        {
            sp_blocking_read(com_port, &c, 1, 100);
            if (c == '!')
            {
                uint32_t len;
                sp_blocking_read(com_port, &len, sizeof(len), 100);
                uint32_t checksum;
                sp_blocking_read(com_port, &checksum, sizeof(checksum), 100);
                uint32_t le_ip, le_port;
                IPaddress ip;
                sp_blocking_read(com_port, &le_ip, sizeof(le_ip), 100);
                SDLNet_Write32(le_ip, &ip.host);
                sp_blocking_read(com_port, &le_port, sizeof(le_port), 100);
                SDLNet_Write16(port, &ip.port);

                sp_blocking_read(com_port, data_buffer, len, 100);

                sp_blocking_read(com_port, &c, 1, 100);
                if (c != ';')
                {
                    fprintf(stderr, "Expected ';' as end of packet");
                }

                udp_send(ip, data_buffer, len);
            }
        }

        if (udp_receive())
        {
            c = '!';
            sp_blocking_write(com_port, &c, 1, 100);

            rcv_pckt->ip   = SDLNet_Read32(&recvpacket->address.host);
            rcv_pckt->port = SDLNet_Read16(&recvpacket->address.port);
            rcv_pckt->data_len = recvpacket->len;
            memcpy(rcv_pckt->data, recvpacket->data, recvpacket->len);

            sp_blocking_write(com_port, (const void*)rcv_pckt, recvpacket->len + sizeof(serial_com_packet_t), 100);

            c = ';';
            sp_blocking_write(com_port, &c, 1, 100);
        }
    }

    return 0;
}

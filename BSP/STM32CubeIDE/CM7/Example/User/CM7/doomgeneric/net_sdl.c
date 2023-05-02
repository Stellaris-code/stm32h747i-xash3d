//
// Copyright(C) 2005-2014 Simon Howard
// Copyright(C) 2021-2022 Graham Sanderson
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//     Networking module which uses SDL_net
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "doomtype.h"
#include "i_system.h"
#include "m_argv.h"
#include "m_misc.h"
#include "net_defs.h"
#include "net_io.h"
#include "net_packet.h"
#include "net_sdl.h"
#include "z_zone.h"

#include "usbd_cdc_if.h"

#if !NO_USE_NET

//
// NETWORKING
//

#define INADDR_BROADCAST    0xFFFFFFFF

#define DEFAULT_PORT 2342

static boolean initted = false;
static int port = DEFAULT_PORT;

struct serial_com_packet_t
{
    uint32_t data_len;
    uint32_t data_checksum;
    uint32_t ip;
    uint32_t port;
    uint8_t data[];
} __attribute__((packed));

typedef struct {
    uint32_t host;            /* 32-bit IPv4 host address */
    uint16_t port;            /* 16-bit protocol port */
} IPaddress;


typedef struct
{
    net_addr_t net_addr;
    IPaddress sdl_addr;
} addrpair_t;

static addrpair_t **addr_table;
static int addr_table_size = -1;

// Initializes the address table

static void NET_SDL_InitAddrTable(void)
{
    addr_table_size = 16;

    addr_table = Z_Malloc(sizeof(addrpair_t *) * addr_table_size,
                          PU_STATIC, 0);
    memset(addr_table, 0, sizeof(addrpair_t *) * addr_table_size);
}

static boolean AddressesEqual(IPaddress *a, IPaddress *b)
{
    return a->host == b->host
        && a->port == b->port;
}

// Finds an address by searching the table.  If the address is not found,
// it is added to the table.

static net_addr_t *NET_SDL_FindAddress(IPaddress *addr)
{
    addrpair_t *new_entry;
    int empty_entry = -1;
    int i;

    if (addr_table_size < 0)
    {
        NET_SDL_InitAddrTable();
    }

    for (i=0; i<addr_table_size; ++i)
    {
        if (addr_table[i] != NULL
         && AddressesEqual(addr, &addr_table[i]->sdl_addr))
        {
            return &addr_table[i]->net_addr;
        }

        if (empty_entry < 0 && addr_table[i] == NULL)
            empty_entry = i;
    }

    // Was not found in list.  We need to add it.

    // Is there any space in the table? If not, increase the table size

    if (empty_entry < 0)
    {
        addrpair_t **new_addr_table;
        int new_addr_table_size;

        // after reallocing, we will add this in as the first entry
        // in the new block of memory

        empty_entry = addr_table_size;

        // allocate a new array twice the size, init to 0 and copy
        // the existing table in.  replace the old table.

        new_addr_table_size = addr_table_size * 2;
        new_addr_table = Z_Malloc(sizeof(addrpair_t *) * new_addr_table_size,
                                  PU_STATIC, 0);
        memset(new_addr_table, 0, sizeof(addrpair_t *) * new_addr_table_size);
        memcpy(new_addr_table, addr_table,
               sizeof(addrpair_t *) * addr_table_size);
        Z_Free(addr_table);
        addr_table = new_addr_table;
        addr_table_size = new_addr_table_size;
    }

    // Add a new entry

    new_entry = Z_Malloc(sizeof(addrpair_t), PU_STATIC, 0);

    new_entry->sdl_addr = *addr;
    new_entry->net_addr.handle = &new_entry->sdl_addr;
    new_entry->net_addr.module = &net_stm_module;

    addr_table[empty_entry] = new_entry;

    return &new_entry->net_addr;
}

static void NET_STM_FreeAddress(net_addr_t *addr)
{
    int i;

    for (i=0; i<addr_table_size; ++i)
    {
        if (addr == &addr_table[i]->net_addr)
        {
            Z_Free(addr_table[i]);
            addr_table[i] = NULL;
            return;
        }
    }

    I_Error("NET_SDL_FreeAddress: Attempted to remove an unused address!");
}

static boolean NET_STM_InitClient(void)
{
	return true;
}

static boolean NET_STM_InitServer(void)
{
	return false;
}

static uint8_t data_buffer[65536];

static void NET_STM_SendPacket(net_addr_t *addr, net_packet_t *packet)
{
	IPaddress ip = {0};

    if (addr == &net_broadcast_addr)
    {
        ip.host = INADDR_BROADCAST;
        ip.port = port;
    }
    else
    {
    	ip = *((IPaddress *) addr->handle);
    }

    struct serial_com_packet_t com_packt;
    com_packt.ip = ip.host;
    com_packt.port = ip.port;
    com_packt.data_len = packet->len;
    com_packt.data_checksum = 0;

    char c = '!';
    vcp_send(&c, 1);

    vcp_send(&com_packt, sizeof(com_packt));
    vcp_send(packet->data, packet->len);

    c = ';';
    vcp_send(&c, 1);

    vcp_service();

	return;
}

static boolean NET_STM_RecvPacket(net_addr_t **addr, net_packet_t **packet)
{
	char c;
	int read = vcp_recv(&c, 1);
	if (read == 0)
		return false;

	assert(c == '!');

    uint32_t len;
    vcp_recv_blocking(&len, sizeof(len));
    uint32_t checksum;
    vcp_recv_blocking(&checksum, sizeof(checksum));
    uint32_t ip;
    vcp_recv_blocking(&ip, sizeof(ip));
    uint32_t port;
    vcp_recv_blocking(&port, sizeof(port));

    vcp_recv_blocking(data_buffer, len);

    vcp_recv_blocking(&c, 1);
    assert(c == ';');

    *packet = NET_NewPacket(len);
    memcpy((*packet)->data, data_buffer, len);
    (*packet)->len = len;


    IPaddress full_ip;
    full_ip.host = ip;
    full_ip.port = port;
    *addr = NET_SDL_FindAddress(&full_ip);

	return true;
}

void NET_STM_AddrToString(net_addr_t *addr, char *buffer, int buffer_len)
{
     uint32_t host = (uint32_t)addr->handle;

    M_snprintf(buffer, buffer_len, "%i.%i.%i.%i",
               (host >> 24) & 0xff, (host >> 16) & 0xff,
               (host >> 8) & 0xff, host & 0xff);
}

net_addr_t *NET_STM_ResolveAddress(const char *address)
{
	assert(false);
	return 0;
}

// Complete module

net_module_t net_stm_module =
{
    NET_STM_InitClient,
    NET_STM_InitServer,
    NET_STM_SendPacket,
    NET_STM_RecvPacket,
    NET_STM_AddrToString,
    NET_STM_FreeAddress,
    NET_STM_ResolveAddress,
};

#endif

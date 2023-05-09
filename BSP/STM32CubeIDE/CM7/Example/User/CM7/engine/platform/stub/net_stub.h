/*
net_stub.h - stub BSD sockets
Copyright (C) 2020 mittorn

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#ifndef NET_STUB_H
#define NET_STUB_H

#include <stdint.h>

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define SOCKET int
typedef int WSAsize_t;
//typedef int socklen_t;
struct in_addr {unsigned long s_addr;};
struct sockaddr_in{ short sin_family;unsigned short sin_port;struct in_addr sin_addr;};
struct sockaddr {short sa_family;int stub[32];};
struct hostent {int h_addr_list[1];};
//#ifndef __MINGW32__
//struct timeval {long tv_sec;long tv_usec;};
//#endif

struct in6_addr {
	unsigned char   s6_addr[16];   /* adresse IPv6 */
};

struct sockaddr_in6 {
	uint16_t        sin6_family;   /* AF_INET6 */
	uint16_t        sin6_port;     /* num�ro de port */
	uint32_t        sin6_flowinfo; /* information de flux IPv6 */
	struct in6_addr sin6_addr;     /* adresse IPv6 */
	uint32_t        sin6_scope_id; /* Scope ID (nouveaut� 2.4) */
};

#define AF_UNSPEC       0               // unspecified
#define AF_UNIX         1               // local to host (pipes, portals)
#define AF_INET         2               // internetwork: UDP, TCP, etc.
#define AF_IMPLINK      3               // arpanet imp addresses
#define AF_PUP          4               // pup protocols: e.g. BSP
#define AF_CHAOS        5               // mit CHAOS protocols
#define AF_NS           6               // XEROX NS protocols
#define AF_IPX          AF_NS           // IPX protocols: IPX, SPX, etc.
#define AF_ISO          7               // ISO protocols
#define AF_OSI          AF_ISO          // OSI is ISO
#define AF_ECMA         8               // european computer manufacturers
#define AF_DATAKIT      9               // datakit protocols
#define AF_CCITT        10              // CCITT protocols, X.25 etc
#define AF_SNA          11              // IBM SNA
#define AF_DECnet       12              // DECnet
#define AF_DLI          13              // Direct data link interface
#define AF_LAT          14              // LAT
#define AF_HYLINK       15              // NSC Hyperchannel
#define AF_APPLETALK    16              // AppleTalk
#define AF_NETBIOS      17              // NetBios-style addresses
#define AF_VOICEVIEW    18              // VoiceView
#define AF_FIREFOX      19              // Protocols from Firefox
#define AF_UNKNOWN1     20              // Somebody is using this!
#define AF_BAN          21              // Banyan
#define AF_ATM          22              // Native ATM Services
#define AF_INET6        23              // Internetwork Version 6
#define AF_CLUSTER      24              // Microsoft Wolfpack
#define AF_12844        25              // IEEE 1284.4 WG AF
#define AF_IRDA         26              // IrDA
#define AF_NETDES       28              // Network Designers OSI & gateway
#define AF_MAX          29


#define PF_UNSPEC       AF_UNSPEC
#define PF_UNIX         AF_UNIX
#define PF_INET         AF_INET
#define PF_IMPLINK      AF_IMPLINK
#define PF_PUP          AF_PUP
#define PF_CHAOS        AF_CHAOS
#define PF_NS           AF_NS
#define PF_IPX          AF_IPX
#define PF_ISO          AF_ISO
#define PF_OSI          AF_OSI
#define PF_ECMA         AF_ECMA
#define PF_DATAKIT      AF_DATAKIT
#define PF_CCITT        AF_CCITT
#define PF_SNA          AF_SNA
#define PF_DECnet       AF_DECnet
#define PF_DLI          AF_DLI
#define PF_LAT          AF_LAT
#define PF_HYLINK       AF_HYLINK
#define PF_APPLETALK    AF_APPLETALK
#define PF_VOICEVIEW    AF_VOICEVIEW
#define PF_FIREFOX      AF_FIREFOX
#define PF_UNKNOWN1     AF_UNKNOWN1
#define PF_BAN          AF_BAN
#define PF_ATM          AF_ATM
#define PF_INET6        AF_INET6
#define PF_MAX          AF_MAX

#define INADDR_BROADCAST 0
#define INADDR_ANY 0
//! Network to host conversion for a word.
#define ntohs(n) ( (((n) & 0xFF00) >> 8) | (((n) & 0x00FF) << 8) )
//! Host to network conversion for a word.
#define htons(n) ( (((n) & 0xFF00) >> 8) | (((n) & 0x00FF) << 8) )
//! Network to host conversion for a double word.
#define ntohl(n) ( (((n) & 0xFF000000) >> 24) | (((n) & 0x00FF0000) >> 8) \
	 | (((n) & 0x0000FF00) << 8) | (((n) & 0x000000FF) << 24) )
//! Host to network conversion for a double word.
#define htonl(n) ( (((n) & 0xFF000000) >> 24) | (((n) & 0x00FF0000) >> 8) \
	 | (((n) & 0x0000FF00) << 8) | (((n) & 0x000000FF) << 24) )

#define gethostbyname(...) NULL
#define inet_addr(...) (-1)
#define recvfrom(...) (-1)
#define sendto(...) (-1)
#define socket(...) (-1)
#define ioctlsocket(...) (-1)
#define setsockopt(...) (-1)
#define bind(...) (-1)
#define gethostname(...) (-1)
#define getsockname(...) (-1)
#define connect(...) (-1)
#define send(...) (-1)
#define recv(...) (-1)
#define bind(...) (-1)
#define closesocket(...) (-1)
#define select(...) (-1)

#define WSAGetLastError() (22) //ENETDOWN
#define WSAEINTR           1 //EINTR
#define WSAEBADF           2 //EBADF
#define WSAEACCES          3 //EACCES
#define WSAEFAULT          4 //EFAULT
#define WSAEINVAL          5 //EINVAL
#define WSAEMFILE          6 //EMFILE
#define WSAEWOULDBLOCK     7 //EWOULDBLOCK
#define WSAEINPROGRESS     8 //EINPROGRESS
#define WSAEALREADY        9 //EALREADY
#define WSAENOTSOCK        10 //ENOTSOCK
#define WSAEDESTADDRREQ    11 //EDESTADDRREQ
#define WSAEMSGSIZE        12 //EMSGSIZE
#define WSAEPROTOTYPE      13 //EPROTOTYPE
#define WSAENOPROTOOPT     14 //ENOPROTOOPT
#define WSAEPROTONOSUPPORT 15 //EPROTONOSUPPORT
#define WSAESOCKTNOSUPPORT 16 //ESOCKTNOSUPPORT
#define WSAEOPNOTSUPP      17 //EOPNOTSUPP
#define WSAEPFNOSUPPORT    18 //EPFNOSUPPORT
#define WSAEAFNOSUPPORT    19 //EAFNOSUPPORT
#define WSAEADDRINUSE      20 //EADDRINUSE
#define WSAEADDRNOTAVAIL   21 //EADDRNOTAVAIL
#define WSAENETDOWN        22 //ENETDOWN
#define WSAENETUNREACH     23 //ENETUNREACH
#define WSAENETRESET       24 //ENETRESET
#define WSAECONNABORTED    25 //ECONNABORTED
#define WSAECONNRESET      26 //ECONNRESET
#define WSAENOBUFS         27 //ENOBUFS
#define WSAEISCONN         28 //EISCONN
#define WSAENOTCONN        29 //ENOTCONN
#define WSAESHUTDOWN       30 //ESHUTDOWN
#define WSAETOOMANYREFS    31 //ETOOMANYREFS
#define WSAETIMEDOUT       32 //ETIMEDOUT
#define WSAECONNREFUSED    33 //ECONNREFUSED
#define WSAELOOP           34 //ELOOP
#define WSAENAMETOOLONG    35 //ENAMETOOLONG
#define WSAEHOSTDOWN       36 //EHOSTDOWN


typedef uint32_t socklen_t;
typedef unsigned short ADDRESS_FAMILY;

typedef struct sockaddr_storage {
	ADDRESS_FAMILY ss_family;      // address family

    uint64_t __ss_align;            // Field to force desired structure
};

#endif // NET_STUB_H

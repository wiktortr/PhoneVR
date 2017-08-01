#ifndef _NET
#define _NET

// -------------------------------------------------------------------------------------------------------------------------- //

//Variable types
#if defined(_MSC_VER) && _MSC_VER < 1600
typedef   signed char    net_int8;
typedef unsigned char    net_uint8;
typedef   signed short   net_int16;
typedef unsigned short   net_uint16;
typedef   signed int     net_int32;
typedef unsigned int     net_uint32;
typedef   signed __int64 net_int64;
typedef unsigned __int64 net_uint64;
#else
#include <stdint.h>
typedef int8_t           net_int8;
typedef uint8_t          net_uint8;
typedef int16_t          net_int16;
typedef uint16_t         net_uint16;
typedef int32_t          net_int32;
typedef uint32_t         net_uint32;
typedef int64_t          net_int64;
typedef uint64_t         net_uint64;
#endif
typedef net_uint8		 net_byte;

// -------------------------------------------------------------------------------------------------------------------------- //


//Includes
#if defined(_WIN32) || defined(_WIN64)


#pragma comment(lib,"WS2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>


//Defines
#define NET_INVALID_SOCKET INVALID_SOCKET
#define NET_PROTO_IPV4 IPPROTO_IPV4
#define NET_PROTO_IPV6 IPPROTO_IPV6
#define NET_PROTO_TCP IPPROTO_TCP
#define NET_PROTO_UDP IPPROTO_UDP

#define NetSocketInit(protocol) socket(AF_INET, SOCK_STREAM, protocol)
#define NetBind(socket, socket_addr) bind(socket, (SOCKADDR*)&socket_addr, sizeof(socket_addr))
#define NetListen(socket) listen(socket, 1)
#define NetConnect(socket, socketAddr) connect(socket, (SOCKADDR*)&socketAddr, sizeof(socketAddr))
#define NetAccept(socket) accept(socket, NULL, NULL)
#define NetWrite(socket, data, data_size) send(socket, data, data_size, 0)
#define NetRead(socket, data, size) recv(socket, data, size, 0)
#define NetSocketClose(socket) closesocket(socket)



//Variables type
typedef SOCKET NetSocket;
typedef sockaddr_in NetSocketAddr;


//Functions
NetSocketAddr& NetInitSocketAddr(const char* ip, net_uint16 port);
NetSocket NetAcceptGetClient(NetSocket socket, NetSocketAddr& client);
void NetGetSocketAddr(NetSocketAddr socket, const char*& ip, net_uint16& port);


#elif defined(__APPLE__)
#error Not supported

#elif defined(__linux__)
#error Not supported

#elif defined(__unix__)
#error Not supported

#else
#error Unknow copiler
#endif

// -------------------------------------------------------------------------------------------------------------------------- //

//Defines
#define NET_OK 0
#define NET_ERROR -1

// -------------------------------------------------------------------------------------------------------------------------- //

//Functions
int NetInit();
int NetDeInit();
int NetCheckError();
const char* NetGetErrorString();


#endif // !_NET

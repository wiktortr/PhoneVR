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

//Defines
#define NET_OK 0
#define NET_ERROR -1

// -------------------------------------------------------------------------------------------------------------------------- //

//Variables
extern int _net_machine_status = NET_ERROR;
extern int _net_machine_status_last_function = NET_ERROR;

// -------------------------------------------------------------------------------------------------------------------------- //

//Functions
int NetInit();
int NetDeInit();
int NetCheckError();
const char* NetGetLocalIP();


// -------------------------------------------------------------------------------------------------------------------------- //

#if defined(_WIN32) || defined(_WIN64)


#pragma comment(lib,"WS2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <ws2tcpip.h>


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
NetSocket NetAcceptAndGetClient(NetSocket socket, NetSocketAddr& client);
void NetGetSocketAddr(NetSocketAddr socket, const char*& ip, net_uint16& port);


//Body function
int NetInit() {
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result == NO_ERROR) {
		_net_machine_status = NET_OK;
		return NET_OK;
	}
	else {
		_net_machine_status = NET_ERROR;
		_net_machine_status_last_function = WSAGetLastError();
		return NET_ERROR;
	}
}

int NetDeInit() {
	WSACleanup();
	return NET_OK;
}

const char* NetGetLocalIP() {
	char ac[80];
	if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR)
		return "";

	struct hostent *phe = gethostbyname(ac);
	if (phe == 0)
		return "";

	for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
		return inet_ntoa(addr);
	}
}

NetSocketAddr& NetInitSocketAddr(const char* ip, net_uint16 port) {
	NetSocketAddr service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = inet_addr(ip);
	service.sin_port = htons(port);
	return service;
}

NetSocket NetAcceptAndGetClient(NetSocket socket, NetSocketAddr& client) {
	int addrsize = sizeof(client);
	return accept(socket, (struct sockaddr*)&client, &addrsize);
}

void NetGetSocketAddr(NetSocketAddr socket, const char*& ip, net_uint16& port) {
	ip = inet_ntoa(socket.sin_addr);
	port = socket.sin_port;
}


#elif defined(__APPLE__)
#error Not supported

#elif defined(__linux__)
#error Not supported

#elif defined(__unix__)
#error Not supported

#else
#error Unknow copiler
#endif



//Boby function

int NetCheckError() {
	if (_net_machine_status != NET_OK)
		return _net_machine_status_last_function;
	else
		return NET_OK;
}



#endif // !_NET

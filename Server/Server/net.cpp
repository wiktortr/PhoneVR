#include "net.h"

// -------------------------------------------------------------------------------------------------------------------------- //

//Variables
int _net_machine_status = NET_ERROR;
int _net_machine_status_last_function = NET_ERROR;

// -------------------------------------------------------------------------------------------------------------------------- //


//Functions
NetSocketAddr& NetInitSocketAddr(const char * ip, net_uint16 port) {
	NetSocketAddr service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = inet_addr(ip);
	service.sin_port = htons(port);
	return service;
}

// -------------------------------------------------------------------------------------------------------------------------- //

NetSocket NetAcceptGetClient(NetSocket socket, NetSocketAddr & client){
	int addrsize = sizeof(client);
	return accept(socket, (struct sockaddr*)&client, &addrsize);
}

// -------------------------------------------------------------------------------------------------------------------------- //

void NetGetSocketAddr(NetSocketAddr socket, const char *& ip, net_uint16 & port){
	ip = inet_ntoa(socket.sin_addr);
	port = socket.sin_port;
}

// -------------------------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------------------------- //

int NetInit(){
#if defined(_WIN32) || defined(_WIN64)
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
#elif defined(__APPLE__)
#error Not supported
#elif defined(__linux__)
#error Not supported
#elif defined(__unix__)
#error Not supported
#else
	return NET_ERROR;
#endif

	return NET_ERROR;
}

int NetDeInit(){
#if defined(_WIN32) || defined(_WIN64)
	
#elif defined(__APPLE__)
#error Not supported
#elif defined(__linux__)
#error Not supported
#elif defined(__unix__)
#error Not supported
#else
	return NET_ERROR;
#endif
	return NET_OK;
}

// -------------------------------------------------------------------------------------------------------------------------- //

int NetCheckError(){
	if (_net_machine_status != NET_OK)
		return _net_machine_status_last_function;
	else
		return NET_OK;
	return NET_ERROR;
}

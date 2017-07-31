#include <iostream>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>

using namespace std;

#define CHUNK_SIZE 10

int main() {

	//create wsaData
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		cout << "Init Error" << endl;
	else
		cout << "Init ok" << endl;


	//Create main socket
	SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mainSocket == INVALID_SOCKET) {
		cout << "Error creating socket: " << WSAGetLastError() << endl;
		WSACleanup();
	}
	else
		cout << "Socket Created ok" << endl;


	//Create service
	sockaddr_in service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(27015);


	//Bind soocket and service
	if (bind(mainSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "Error bind socket" << endl;
		closesocket(mainSocket);
	}
	else
		cout << "Bind ok" << endl;


	//Listen
	if (listen(mainSocket, 1) == SOCKET_ERROR)
		cout << "Error listening on socket" << endl;
	else
		cout << "ok listen on socket" << endl;


	//waiting for client
	SOCKET acceptSocket = SOCKET_ERROR;
	cout << "Waiting for a client to connect..." << endl;

	while (acceptSocket == SOCKET_ERROR)
		acceptSocket = accept(mainSocket, NULL, NULL);

	cout << "Client connected" << endl;
	mainSocket = acceptSocket;


	////connect client to server
	//if (connect(mainSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
	//	cout << "Failed to connect" << endl;
	//	WSACleanup();
	//}
	//else
	//	cout << "connect ok" << endl;


	//Send data
	for (int i = 0; i < 1000; i++){
		string message = to_string(i) + ". Data send";
		if (send(mainSocket, message.c_str(), message.size(), 0) < 0)
			cout << "Error send data" << endl;
		else
			cout << "Send data" << endl;
	}
	


	//Recive data
	//string rev_data = "";
	//int size_recv, total_size = 0;
	//char chunk[CHUNK_SIZE];
	//while (1){
	//	memset(chunk, 0, CHUNK_SIZE);  //clear the variable
	//	if ((size_recv = recv(mainSocket, chunk, CHUNK_SIZE, 0)) < 0)
	//		break;
	//	else{
	//		total_size += size_recv;
	//		chunk[size_recv] = '\0';
	//		rev_data += chunk;
	//	}
	//}

	//cout << rev_data << endl;

	system("pause");
	return 0;
}

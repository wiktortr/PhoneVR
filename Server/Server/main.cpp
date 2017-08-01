#include <iostream>
#include <string>

#include "net.hpp"

using namespace std;

#define CHUNK_SIZE 10

int main() {

	if (NetInit() != NET_OK)
		cout << "Error init net" << endl;

	//Create main socket
	NetSocket mainSocket = NetSocketInit(NET_PROTO_TCP);
	if (mainSocket == NET_INVALID_SOCKET) {
		cout << "Error creating socket: " << WSAGetLastError() << endl;
		WSACleanup();
	}
	else
		cout << "Socket Created ok" << endl;


	//Create service
	NetSocketAddr service = NetInitSocketAddr("127.0.0.1", 27015);


	//Bind soocket and service
	if (NetBind(mainSocket, service) == NET_ERROR) {
		cout << "Error bind socket" << endl;
		closesocket(mainSocket);
	}
	else
		cout << "Bind ok" << endl;


	//Listen
	if (NetListen(mainSocket) == NET_ERROR)
		cout << "Error listening on socket" << endl;
	else
		cout << "ok listen on socket" << endl;


	//waiting for client
	SOCKET acceptSocket = NET_ERROR;
	cout << "Waiting for a client to connect..." << endl;

	while (acceptSocket == NET_ERROR) {
		acceptSocket = NetAccept(mainSocket);
	}


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
		int out = NetWrite(mainSocket, message.c_str(), message.size());
		cout << out << endl;
		//	cout << "Error send data" << endl;
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

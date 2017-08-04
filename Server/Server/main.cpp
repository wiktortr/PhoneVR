#include <iostream>
#include <string>

#include "net.hpp"

#pragma comment(lib,"opengl32.lib")
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <lz4.h>

//#include <thread>

using namespace std;

int width = 800;
int height = 600;

int main() {

	if (!glfwInit())
		cout << "Error init glfw" << endl;

	GLFWwindow* win = glfwCreateWindow(width, height, "PhoneVR server", NULL, NULL);
	glfwMakeContextCurrent(win);

	if (GLenum err = glewInit() != GLEW_OK)
		cout << "GLEW init error: " << (char*)glewGetErrorString(err) << endl;

	//Init net socket
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
	NetSocketAddr service = NetInitSocketAddr(NetGetLocalIP(), 27015);


	//Bind soocket and service
	if (bind(mainSocket, (SOCKADDR*)&service, sizeof(service)) == -1) {
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
	NetSocket acceptSocket = NET_ERROR;
	cout << "Waiting for a client to connect..." << endl;

	while (acceptSocket == NET_ERROR) {
		acceptSocket = NetAccept(mainSocket);
	}

	cout << "Client connected" << endl;
	NetSocket old_main_socket = mainSocket;
	mainSocket = acceptSocket;

	int size_data = 100;
	unsigned int suma_kontrolna = 0;
	char* data = new char[size_data];
	for (int i = 0; i < size_data; i++) {
		data[i] = i;
		suma_kontrolna += i;
	}

	//while (1){
	//	//int result = NetWrite(mainSocket, (const char*)color_buffer, buffer_size);
	//	int result = NetWrite(mainSocket, data, size_data);
	//	/*if (result == NET_ERROR) {
	//		acceptSocket = NET_ERROR;
	//		mainSocket = old_main_socket;
	//		cout << "Waiting for a client to connect..." << endl;

	//		while (acceptSocket == NET_ERROR) {
	//			acceptSocket = NetAccept(mainSocket);
	//		}

	//		cout << "Client connected" << endl;
	//		mainSocket = acceptSocket;
	//	}
	//	else {
	//		cout << "Size: " << size_data << endl;
	//		cout << "suma kontrolna: " << suma_kontrolna << endl;
	//		cout << "R: " << result << endl;
	//	}*/
	//}

	glfwSwapInterval(0);

	while (!glfwWindowShouldClose(win)){
		glClearColor(0.25, 0.25, 0.60, 1.00);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);

		unsigned char* color_buffer = new unsigned char[3 * width * height];
		unsigned int buffer_size = 3 * width*height;
		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);

		/*char* out_put = new char[2024];
		LZ4_compress_fast((const char*)color_buffer, out_put, buffer_size, 2024, 0);

		system("pause");*/

		//for (int i = 0; i < height; i++){
		//	for (int j = 0; j < width; j++){
		//		unsigned int pos = 3 * ((height - i - 1) * width + j);
		//		cout << (double)color_buffer[pos + 2] << endl;
		//		//cout << double(color_buffer[i + j]) << endl;
		//	}
		//}

		//string out_data = "{size: "+to_string(buffer_size)+"}";

		//int result = NetWrite(mainSocket, out_data.c_str(), out_data.size());
		

		char* out_put = new char[LZ4_compressBound(buffer_size)];
		int byte_return = LZ4_compress_default((char*)color_buffer, out_put, buffer_size, LZ4_compressBound(buffer_size));


		int result = NetWrite(mainSocket, out_put, byte_return);
		if (result == NET_ERROR) {
			acceptSocket = NET_ERROR;
			mainSocket = old_main_socket;
			cout << "Waiting for a client to connect..." << endl;

			while (acceptSocket == NET_ERROR) {
				acceptSocket = NetAccept(mainSocket);
			}

			cout << "Client connected" << endl;
			mainSocket = acceptSocket;
		}
		else {
			cout << "Size: " << byte_return << endl;
			cout << "R: " << result << endl;
		}
		//int result = NetWrite(mainSocket, (const char*)color_buffer, buffer_size);
		//cout << result << endl;

		delete color_buffer;
		delete out_put;

		/*cout << buffer_size << endl;
		cout << LZ4_compressBound(buffer_size) << endl;

		char* out_put = new char[LZ4_compressBound(buffer_size)];
		int byte_return = LZ4_compress_default((char*)color_buffer, out_put, buffer_size, LZ4_compressBound(buffer_size));

		cout << byte_return << endl;

		system("pause");*/
		glfwPollEvents();
		glfwSwapBuffers(win);
	}

	glfwDestroyWindow(win);
	glfwTerminate();

	////Init net socket
	//if (NetInit() != NET_OK)
	//	cout << "Error init net" << endl;

	////Create main socket
	//NetSocket mainSocket = NetSocketInit(NET_PROTO_TCP);
	//if (mainSocket == NET_INVALID_SOCKET) {
	//	cout << "Error creating socket: " << WSAGetLastError() << endl;
	//	WSACleanup();
	//}
	//else
	//	cout << "Socket Created ok" << endl;


	////Create service
	//NetSocketAddr service = NetInitSocketAddr("127.0.0.1", 27015);


	////Bind soocket and service
	//if (NetBind(mainSocket, service) == NET_ERROR) {
	//	cout << "Error bind socket" << endl;
	//	closesocket(mainSocket);
	//}
	//else
	//	cout << "Bind ok" << endl;


	////Listen
	//if (NetListen(mainSocket) == NET_ERROR)
	//	cout << "Error listening on socket" << endl;
	//else
	//	cout << "ok listen on socket" << endl;


	////waiting for client
	//SOCKET acceptSocket = NET_ERROR;
	//cout << "Waiting for a client to connect..." << endl;

	//while (acceptSocket == NET_ERROR) {
	//	acceptSocket = NetAccept(mainSocket);
	//}


	//cout << "Client connected" << endl;
	//mainSocket = acceptSocket;



	////Send data
	//for (int i = 0; i < 1000; i++){
	//	string message = to_string(i) + ". Data send";
	//	int out = NetWrite(mainSocket, message.c_str(), message.size());
	//	cout << out << endl;
	//}

	//NetDeInit();

	return 0;
}

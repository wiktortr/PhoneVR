#include <iostream>
#include <fstream>
#include <chrono>
#include <math.h>
#include <thread>

#include <bitset>

#pragma comment(lib,"WS2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <ws2tcpip.h>

struct packet_message {
	char start = -1;
	uint32_t message = 0;
	char end = 1;

	bool check() {
		if (start == -1 && end == 1 && message > 0)
			return true;
		return false;
	}
};

struct packet_sync {
	char start = -1;
	uint32_t size = 0;
	uint32_t num_of_packets = 0;
	char end = 1;

	bool check() {
		if (start == -1 && end == 1 && size > 0 && num_of_packets > 0)
			return true;
		return false;
	}
};

struct packet_data {
	char start = -1;
	uint32_t size = 0;
	uint32_t num_of_packet = 0;
	uint32_t num_of_packets = 0;
	char data[64000];
	char end = 1;

	bool check() {
		if (start == -1 && end == 1 && size > 0 && num_of_packets > 0)
			return true;
		return false;
	}
};

using namespace std;
using namespace std::chrono;


uint64_t get_time();

int width, height;
char* buffer;

int main() {


	width = 800;
	height = 600;

	int buffer_size = width * height;
	buffer = new char[buffer_size];
	memset(buffer, 100, buffer_size);
	for (int i = 0; i < buffer_size; i++) {
		buffer[i] = rand() % 240;
	}

	cout << "Input size: " << buffer_size << "B\n";
	cout << "Input size: " << buffer_size * 8 << "b\n";


	cout << "Compress 1 step size: " << (buffer_size * 4) / 8 << "B\n";
	cout << "Compress 2 step size: " << (((buffer_size * 4) / 8) * 2) / 4 << "B\n";
	/*char* buffer1 = new char[(buffer_size * 7) / 8];
	int index = 0;
	for (int i = 0; i < buffer_size; i+=8){

	for (int j = 0; j < 8; j++){


	}

	index = i - 1;
	}*/


	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result == NO_ERROR)
		cout << "Init ok" << endl;


	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
		cout << "Socket ok" << endl;


	sockaddr_in si_me;
	memset(&si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_addr.s_addr = inet_addr("192.168.1.13");
	si_me.sin_port = htons(27015);

	if (::bind(s, (sockaddr*)&si_me, sizeof(si_me)) != SOCKET_ERROR)
		cout << "Bind ok" << endl;

	sockaddr_in si_other;
	int slen = sizeof(si_other);

	packet_message msg;
	msg.message = 3;

	packet_sync sync;
	sync.size = buffer_size;
	sync.num_of_packets = buffer_size / 64000;
	if (buffer_size % 64000 > 0)
		sync.num_of_packets += 1;

	packet_data* data0 = new packet_data[sync.num_of_packets];
	int index = 0;
	int j = 0;
	for (int i = 0; i < sync.num_of_packets; i++) {
		data0[i].start = -1;
		data0[i].size = 64000;
		data0[i].num_of_packet = i;
		data0[i].num_of_packets = sync.num_of_packets;
		data0[i].end = 1;
		memset(data0[i].data, 0, 64000);
		for (j = 0; j < 64000; j++) {
			if (index + j > sync.size) {
				data0[i].size = (index + j) - 1;
				break;
			}
			data0[i].data[j] = buffer[index + j];
		}
		cout << data0[i].check() << endl;
		index += 64000;
	}

	for (;;) {
		if (recvfrom(s, (char*)&msg, sizeof(packet_message), 0, (sockaddr*)&si_other, &slen) != -1) {
			cout << "Request from: " << inet_ntoa(si_other.sin_addr) << ":" << ntohs(si_other.sin_port) << "\n";

			if (msg.check() && msg.message == 4) {

				msg.message = 2;

				Sleep(300);

				if (sendto(s, (char*)&msg, sizeof(packet_message), 0, (sockaddr*)&si_other, slen) != -1) {

					cout << "Connect to client\n";

					bool s_sync = false;
					while (!s_sync) {
						sendto(s, (char*)&sync, sizeof(packet_sync), 0, (sockaddr*)&si_other, slen);
						uint64_t s_time = get_time();
						for (;;) {
							if (recvfrom(s, (char*)&msg, sizeof(packet_message), 0, (sockaddr*)&si_other, &slen) != -1) {
								if (msg.check() && msg.message == 2) {
									cout << "Sync\n";
									s_sync = true;
									break;
								}
							}
							if (get_time() - s_time > 1000)
								break;
						}
					}

					int i;
					for (;;) {

						for (i = 0; i < sync.num_of_packets; i++)
							sendto(s, (char*)&data0[i], sizeof(packet_data), 0, (sockaddr*)&si_other, slen);

					}

					//for (;;) {
					//	/*if (recvfrom(s, (char*)&msg, sizeof(packet_message), 0, (sockaddr*)&si_other, &slen) != -1) {
					//		if (msg.check() && msg.message == 6)
					//			break;
					//	}*/

					//	//uint64_t start_time = get_time();

					//	/*packet_sync sync;
					//	sync.size = buffer_size;
					//	sync.num_of_packets = buffer_size / 64000;
					//	if (buffer_size % 64000 > 0)
					//		sync.num_of_packets += 1;*/
					//		

					//	/*packet_data* data0 = new packet_data[sync.num_of_packets];
					//	int index = 0;
					//	int j = 0;
					//	for (int i = 0; i < sync.num_of_packets; i++){
					//		data0[i].num_of_packet = i;
					//		data0[i].num_of_packets = sync.num_of_packets;
					//		memset(data0[i].data, 0, 64000);
					//		for (j = 0; j < 64000; j++){
					//			if (index + j > sync.size) {
					//				data0[i].size = (index + j) - 1;
					//				break;
					//			}
					//			data0[i].data[j] = buffer[index + j];
					//		}
					//		index += 64000;
					//	}*/
					//	//cout << get_time() - start_time << endl;

					//	//cout << "Send to: " << inet_ntoa(si_other.sin_addr) << ":" << ntohs(si_other.sin_port) << "\n";
					//	sendto(s, (char*)&sync, sizeof(packet_sync), 0, (sockaddr*)&si_other, slen);
					//	for (int i = 0; i < sync.num_of_packets; i++)
					//		sendto(s, (char*)&data0[i], sizeof(packet_data), 0, (sockaddr*)&si_other, slen);

					//	//delete data0;
					//}



				}

			}

		}
	}

	system("pause");
	return 0;
}



uint64_t get_time() {
	return (uint64_t)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

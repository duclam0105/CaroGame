#include <WS2tcpip.h>
#include "Lib.h"
#include "./Controller/Controller.h"
#include "./Controller/controlThread.h"

#pragma comment (lib, "ws2_32.lib")
#define PORT 1599
//listen: 123, 456 , 789
void handle(Controller m, SOCKET sckX, SOCKET sckO) {
	//key.lock();
	Controller ctrl = m;
	fd_set temp;
	FD_ZERO(&temp);
	FD_SET(sckX, &temp);
	FD_SET(sckO, &temp);
	cout << "Create thread" << endl;
	while (true) {
		fd_set copy = temp;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		for (int i = 0; i < socketCount; i++) {
			SOCKET sock = copy.fd_array[i];
			char buff[4096];
			ZeroMemory(buff, 4096);
			int bytesIn = recv(sock, buff, 4096, 0);
			if (bytesIn <= 0) {
				//Drop the client
				closesocket(sock);
				FD_CLR(sock, &temp);
				break;
			}
			else {
				string mess = string(buff, 0, bytesIn);
				msg_cmd cmd = ctrl.readMSG(mess);
				string strOut = ctrl.handleThread(cmd, mess);
				//send message to other clients and definiately NOT listening socket
				for (int i = 0; i < temp.fd_count; i++) {
					SOCKET outSock = temp.fd_array[i];
					send(outSock, strOut.c_str(), strOut.size() + 1, 0);
					cout << "Socket " << outSock << ": " << strOut << endl;
				}

			}
		}
	}
	//key.unlock();
}

int main() {
	Controller m;
	//mutex key;
	//===============//
	//init winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0) {
		cerr << "Cannot Initialize winsock!" << endl;
		return -1;
	}

	//creat a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Cannot create a socket!" << endl;
		return -1;
	}

	//bind the socket to an ip address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;	//could also use function: inet_pton....

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//tell winsock the socket is listening
	listen(listening, SOMAXCONN);
	cout << "Waiting for connection..." << endl;

	fd_set master;
	FD_ZERO(&master);

	FD_SET(listening, &master);

	while (true) {
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++) {
			SOCKET sock = copy.fd_array[i];
			if (m.checkSocket(sock)) {
				if (sock == listening) {
					//accept a new connection
					SOCKET client = accept(listening, nullptr, nullptr);
					//Add the new connection to the list of connection clients
					FD_SET(client, &master);
					//Send a welcome message to the connected client
					string welcomeMsg = "Welcome to Server!";
					send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
					//Broadcast we have a new connection
				}
				else {
					char buff[4096];
					ZeroMemory(buff, 4096);
					//accept a new message
					//receive the message
					int bytesIn = recv(sock, buff, 4096, 0);
					if (bytesIn <= 0) {
						//Drop the client
						closesocket(sock);
						FD_CLR(sock, &master);
					}
					else {
						string strOut;
						//read a message===================
						string mess = string(buff, 0, bytesIn);
						msg_cmd cmd = m.readMSG(mess);
						if (m.handleMSG(strOut, cmd, mess, sock)) {
							thread th(handle, m, m.tmp_sock1, m.tmp_sock2);
							th.detach();
							if (th.joinable()) {
								th.join();
							}
						}
						else {
							for (int i = 0; i < master.fd_count; i++) {
								SOCKET outSock = master.fd_array[i];
								//check xem socket hien tai co dang dung de choi game hay k. neu co thi bo qua
								if (m.checkSocket(outSock)) {
									send(outSock, strOut.c_str(), strOut.size() + 1, 0);
									cout << "Socket " << outSock << ": " << strOut << endl;
								}
							}
						}
					}
				}
			}
		}
	}
	//cleanup winsock
	WSACleanup();
	//===============//
	return 0;
}
/*
Tap lenh:
+ Khoi dong tro choi: SOCKET #xxx: PLAYER: <player name> <game id>
+ Gui du lieu ban co: SOCKET #xxx: SIZE: <size>
+ Run game: SOCKET #xxx: MOVE: <turn> <X> <O>
+ Gui thong diep: SOCKET #xxx: MSG: <msg>
+ Gui ket qua: SOCKET #xxx: Result: <X or O or Draw>
*/
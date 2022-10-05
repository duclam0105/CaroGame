#pragma once
//#include "Lib.h"
#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#define PORT 1599

using namespace std;

class client_sock {
	WSADATA data;
	std::string ipAddress;
	SOCKET sock;
	int port;
public:
	client_sock();
	~client_sock();

	//get-set IP Address
	bool client_init();		//return true if init success
	int client_receive(std::string&);
	bool client_recv(std::string&,const std::string&);
	bool client_send(const std::string&);
	void client_cleanup();
};





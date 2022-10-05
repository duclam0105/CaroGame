#include "client_socket.h"
#pragma comment (lib, "ws2_32.lib")

client_sock::client_sock() {
	ipAddress = "127.0.0.1";			//address of the server
	port = PORT;
}
client_sock::~client_sock() {
	//gracefully close down everything
	closesocket(sock);
	WSACleanup();
}

void client_sock::client_cleanup() {
	closesocket(sock);
	WSACleanup();
}

bool client_sock::client_init() {
	//Initialize winsock
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		//std::cerr << "Cannot Init Winsock! Err #" << wsResult << std::endl;
		return false;
	}

	//create a socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		///std::cerr << "Cannot create socket! Err #" << WSAGetLastError() << std::endl;
		return false;
	}

	//fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//connect to server
	int connectResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectResult == SOCKET_ERROR) {
		//std::cerr << "Cannot connect to server! Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return false;
	}
	return true;
}

int client_sock::client_receive(std::string& output) {
	int len = 1024;
	char buff[1024];
	ZeroMemory(buff, len);
	int bytesReceived = recv(sock, buff, len, 0);
	if (bytesReceived > 0) {
		output = std::string(buff, 0, bytesReceived);
		return bytesReceived;
	}
	else return -1;
}

bool client_sock::client_recv(std::string& output, const std::string& check) {
	string rMsg1;
	string rep;
	int len = 0;
	do {
		rMsg1.clear();
		rep.clear();
		len = client_receive(rMsg1);
		if (len > 0) {
			char msg[128];
			sscanf_s(rMsg1.c_str(), "SERVER: %s", msg, 128);
			rep = string(msg);
		}
		if (rep == "Error") {
			return false;
		}
	} while (rep != check);
	output = rMsg1;
	return true;
}

bool client_sock::client_send(const std::string& input) {
	int sendResult = send(sock, input.c_str(), input.size() + 1, 0);
	if (sendResult != SOCKET_ERROR) {
		return true;
	}
	else if (sendResult == SOCKET_ERROR) {
		return false;
	}
}
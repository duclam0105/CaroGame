#include "client_socket.h"
#include "Lib.h"
#include "./Controller/Controller.h"

#pragma comment (lib, "ws2_32.lib")

//thread th;

int main() {
	Controller m;
	m.runProgram();
	//client_sock client;
	//client.client_init();
	//while (true)
	//{
	//	string str = client.client_receive();
	//	cout << str << endl;
	//}

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
#pragma once
#include ".\..\client_socket.h"
#include ".\..\Lib.h"
#include ".\..\Model\Model.h"
#include ".\..\View\View.h"
#include "file.h"

class Controller {
private:
	Model mModel;
	View mView;
	string tmp_p1, tmp_p2, tmp_gameid;
	result_t tmp_result;
	file file1;
	client_sock client;
	int gameMode = 0;;
public:
	//Controller();
	//~Controller();
	bool game_run;
	void viewDisplayTable(int);
	void viewDisplayMenu();
	game_cmd readButton(vCoord);
	
	void newGame();
	void runGame();
	void continueGame();
	void saveGame();
	void loadGame();
	void quitGame();
	void findPerson();
	void showDatabase();

	void creatHost();
	void runHost();

	void joinGame();
	void runGameJoined();

	result_t checkResult();
	bool caseWin1(int, int);	//case1: 5 diem cung hang ngang(-) cung chat voi nhau VD : XXXXX
	bool caseWin2(int, int);	//case2: 5 diem cung hang doc (|) cung chat voi nhau VD: XXXXX
	bool caseWin3(int, int);	//case3: 5 diem hang cheo len tren (/) chat voi nhau VD: XXXXX
	bool caseWin4(int, int);	//case4: 5 diem cung hang cheo xuong (\) cung chat voi nhau VD: XXXXX

	void runProgram();

	bool MtoVCoordConvert(mCoord, vCoord&);
	bool VtoMCoordConvert(vCoord, mCoord&);

};


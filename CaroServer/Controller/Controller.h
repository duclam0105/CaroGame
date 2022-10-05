#pragma once
#include ".\..\Lib.h"
#include ".\..\Model\Model.h"
#include "file.h"

class Controller {
private:
	Model mModel;
	file file1;
public:
	bool game_run;
	string tmp_p1, tmp_p2, tmp_gameid;
	result_t tmp_result;
	SOCKET tmp_sock1, tmp_sock2;
	vector<SOCKET> v;

	msg_cmd readMSG(const string&);
	bool handleMSG(string&, const msg_cmd&, const string&, SOCKET&);
	string handleThread(const msg_cmd&, const string&);
	void saveData();
	bool checkSocket(const SOCKET&);
};


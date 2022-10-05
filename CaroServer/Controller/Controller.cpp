#include "Controller.h"
/*
+ Khoi dong game: p1 an host->gui tin hieu den server-> server accept
->P1: Nhap ten, game id -> server -> p2: nhap ten, gameid -> server accept -> p1: nhap size ban co

*/
//========================================//

void Controller::saveData() {
	file1.writeFile(tmp_p1, mModel.pushPlayerDataToINI(tmp_p1));
	file1.writeFile(tmp_p2, mModel.pushPlayerDataToINI(tmp_p2));
}

msg_cmd Controller::readMSG(const string& mess) {
	string tmp_msg = mess;
	char tmp_cmd[32];
	char info[64];
	sscanf_s(tmp_msg.c_str(), "%s %s", tmp_cmd, 32, info, 64);	//Doc chu dau tien cua ban tin de doc lenh
	string cmd(tmp_cmd);
	if (cmd == "Player1") {
		return cmd_p1;
	}
	else if (cmd == "Player2") {
		return cmd_p2;
	}
	else if (cmd == "Move1") {	
		return cmd_p1_move;
	}
	else if (cmd == "Move2") {
		return cmd_p2_move;
	}
	else if (cmd == "Host") {
		return cmd_host;
	}
	else if (cmd == "Join") {
		return cmd_join;
	}
	else if (cmd == "Size"){
		return cmd_size;
	}
	else if (cmd == "Result") {
		return cmd_result;
	}
	else if (cmd == "ShowDB") {
		return cmd_showDB;
	}
	else if (cmd == "Gameid") {
		return cmd_gameid;
	}

	else {
		return cmd_NaN;
	}
}

bool Controller::handleMSG(string& strOut, const msg_cmd& cmd, const string& mess, SOCKET& temp) {
	switch (cmd) {
	case cmd_host: {
		//init new game
		tmp_p1.clear();
		tmp_p2.clear();
		tmp_gameid.clear();
		//send msg to all player
		strOut = "SERVER: Matching";
		break;
	}
	case cmd_join: {
		strOut = "SERVER: Accept";
		break;
	}
	case cmd_p1: {	//Player1 <name> <game id>
		char name1[32];
		char gameid[32];
		sscanf_s(mess.c_str(), "Player1 %s %s", name1, 32, gameid, 32);
		tmp_p1 = string(name1, 0, 32);
		tmp_gameid = string(gameid, 0, 32);
		strOut = "SERVER: " + mess;
		tmp_sock1 = temp;
		break;
	}
	case cmd_gameid: {
		char gameid[32];
		sscanf_s(mess.c_str(), "Gameid %s", gameid, 32);
		string tmp(gameid);
		if (gameid == tmp_gameid) {
			strOut = "SERVER: " + mess;
			tmp_sock2 = temp;
			v.push_back(tmp_sock1);	//luu thong tin nhung socket dang duoc su dung de choi game
			v.push_back(tmp_sock2);
			return true;
		}
		else {
			//strOut = "SERVER: Error";
		}
	}
	case cmd_p2: {	//Player2 <name> <game id>
		//char name2[32];
		//char gameid[32];
		//sscanf_s(mess.c_str(), "Player2 %s %s", name2, 32, gameid, 32);
		//tmp_p2 = string(name2, 0, 32);
		//string tmp(gameid);
		//if (gameid == tmp_gameid) {
		//	strOut = "SERVER: " + mess;
		//	tmp_sock2 = temp;
		//	v.push_back(tmp_sock1);	//luu thong tin nhung socket dang duoc su dung de choi game
		//	v.push_back(tmp_sock2);
		//	return true;
		//}
		//else {
		//	//strOut = "SERVER: Error";
		//}
		//break;
	}
	case cmd_showDB: {
		strOut = "SERVER: Dir " + file1.getDirection();
		break;
	}
	default:
		strOut = mess;
		break;
	}
	return false;
}

string Controller::handleThread(const msg_cmd& cmd, const string& mess) {
	string strOut;
	switch (cmd) {
	case cmd_host: {
		//init new game
		tmp_p1.clear();
		tmp_p2.clear();
		tmp_gameid.clear();
		//send msg to all player
		strOut = "SERVER: Matching";
		break;
	}
	case cmd_join: {
		strOut = "SERVER: Accept";
		break;
	}
	case cmd_size: {	//Size <table size>
		int size;
		sscanf_s(mess.c_str(), "Size %d", &size);
		strOut = "SERVER: Size " + to_string(size);
		break;
	}
	case cmd_p1: {	//Player1 <name> <game id>
		char name1[32];
		char gameid[32];
		sscanf_s(mess.c_str(), "Player1 %s %s", name1, 32, gameid, 32);
		tmp_p1 = string(name1, 0, 32);
		tmp_gameid = string(gameid, 0, 32);
		strOut = "SERVER: " + mess;
		break;
	}
	case cmd_p2: {	//Player2 <name> <game id>
		char name2[32];
		char gameid[32];
		sscanf_s(mess.c_str(), "Player2 %s %s", name2, 32, gameid, 32);
		tmp_p2 = string(name2, 0, 32);
		string tmp(gameid);
		if (gameid == tmp_gameid) {
			strOut = "SERVER: " + mess;
		}
		else {
			strOut = "SERVER: Error";
		}
		break;
	}
	case cmd_p1_move: {	//	Move2 <turn> <pX> <pY>
		int turn, pX, pY;
		sscanf_s(mess.c_str(), "Move1 %d %d %d", &turn, &pX, &pY);
		mCoord tmp;
		tmp.p.X = pX;
		tmp.p.Y = pY;
		strOut = "SERVER: Move1 " + to_string(turn) + " " + to_string(pX) + " " + to_string(pY);
		break;
	}
	case cmd_p2_move: {	//	Move2 <turn> <pX> <pY>
		int turn, pX, pY;
		sscanf_s(mess.c_str(), "Move2 %d %d %d", &turn, &pX, &pY);
		mCoord tmp;
		tmp.p.X = pX;
		tmp.p.Y = pY;
		strOut = "SERVER: Move2 " + to_string(turn) + " " + to_string(pX) + " " + to_string(pY);
		break;
	}
	case cmd_result: {	// Result <X or O or Draw>		(data is send from host)
		char tmp[10];
		sscanf_s(mess.c_str(), "Result %s", tmp, 10);
		string result(tmp);
		//load data from ini file to buffer
		if (mModel.getPlayerDBSize() == 0) {
			vector<Player> v = file1.loadDataToDB();
			mModel.loadDataFromIni(v);
		}
		//==== cap nhat data
		mModel.insertPlayerToDB(tmp_p1, tmp_p2);
		if (result == "X_win") {
			mModel.updatePlayerResult(tmp_p1, tmp_p2, X_win);
		}
		else if (result == "O_win") {
			mModel.updatePlayerResult(tmp_p1, tmp_p2, O_win);
		}
		else {
			mModel.updatePlayerResult(tmp_p1, tmp_p1, draw);
		}
		mModel.getPlayerData(mModel.getPlayerDBSize() - 2);		//show ket qua cua player X
		cout << endl;
		mModel.getPlayerData(mModel.getPlayerDBSize() - 1);		//show ket qua cua player O

		//save data to INI file
		saveData();

		break;
	}
	case cmd_showDB: {
		strOut = "SERVER: Dir " + file1.getDirection();
		break;
	}
	default:
		strOut = mess;
		break;
	}
	return strOut;
}

bool Controller::checkSocket(const SOCKET& sock) {
	if (v.empty()) {
		return true;
	}
	else {
		for (int i = 0; i < v.size(); i++) {
			if (sock == v[i]) {
				return false;
			}
		}
	}
	return true;
}

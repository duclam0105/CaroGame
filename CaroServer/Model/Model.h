#pragma once
#include "./../Lib.h"
#include "Player.h"

class Model {
private:
	vector<Player> playerManage;
public:
	//UPDATE PLAYER DATABASE
	int getPlayerDBSize();
	void insertPlayerToDB(const string&, const string&);
	void updatePlayerResult(const string&, const string&, result_t);
	void getPlayerData(const int&);
	string pushPlayerDataToINI(const string&);
	void loadDataFromIni(vector<Player>);
};


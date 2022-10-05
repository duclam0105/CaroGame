#pragma once
#include "./../Lib.h"

class node {
private:
	typeXO_t sideXO;
	unsigned int nodeTurn;
	//bool en;
public:
	//static int numberID;
	node();
	void setSideXO(typeXO_t);
	void setTurn(const unsigned int&);
	typeXO_t getSideXO();
	unsigned int getTurn();
};

class Game {
private:
	vector<vector<node>> data;
	int current_turn;				//sau khi end game bien nay se luu so luot choi cua game do
	result_t current_result;
	string p1, p2;
public:
	Game();
	void setName(const string&, const string&);
	string getP1();
	string getP2();
	void resetData();
	void incTurn();
	int getCurrentTurn();
	void setCurrentTurn(const int&);
	void creatVirtualBoard(const int&);
	node getNode(const int&, const int&);
	bool putXtoTable(const int&, const int&);	//return true if put success
	bool putOtoTable(const int&, const int&);
	mCoord getNode_Replay(const int&);
	int getTableSize_Replay();
	//result_t getResult();
	//void setResult(result_t);
};


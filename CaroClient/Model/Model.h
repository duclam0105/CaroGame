#pragma once
#include "./../Lib.h"
#include "Player.h"
#include "Game.h"

typedef enum { cmd_printX, cmd_printO, cmd_X_Win, cmd_O_Win }cmd_game;

class Model {
private:
	Game currentGame;
	map<string, Game> dataBase;
	vector<Player> playerManage;
public:
	//void updateDatabase();
	//GAME FUNCTION
	string getP1Name();
	string getP2Name();
	void setPlayerGameName(const string&, const string&);
	void createGameTable(const int&);
	void resetGameTable();
	void setGameTurn(const int&);
	void incGameTurn();
	int getGameTurn();							//khi xem replay bien current turn se luu so luot di cua game do
	node getNodeData(int, int);
	typeXO_t getNodeType(int, int);
	bool pushXtoGame(const mCoord&);
	bool pushOtoGame(const mCoord&);

	void setCurrGame_Replay(Game);				//xem replay
	mCoord getNode_Replay(const int&);
	int getGameTable_Replay();
	
	//UPDATE GAME DATABASE
	bool checkDBEmpty();					//if empty return true else return false
	void insertCurrGameToDB(const string&);
	Game readGameFromDB(const string&);
	string getGameIDFromDB(map<string, Game>::iterator);
	map<string, Game>::iterator getMapBegin();
	map<string, Game>::iterator getMapEnd();
	//UPDATE PLAYER DATABASE
	int getPlayerDBSize();
	void insertPlayerToDB(const string&, const string&);
	void updatePlayerResult(const string&, const string&, result_t);
	void getPlayerData(const int&);
	string pushPlayerDataToINI(const string&);
	void loadDataFromIni(vector<Player>);
};


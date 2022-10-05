#include "Model.h"

//GAME FUNCTION
void Model::setPlayerGameName(const string& p1, const string& p2) {
	currentGame.setName(p1, p2);
}

string Model::getP1Name() {
	return currentGame.getP1();
}
string Model::getP2Name() {
	return currentGame.getP2();
}

void Model::setCurrGame_Replay(Game replay) {				//xem replay
	currentGame = replay;
}
mCoord Model::getNode_Replay(const int& turn) {
	return currentGame.getNode_Replay(turn);
}
int Model::getGameTable_Replay() {
	return currentGame.getTableSize_Replay();
}

void Model::resetGameTable(){
	currentGame.resetData();
}

void Model::createGameTable(const int& size) {
	currentGame.creatVirtualBoard(size);
}

int Model::getGameTurn() {
	return currentGame.getCurrentTurn();
}

node Model::getNodeData(int row, int col) {
	node tmp = currentGame.getNode(row, col);
	return tmp;
}

typeXO_t Model::getNodeType(int row, int col) {
	node tmp = currentGame.getNode(row, col);
	return tmp.getSideXO();
}

bool Model::pushXtoGame(const mCoord& mNode) {
	return currentGame.putXtoTable((int)mNode.p.Y, (int)mNode.p.X);
}

bool Model::pushOtoGame(const mCoord& mNode) {
	return currentGame.putOtoTable((int)mNode.p.Y, (int)mNode.p.X);
}

void Model::setGameTurn(const int& turn) {
	currentGame.setCurrentTurn(turn);
}

void Model::incGameTurn() {
	currentGame.incTurn();
}

//UPDATE GAME DATABASE
bool Model::checkDBEmpty() {
	return dataBase.empty();
}
void Model::insertCurrGameToDB(const string& gameID) {
	dataBase.insert({ gameID, currentGame });
}
Game Model::readGameFromDB(const string& gameID) {
	Game tmp = dataBase[gameID];
	return tmp;
}
map<string, Game>::iterator Model::getMapBegin() {
	return dataBase.begin();
}
map<string, Game>::iterator Model::getMapEnd() {
	return dataBase.end();
}
string Model::getGameIDFromDB(map<string, Game>::iterator index) {
	return index->first;
}
//PLAYER MANAGE FUNCTION===========//
int Model::getPlayerDBSize() {
	return playerManage.size();
}
void Model::insertPlayerToDB(const string& playerX, const string& playerO) {
	int count1 = 0, count2 = 0;
	if (playerManage.empty()) {
		Player p1, p2;
		p1.setName(playerX);
		p2.setName(playerO);
		playerManage.push_back(p1);
		playerManage.push_back(p2);
	}
	for (int i = 0; i < playerManage.size(); i++) {
		if (playerManage[i].getName() == playerX) {
			count1++;									//Neu co trong co so du lieu roi thi thoi
		}
		else if (playerManage[i].getName() == playerO) {
			count2++;									//Neu co trong co so du lieu roi thi thoi
		}
	}
	if (count1 == 0) {
		Player p1;
		p1.setName(playerX);
		playerManage.push_back(p1);
	}
	if (count2 == 0) {
		Player p2;
		p2.setName(playerO);
		playerManage.push_back(p2);
	}
}

void Model::updatePlayerResult(const string& playerX, const string& playerO, result_t result) {
	int X_index, O_index;
	for (int i = 0; i < playerManage.size(); i++) {
		if (playerManage[i].getName() == playerX) {
			X_index = i;
		}
		else if (playerManage[i].getName() == playerO) {
			O_index = i;
		}
	}
	switch (result)
	{
	case X_win: {
		playerManage[X_index].incNumberWin();
		playerManage[O_index].incNumberLoss();
		break;
	}
	case O_win: {
		playerManage[O_index].incNumberWin();
		playerManage[X_index].incNumberLoss();
		break;
	}
	case draw: {
		playerManage[X_index].incNumberDraw();
		playerManage[O_index].incNumberDraw();
		break;
	}
	default:
		break;
	}
}

void Model::getPlayerData(const int& index) {
	cout << playerManage[index].getName() << " Win: " << playerManage[index].getNumberWin()
		<< " Lose: " << playerManage[index].getNumberLose() << " Draw: " << playerManage[index].getNumberDraw();
}
string Model::pushPlayerDataToINI(const string& playerName) {
	for (int index = 0; index < playerManage.size(); index++) {
		if (playerManage[index].getName() == playerName) {
			string str = " Win: " + to_string(playerManage[index].getNumberWin()) +
				" Lose: " + to_string(playerManage[index].getNumberLose()) + " Draw: " + to_string(playerManage[index].getNumberDraw());
			return str;
		}
	}
}
void Model::loadDataFromIni(vector<Player> v) {
	playerManage = v;
}
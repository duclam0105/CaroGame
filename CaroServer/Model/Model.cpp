#include "Model.h"

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
	switch (result) {
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
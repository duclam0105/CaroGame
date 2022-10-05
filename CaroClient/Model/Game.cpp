#include "Game.h"


//NODE FUNCTION===============================================================//
node::node() {
//		en = disable;
		sideXO = other;
		nodeTurn = 0;
}
void node::setSideXO(typeXO_t side)					{ this->sideXO = side; }
void node::setTurn(const unsigned int& turn)		{ this->nodeTurn = turn; }
typeXO_t node::getSideXO()							{ return this->sideXO; }
unsigned int node::getTurn()						{ return this->nodeTurn; }

//GAME FUNCTION===============================================================//
void Game::setName(const string& playerX, const string& playerO) {
	p1 = playerX;
	p2 = playerO;
}
string Game::getP1() {
	return p1;
}
string Game::getP2() {
	return p2;
}
Game::Game() {
	current_turn = 1;
	current_result = is_playing;
}

void Game::resetData() {
	data.clear();
	current_turn = 1;
}

node Game::getNode(const int& row, const int& col) {
	return data[row][col];
}

void Game::setCurrentTurn(const int& turn) {
	this->current_turn = turn;
}

void Game::creatVirtualBoard(const int& size) {
	node tmp_node;
	vector<node> tmp_vec;
	tmp_vec.assign(size, tmp_node);
	data.assign(size, tmp_vec);
}

int Game::getCurrentTurn() {
	return this->current_turn;
}

void Game:: incTurn() {
	this->current_turn++;
}

mCoord Game::getNode_Replay(const int& turn) {
	for (int row = 0; row < data.size(); row++) {
		for (int col = 0; col < data.size(); col++) {
			if (data[row][col].getTurn() == turn) {
				mCoord tmp;
				tmp.p.X = (SHORT)col;
				tmp.p.Y = (SHORT)row;
				return tmp;
			}
		}
	}
}
int Game::getTableSize_Replay() {
	return this->data.size();
}

//result_t Game::getResult() {
//	return current_result;
//}
//
//void Game::setResult(result_t result) {
//	this->current_result = result;
//}

bool Game::putXtoTable(const int& row, const int& col) {
	if (data[row][col].getSideXO() == other) {
		data[row][col].setSideXO(side_X);
		data[row][col].setTurn(this->current_turn);
		//current_turn++;
		return true;
	}
	else if (data[row][col].getSideXO() != other) {
		return false;
	}
	return false;
}

bool Game::putOtoTable(const int& row, const int& col) {
	if (data[row][col].getSideXO() == other) {
		data[row][col].setSideXO(side_O);
		data[row][col].setTurn(this->current_turn);
		//current_turn++;
		return true;
	}
	else if (data[row][col].getSideXO() != other) {
		return false;
	}
	return false;
}


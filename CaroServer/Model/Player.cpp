#include "Player.h"

Player::Player() {
	numberWin = numberLose = numberDraw = 0;
}
void Player::setName(const string& name)		{ this->name = name; }
void Player::setNumberWin(const int& numWin)	{ this->numberWin = numWin; }
void Player::setNumberLoss(const int& numLose)	{ this->numberLose = numLose; }
void Player::setNumberDraw(const int& numDraw)	{ this->numberDraw = numDraw; }
void Player::incNumberWin()						{ numberWin++; }
void Player::incNumberLoss()					{ numberLose++; }
void Player::incNumberDraw()					{ numberDraw++; }
string Player::getName()						{ return this->name; }
int Player::getNumberWin()						{ return this->numberWin; }
int Player::getNumberLose()						{ return this->numberLose; }
int Player::getNumberDraw()						{ return this->numberDraw; }
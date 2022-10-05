#pragma once
#include "./../Lib.h"
class Player {
private:
	string name;
	unsigned int numberWin;
	unsigned int numberLose;
	unsigned int numberDraw;
public:
	Player();
	void setName(const string&);
	void setNumberWin(const int&);
	void setNumberLoss(const int&);
	void setNumberDraw(const int&);
	void incNumberWin();
	void incNumberLoss();
	void incNumberDraw();
	string getName();
	int getNumberWin();
	int getNumberLose();
	int getNumberDraw();
};


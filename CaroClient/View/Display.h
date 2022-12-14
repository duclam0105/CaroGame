#pragma once
#include "./../Lib.h"

#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7

#define default_ScreenWidth				800
#define default_ScreenHeight			600

class Display{
public:
	void resizeConsole(const int&, const int&);				//width, height
	void changeTextColor(const int&);						//Color code, default is 7 - white
	//void gotoXY(const unsigned int&, const unsigned int&);	// X, Y	
	void gotoXY(SHORT x, SHORT y);
	void clearScreen();
};


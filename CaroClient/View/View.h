#pragma once
#include ".\..\Lib.h"
#include "Display.h"
//#include "MouseHandle.h"

class View: public Display {
	/*friend class MouseHandle;*/
private:
	SHORT tableSize;
	vector<vCoord> vNode;
public:
	void addNode(const SHORT&, const SHORT&, bool );
	void checkNodeExits(const SHORT&, const SHORT&, bool );
	bool checkNodeEnable(SHORT , SHORT );
	void setNodeStatus(SHORT, SHORT, bool);

	void setTableSize(SHORT);
	SHORT getTableSize();

	void deleteTable();
	void displayName();
	void displayMenu();
	void displayTable(int);
	void displayTurn(int);					//
	void displayDBBox();
	void displayMsg(SHORT, SHORT, string);
	void clearNortifiBox();
	void deleteNameBox();

	vCoord mouse();
	bool mouse2(vCoord&);
	bool mouse3(vCoord&);
	/*game_cmd readButton(vCoord);*/

	void printX(vCoord);					//in ra X
	void printO(vCoord);					//in ra O
	//get mouse input
};


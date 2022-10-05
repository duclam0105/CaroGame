#include "View.h"

void View::addNode(const SHORT& x, const SHORT& y, bool status) {
	COORD node = { x, y };
	//Neu trong vector chua co du lieu cua toa do X,Y
	vCoord tmp;
	tmp.p = node;					//gan toa do
	tmp.en = status;
	vNode.push_back(tmp);
	return;
}

void View::checkNodeExits(const SHORT& x, const SHORT& y, bool status) {
	//int count = 0;
	COORD node = { x, y };
	if (vNode.empty()) {
		addNode(x, y, status);
		return;
	}
	for (int i = 0; i < vNode.size(); i++) {
		if ((vNode[i].p.X == node.X) && (vNode[i].p.Y == node.Y)) {
			return;				//Neu co du lieu trung voi toa do X, Y thi return luon
		}
	}
	//Neu trong vector chua co du lieu cua toa do X,Y
	addNode(x, y, status);
	return;
}

void View::setNodeStatus(SHORT x, SHORT y, bool status) {
	COORD node = { x, y };
	if (vNode.empty()) {
		addNode(x, y, status);
		return;
	}
	for (int i = 0; i < vNode.size(); i++) {
		if ((vNode[i].p.X == node.X) && (vNode[i].p.Y == node.Y)) {
			vNode[i].en = status;
			return;
		}
	}
	//Neu trong vector chua co du lieu cua toa do X,Y
	addNode(x, y, status);
	return;
}

bool View::checkNodeEnable(SHORT x, SHORT y) {				//return 1 if enable; return 0 if disable
	COORD node = { x, y };
	if (vNode.empty()) {
		addNode(x, y, true);
		return true;
	}
	for (int i = 0; i < vNode.size(); i++) {
		if ((vNode[i].p.X == node.X) && (vNode[i].p.Y == node.Y)) {
			return vNode[i].en;
		}
	}
	//Neu trong vector chua co du lieu cua toa do X,Y
	addNode(x, y, true);
	return vNode[vNode.size() - 1].en;
}

void View::setTableSize(SHORT size) {
	this->tableSize = size;
}

SHORT View::getTableSize() {
	return this->tableSize;
}

void View::printX(vCoord vNode) {					//in ra X
	gotoXY(vNode.p.X, vNode.p.Y);
	changeTextColor(ColorCode_Blue);
	cout << "X";
	setNodeStatus(vNode.p.X + 1, vNode.p.Y, disable);
	setNodeStatus(vNode.p.X - 1, vNode.p.Y, disable);
	/*gotoXY(0, 0);*/
	changeTextColor(default_ColorCode);
}

void View::printO(vCoord vNode) {					//in ra O
	gotoXY(vNode.p.X, vNode.p.Y);
	changeTextColor(ColorCode_Red);
	cout << "O";
	setNodeStatus(vNode.p.X + 1, vNode.p.Y, disable);
	setNodeStatus(vNode.p.X - 1, vNode.p.Y, disable);
	/*gotoXY(0, 0);*/
	changeTextColor(default_ColorCode);
}

void View::displayTurn(int turn) {
	gotoXY(7, 6);
	cout << turn;
}
void View::displayMsg(SHORT x, SHORT y, string msg) {
	gotoXY(x, y);
	changeTextColor(ColorCode_DarkPink);
	cout << msg;
	changeTextColor(default_ColorCode);
}
void View::clearNortifiBox() {
	displayMsg(25, 4, "                                 ");	//xoa msg
	displayMsg(25, 5, "                                 ");	//xoa msg
	displayMsg(25, 6, "                                 ");	//xoa msg
}

void View::displayTable(int size) {		//const unsigned int& size
	changeTextColor(ColorCode_DarkGreen);
	//gotoXY(25, 4);
	//cout << "Nhap kich thuoc cua ban co: ";
	//cin >> this->tableSize;
	this->tableSize = size;
	SHORT x = TABLE_POS_X;				//vi tri cua table
	SHORT y = TABLE_POS_Y;				//vi tri cua table
	for (SHORT row = 0; row < CELL_HEIGHT * this->tableSize +1; row++) {			//x la col; y la row
		if ((row % CELL_HEIGHT == 0)||(row==0)) {
			for (SHORT col = 0; col < CELL_WIDTH * this->tableSize +1; col++) {
				SHORT a = x + col;
				SHORT b = y + row;
				gotoXY(a, b);
				cout << "-";
				setNodeStatus(a, b, disable);
			}
		}
		else if (row % CELL_HEIGHT == 1) {			//TH cell height = 2
			for (SHORT col = 0; col < CELL_WIDTH * this->tableSize + 1; col++) {
				if ((col % CELL_WIDTH == 0)||(col == 0)) {
					SHORT a = x + col;
					SHORT b = y + row;
					gotoXY(a, b);
					cout << "|";
					setNodeStatus(a, b, disable);
				}
			}
		}
	}
	changeTextColor(default_ColorCode);					//
	clearNortifiBox();
}

void View::deleteTable() {
	SHORT x = 2;//TABLE_POS_X;				//vi tri cua table
	SHORT y = 7;//TABLE_POS_Y;				//vi tri cua table
	for (SHORT row = y; row < 35; row++) {			//x la col; y la row
		for (SHORT col = x; col < 78; col++) {
			SHORT a = col;
			SHORT b = row;
			gotoXY(a, b);
			cout << " ";
			setNodeStatus(a, b, enable);
		}
	}
}

void View::displayDBBox() {
	//display player list
	for (SHORT row = 8; row < 31; row++) {
		for (SHORT col = 2; col < 49; col++) {
			if ((row == 8) || (row == 30)) {
				changeTextColor(col % 15 + 1);
				gotoXY(col, row);
				cout << "~";
			}
			else if ((row != 8) && (row != 30)) {
				changeTextColor(row % 15 + 1);
				gotoXY(2, row);
				cout << "|";
				gotoXY(48, row);
				cout << "|";
			}
		}
	}
	changeTextColor(default_ColorCode);
	gotoXY(5, 8);
	cout << " PLAYER LIST ";
	SHORT tmp_x = 4;
	SHORT tmp_y = 10;
	for (int i = 1; i <= 10; i++) {
		gotoXY(tmp_x, tmp_y);
		cout << i << ". ";					//next: < 7, y>
		tmp_y += 2;
	}
	//display game list
	for (SHORT row = 8; row < 31; row++) {
		for (SHORT col = 56; col < 77; col++) {
			if ((row == 8) || (row == 30)) {
				changeTextColor(col % 15 + 1);
				gotoXY(col, row);
				cout << "~";
			}
			else if ((row != 8) && (row != 30)) {
				changeTextColor(row % 15 + 1);
				gotoXY(56, row);
				cout << "|";
				gotoXY(76, row);
				cout << "|";
			}
		}
	}
	changeTextColor(default_ColorCode);
	gotoXY(59, 8);
	cout << " GAME LIST ";
	tmp_x = 58;
	tmp_y = 10;
	for (int i = 1; i <= 10; i++) {
		gotoXY(tmp_x, tmp_y);
		cout << i << ". ";					//next: < 7, y>
		tmp_y += 2;
	}
}

void View::displayName() {
	gotoXY(1, 3);
	changeTextColor(ColorCode_Blue);
	cout << "PLAYER 1 <X>:                   ";		//next: <15, 3>
	gotoXY(1, 4);
	changeTextColor(ColorCode_Red);
	cout << "PLAYER 2 <O>:                   ";		//next: <15, 4>
	gotoXY(1, 5);
	changeTextColor(ColorCode_DarkYellow);
	cout << "GAME ID:               ";				//next: <10, 5>
	changeTextColor(default_ColorCode);
	gotoXY(1, 6);
	cout << "TURN:      ";				//next: <7, 6>
}
void View::deleteNameBox() {
	gotoXY(1, 3);
	changeTextColor(ColorCode_Blue);
	cout << "                                ";		//next: <15, 3>
	gotoXY(1, 4);
	changeTextColor(ColorCode_Red);
	cout << "                                ";		//next: <15, 4>
	gotoXY(1, 5);
	changeTextColor(ColorCode_DarkYellow);
	cout << "                        ";				//next: <10, 5>
	changeTextColor(default_ColorCode);
	gotoXY(1, 6);
	cout << "           ";				//next: <7, 6>
}

void View::displayMenu() {
	clearScreen();
	//resizeConsole(800, 800);
	SHORT x = 0;				//vi tri cua table
	SHORT y = 0;				//vi tri cua table
	SHORT max_row = 36;
	SHORT max_col = 80;
	for (SHORT row = 0; row < max_row; row++) {			//x la col; y la row
		for (SHORT col = 0; col < max_col; col++) {
			if ((row == 0) || (row == max_row - 1)) {
				changeTextColor(col % 15 + 1);
				gotoXY(col, row);
				cout << "*";
			}
			else if ((row != 0) && (row != max_row - 1)) {
				changeTextColor(row % 15 + 1);
				gotoXY(0, row);
				cout << "*";
				gotoXY(max_col - 1, row);
				cout << "*";
			}
		}
	}
	changeTextColor(default_ColorCode);
	gotoXY(max_col / 2 - 15, 0);
	cout << "CARO GAME - LAMNGUYENDUC";
	changeTextColor(ColorCode_Yellow);
	gotoXY(1, 1);
	cout << "<NEW> <SAVE> <LOAD> <QUIT> <DATABASE> <FIND> <HOST> <JOIN>";
	gotoXY(72, 1);
	cout << "<EXIT>";
	changeTextColor(default_ColorCode);
}

vCoord View::mouse() {
	INPUT_RECORD ir[128];
	DWORD        nRead;
	COORD        xy;
	HANDLE       hStdInput = NULL;
	HANDLE       hStdOutput = NULL;
	HANDLE       hEvent = NULL;
	hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hStdInput);
	SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE handles[2] = { hEvent, hStdInput };
	while (WaitForMultipleObjects(2, handles, FALSE, INFINITE)) {
		ReadConsoleInput(hStdInput, ir, 128, &nRead);
		for (unsigned int i = 0; i < nRead; i++) {
			if (ir[i].EventType == MOUSE_EVENT) { //
				xy.X = ir[i].Event.MouseEvent.dwMousePosition.X, xy.Y = ir[i].Event.MouseEvent.dwMousePosition.Y;
				if (((int)ir[i].Event.MouseEvent.dwButtonState & 0x07) == 1) {//
					if (checkNodeEnable(xy.X, xy.Y)) {
						vCoord tmp;
						tmp.p.X = xy.X;
						tmp.p.Y = xy.Y;
						tmp.en = disable;
						setNodeStatus(xy.X, xy.Y, disable);
						return tmp;
					}
				}
			}
		}
	}
}

bool View::mouse2(vCoord& tmp) {
	INPUT_RECORD ir[128];
	DWORD        nRead;
	COORD        xy;
	HANDLE       hStdInput = NULL;
	HANDLE       hStdOutput = NULL;
	HANDLE       hEvent = NULL;
	hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hStdInput);
	SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE handles[2] = { hEvent, hStdInput };
	//while (WaitForMultipleObjects(2, handles, FALSE, INFINITE)) {
		ReadConsoleInput(hStdInput, ir, 128, &nRead);
		//for (int i = 0; i < 1000; i++) {
		//	if (i == 1000 - 1) {
		//		return;
		//	}
			for (unsigned int i = 0; i < nRead; i++) {
				if (ir[i].EventType == MOUSE_EVENT) { //
					if (((int)ir[i].Event.MouseEvent.dwButtonState & 0x07) == 1) {//
						xy.X = ir[i].Event.MouseEvent.dwMousePosition.X, xy.Y = ir[i].Event.MouseEvent.dwMousePosition.Y;
						tmp.p.X = xy.X;
						tmp.p.Y = xy.Y;
						tmp.en = disable;
						return true;
					}
				}
			}
		//}
	//}
			return false;
}
bool View::mouse3(vCoord& tmp) {
	INPUT_RECORD ir[128];
	DWORD        nRead;
	COORD        xy;
	HANDLE       hStdInput = NULL;
	HANDLE       hStdOutput = NULL;
	HANDLE       hEvent = NULL;
	hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hStdInput);
	SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE handles[2] = { hEvent, hStdInput };
	//while (WaitForMultipleObjects(2, handles, FALSE, INFINITE)) {
	ReadConsoleInput(hStdInput, ir, 128, &nRead);
	//for (int i = 0; i < 1000; i++) {
	//	if (i == 1000 - 1) {
	//		return;
	//	}
	for (unsigned int i = 0; i < nRead; i++) {
		if (ir[i].EventType == MOUSE_EVENT) { //
			if (((int)ir[i].Event.MouseEvent.dwButtonState & 0x07) == 1) {//
				xy.X = ir[i].Event.MouseEvent.dwMousePosition.X, xy.Y = ir[i].Event.MouseEvent.dwMousePosition.Y;
				if (checkNodeEnable(xy.X, xy.Y)) {
					//vCoord tmp;
					tmp.p.X = xy.X;
					tmp.p.Y = xy.Y;
					tmp.en = disable;
					setNodeStatus(xy.X, xy.Y, disable);
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	//}
//}
	return false;
}


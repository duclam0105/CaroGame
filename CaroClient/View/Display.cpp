#include "Display.h"

// Hàm thay đổi kích cỡ của khung cmd.
void Display::resizeConsole(const int& width, const int& height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void Display::changeTextColor(const int& color) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, color);
}

//x,y là tọa điểm x,y trên màn hình
//void Display::gotoXY(const unsigned int& x, const unsigned int& y) {	
//	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD a = { x, y };    
//	SetConsoleCursorPosition(h, a);
//}
void Display::gotoXY(SHORT x, SHORT y) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD a = { x, y };
	SetConsoleCursorPosition(h, a);
}

// Hàm xóa màn hình.
void Display::clearScreen() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/*COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);*/
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coordScreen = { 0,0 };
	DWORD cCharsWritten;
	DWORD dwConSize;

	GetConsoleScreenBufferInfo(hOut, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hOut, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hOut, &csbi);
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hOut, coordScreen);
	//system("cls");
}

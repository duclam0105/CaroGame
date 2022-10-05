#include "MouseHandle.h"

void MouseHandle::mouseHandle() {
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
		for (int i = 0; i < nRead; i++) {
			if (ir[i].EventType == MOUSE_EVENT) {
				xy.X = ir[i].Event.MouseEvent.dwMousePosition.X, xy.Y = ir[i].Event.MouseEvent.dwMousePosition.Y;
				/*SetConsoleCursorPosition(hStdOutput, xy);
				cout << ((int)ir[i].Event.MouseEvent.dwButtonState & 0x07);*/
				if (((int)ir[i].Event.MouseEvent.dwButtonState & 0x07) == 1) {
					//if (m.checkNodeEnable(xy.X, xy.Y)) {
					//	SetConsoleCursorPosition(hStdOutput, xy);
					//	cout << "X";
					//}
				}
			}
			if (ir[i].EventType == KEY_EVENT) {
				if (ir[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
					//SetEvent(hEvent);
					return;
				}
			}
		}
		//	for (i = 0; i < nRead; i++)
//	{				// mouse buttons and xy position within console in character spaces
//		mouseX = ir[i].Event.MouseEvent.dwMousePosition.X;
//		mouseY = ir[i].Event.MouseEvent.dwMousePosition.Y;
//		if (ir[i].Event.MouseEvent.dwButtonState == 1) lMouse = true;
//		if (ir[i].Event.MouseEvent.dwButtonState == 2) rMouse = true;
//	}
	}

}

#include"Helper.h"


void GoToxy(int x, int y) {
	COORD pos;
	HANDLE hahaha;
	pos.X = x;
	pos.Y = y;
	hahaha = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hahaha, pos);
}
void Getxy(int& x, int& y) {
	HANDLE temp_handle;
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	temp_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(temp_handle, &pBuffer);
	x = pBuffer.dwCursorPosition.X;
	y = pBuffer.dwCursorPosition.Y;
	//cout << x << ',' << y;
}
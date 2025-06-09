#include "Utils.h"
#include <windows.h>
#include <iostream>

void Utils::setCursor(int x, int y) {
	HANDLE handle;
	COORD coordinates;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(handle, coordinates);
}
char Utils::cursorCharRead() {

	//code from stackOverflow (https://stackoverflow.com/questions/54994490/how-to-read-current-character-from-what-stdout-console-cursor-pointing-on)

	char buf[BUFSIZ];
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	COORD pos = csbiInfo.dwCursorPosition; //set pos to current cursor location
	TCHAR strFromConsole[1];    //need space to only one char
	DWORD dwChars;
	ReadConsoleOutputCharacter(
		hConsole,
		strFromConsole, // Buffer where store symbols
		1, // Read 1 char to strFormConsole
		pos, // Read from current cursor position
		&dwChars); // How many symbols stored
	char c = strFromConsole[0];
	return c;
}
int Utils::randomNumberGenerator(int min, int max) {
	srand((unsigned)time(NULL));
	int n = rand();
	return n % max + min;
}

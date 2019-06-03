#include "ConsoleController.h"

bool fullLogColor = false;

/* ______                       __        ________       __
  / ____/___  ____  _________  / /__     / ____/ /______/ /
 / /   / __ \/ __ \/ ___/ __ \/ / _ \   / /   / __/ ___/ / 
/ /___/ /_/ / / / (__  ) /_/ / /  __/  / /___/ /_/ /  / /  
\____/\____/_/ /_/____/\____/_/\___/   \____/\__/_/  /_/   
                                                           
Henry Oliver

Verison 3.0
														   */

void Console_Banner() {

		srand((unsigned int)time(NULL));
		int color = rand() % 15 + 1;
		Console_ColoredTEXT("===============================================================\n", color);
		Console_ColoredTEXT("    _______                      __        ________       __ \n", color);
		Console_ColoredTEXT("   / ____ /___ ____  _________  / /__     / ____/ /______/ / \n", color);
		Console_ColoredTEXT("  / /   / __ \\/ __ \\/ ___/ __ \\/ / _ \\   / /   / __/ ___/ / \n", color);
		Console_ColoredTEXT(" / /___/ /_/ / / / (__  ) /_/ / /  __/  / /___/ /_/ /  / /  \n", color);
		Console_ColoredTEXT(" \\____/\\____/_/ /_/____/\\____/_/\\___/   \\____/\\__/_/  /_/   \n", color);
		Console_ColoredTEXT(" ~Henry Oliver                                    v 3.0\n", color);\
		Console_ColoredTEXT("===============================================================\n", color);
		Console_ColoredTEXT("\n", 15);

}

void Console_gotoXY(int x, int y) //Move Console Cursor to XY
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console_Resize(int x, int y) { //Resize Console Window
	RECT m_rect;
	HWND m_console = GetConsoleWindow();
	GetWindowRect(m_console, &m_rect); //stores the console's current dimensions
	MoveWindow(m_console, m_rect.left, m_rect.top, x, y, TRUE);

}

void Console_Clear() { //Clear console window
	system("cls");
	Console_gotoXY(0, 0);
}

void Console_FontSize(int x, int y) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = x;
	lpConsoleCurrentFontEx->dwFontSize.Y = y;
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}

/*
 
COLOR CODES:

RANGE: 0-254

0 - BLACK
1 - DARK BLUE
2 - DARK GREEN
3 - DARK AQUA
4 - DARK RED
5 - DARK PINK
6 - DARK YELLOW
7 - LIGHT GREY
8 - GREY
9 - BLUE
10 - GREEN
11 - AQUA
12 - RED
13 - PINK
14 - YELLOW
15 - WHITE

0-15 BLACK BACK
16-31 DARK BLUE BACK
32-47 DARK GREEN BACK
48-63 DARK AQUA BACK
64-79 DARK RED BACK
80-95 DARK PINK BACK
96-111 DARK YELLOW BACK
112-127 LIGHT GREY BACK
128-143 GREY BACK
144-159 BLUE BACK
160-175 GREEN BACK
176-191 AQUA BACK
192-207 RED BACK
208-223 PINK BACK
224-239 YELLOW BACK
240-254 WHITE BACK

*/

void Console_ColoredTEXT(string m_word, int m_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_color);
	cout << m_word;
}

void Console_ColoredTEXTChar(char m_word, int m_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_color);
	cout << m_word;
}

void Console_RainbowWrite(std::string m_word) {
	srand((unsigned int)time(NULL));
	
	for (size_t i = 0; i < m_word.length(); i++)
	{
		Console_ColoredTEXTChar(m_word[i], rand() % 15 + 1);
	}
}

void Console_OutputLog(std::string log, int type) {
	Console_ColoredTEXT("[", DEFAULT);
	switch (type)
	{
	case LOGINFO: {
		Console_ColoredTEXT("INFO", LOGINFO);
		break;
	}
	case LOGWARN: {
		Console_ColoredTEXT("WARN", LOGWARN);
		break;
	}
	case LOGFATAL: {
		Console_ColoredTEXT("FATAL", LOGFATAL);
		break;
	}
	default: {
		Console_ColoredTEXT("UNKN", DEFAULT);
		break;
	}
	}
	Console_ColoredTEXT("] ", DEFAULT);
	log = log + "\n";
	if (fullLogColor) {
		Console_ColoredTEXT(log, type);
	}
	else {
		Console_ColoredTEXT(log, DEFAULT);
	}
}
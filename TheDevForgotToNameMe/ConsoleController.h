#pragma once
#include <windows.h> 
#include <iostream>
#include <chrono>
#include <string>
#include <vector>  
#include <stdlib.h>  
#include <time.h>  
#include <stdio.h>

using namespace std;

enum LOGCOLOR
{
	DEFAULT = 15,
	LOGINFO = 10,
	LOGWARN = 6,
	LOGFATAL = 12,
};

void Console_Banner();

void Console_gotoXY(int x, int y);

void Console_Resize(int x, int y);

void Console_Clear();

void Console_FontSize(int a, int b);

void Console_ColoredTEXT(string m_word, int m_color);

void Console_RainbowWrite(string m_word);

void Console_OutputLog(std::string log, int type);

#pragma once
/* 

Time till normal win: 240 minutes = 4 hours

Time till easy win: 5 minutes

*/


class GameManager {
public:
	enum Screens {
		MAIN,
		GAME,
		GAMEOVER
	};
	int currentScreen = MAIN;
	float score = 0;
	bool gameover = false;
	bool won = false;
	bool easy_mode = false;
	bool override_win = false;
	bool leave = false;
	void CheckGeneralInput(GameManager& m_game);
};


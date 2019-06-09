#pragma once

#include <vector>
#include <fstream>
#include "3D.h"

class GameManager {
public:
	GameManager();

	enum Screens {
		MAIN,
		GAME,
		GAMEOVER
	};
	int currentScreen = MAIN;

	std::vector<Enemy*>* enemyList;
	Camera* mCam;

	float score = 0;
	int wave = 1;
	int waveSpawnAmount = 3;
	int lives = 3;
	int amountSpawned = 0;
	float highscore = 0.0f;
	float enemyMoveSpeed = 0.5f;
	bool waveSpawned = false;
	bool gameover = false;
	bool leave = false;
	
	void CheckGeneralInput(GameManager& m_game);
};


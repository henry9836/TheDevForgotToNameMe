#include "GamerManager.h"
#include "Input.h"

Input m_Input;

void GameManager::CheckGeneralInput(GameManager& m_game)
{
	switch (m_game.currentScreen)
	{
	case m_game.MAIN: {
		if (m_Input.CheckKeyDown('1')) {
			m_game.easy_mode = false;
			m_game.currentScreen = m_game.GAME;
		}
		if (m_Input.CheckKeyDown('2')) {
			m_game.easy_mode = true;
			m_game.currentScreen = m_game.GAME;
		}
		if (m_Input.CheckKeyDown('q') == true)
		{
			m_game.leave = true;
		}
		break;
	}
	case m_game.GAME: {
		if ((m_Input.CheckKeyDown('p')) && (m_game.easy_mode)) {
			override_win = true;
		}
		break;
	}
	case m_game.GAMEOVER: {
		if (m_Input.CheckKeyDown('c')) {
			m_game.gameover = false;
			m_game.won = false;
			m_game.easy_mode = false;
			m_game.currentScreen = m_game.MAIN;
			m_game.score = 0;
		}
		break;
	}
	default:
		break;
	}
}

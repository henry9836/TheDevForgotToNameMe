#include <iostream>
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>
#include <time.h>
#include <vector>

#include "ShaderLoader.h"
#include "Audio.h"
#include "Camera.h"
#include "GamerManager.h"
#include "ScreenInfo.h"
#include "Input.h"
#include "Model.h"
#include "ModelMesh.h"
#include "ObjectManager.h"
#include "ShaderLoader.h"
#include "Sphere.h"
#include "TextLabel.h"
#include "Sprite.h"
#include "ConsoleController.h"
#include "3D.h"

using namespace std;

//Classes

Camera mCam;
ScreenInfo mScreen;
AudioSystem mAudio;
TextLabel mScore;
TextLabel mWaveNum;
TextLabel gameOverText;
TextLabel mainText;
TextLabel mLivesText;
TextLabel highscoreText;
GameManager m_Game;
ObjectManager objManager;
LoadTexture textureLoader;

//Sprite
Sprite backdropSprite;

//Models
Model tankModel;
Model shellModel;

//Vectors
vector<Simple3DObject*> simple3DObjects;
vector<Sprite*> menuSprites;
vector<Sprite*> gameSprites;
vector<Model*> menuModels;
vector<Model*> mainModels;
vector<Bullet*> bulletObjects;
vector<Enemy*> enemyObjects;

//Cubemap
CubeMap cubeMap;

//Global Vars

float r = 1.0;
float b = 0.0;
float g = 0.0;

glm::vec3 rotZ = glm::vec3(0.0f, 0.0f, 1.0f);

float rotationAngle = 0;
float currentTime;
float deltaTime;
float pasttime;

GLuint backIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat backVerts[] = {
	1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-1.0f, -1.0f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	1.0f, -1.0f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};

void Render() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	r = (rand() % 10 + 1) / 10.0f;
	g = (rand() % 10 + 1) / 10.0f;
	b = (rand() % 10 + 1) / 10.0f;

	glClearColor(r, g, b, 1.0);

	/* Tick */
	
	mCam.Tick(mScreen, deltaTime);

	glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);

	backdropSprite.Tick(rotationAngle, rotationAxisZ, mCam);

	cubeMap.Update();

	int diff = 0;

	for (size_t i = 0; i < bulletObjects.size() - diff; i++)
	{
		if (!bulletObjects.empty()) {
			bulletObjects.at(i)->Tick(deltaTime);
			if (bulletObjects.at(i)->deadLifeTime < bulletObjects.at(i)->time) {
				Console_OutputLog("Killing Instance Of Bullet", LOGINFO);
				diff++;
				std::vector<Bullet*> tmpBullets;

				for (size_t k = 0; k < bulletObjects.size(); k++)
				{
					if (k != i) {
						tmpBullets.push_back(bulletObjects.at(k));
					}
				}

				delete bulletObjects[i];
				bulletObjects.erase(bulletObjects.begin(), bulletObjects.end());
				bulletObjects.clear();

				for (size_t k = 0; k < tmpBullets.size(); k++) {
					if (k != i) {
						bulletObjects.push_back(tmpBullets.at(k));
					}
				}
				tmpBullets.clear();
			}
		}
		else {
			break;
		}
	}
	
	float rotationAngle = 0;

	/*
		===========
		[RENDERING]
		===========
	*/

	cubeMap.Render();
	

	// MAIN MENU

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.MAIN) {


		tankModel.position = glm::vec3(1.0f, 1.0f, 1.0f);

		for (size_t i = 0; i < menuSprites.size(); i++)
		{
			menuSprites.at(i)->Render();
		}

		backdropSprite.Render();

		for (size_t i = 0; i < mainModels.size(); i++)
		{
			mainModels.at(i)->Render();
		}
		mCam.SwitchMode(mCam.ORBIT, tankModel.position, glm::vec3(-5.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 5.0f, 5.0f);
		mainText.Render();
		highscoreText.SetText("Current Highscore: " + std::to_string(m_Game.highscore));
		highscoreText.Render();
	}

	// GAME

	else if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {
		//Update Text

		mWaveNum.SetText("Wave: " + std::to_string(m_Game.wave));
		mScore.SetText("Score: " + std::to_string(m_Game.score));
		mLivesText.SetText("Lives: " + std::to_string(m_Game.lives));

		mCam.SwitchMode(mCam.FOLLOW_STATIC, tankModel.position, glm::vec3(-10.0f, 15.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 5.0f, 5.0f);
		//Player Input

		MovementPacket PlayerInput = objManager.Move(objManager.PLAYER, 7.0f, mAudio, deltaTime, glm::vec4(-15.0f, 0.0f, 15.0f, 15.0f), tankModel.position, tankModel.rotationAngle, tankModel.position);

		tankModel.position = PlayerInput.newPosition;
		tankModel.rotationAngle = PlayerInput.newRotation;

		//Spawn Player Bullet

		if (PlayerInput.fire){
			bulletObjects.push_back(new Bullet(new Model("Resources/Models/PlayerShell/Dog 1.obj", &mCam, "Shell", rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), "Resources/3DObject_Diffuse.vs", "Resources/3DObject_BlinnPhong.fs"), deltaTime));
			bulletObjects.back()->isOnPlayerTeam = true;
			bulletObjects.back()->object->position = glm::vec3(tankModel.position.x, tankModel.position.y + 0.5f, tankModel.position.z);
			bulletObjects.back()->object->rotationAngle = tankModel.rotationAngle - 180;
		}

		for (size_t i = 0; i < bulletObjects.size(); i++)
		{
			bulletObjects.at(i)->object->Render();
		}

		for (size_t i = 0; i < mainModels.size(); i++)
		{
			mainModels.at(i)->Render();
		}

		//Bullet Position Update

		for (size_t i = 0; i < bulletObjects.size(); i++)
		{
			MovementPacket tmpBu = objManager.Move(objManager.BULLET, 10.0f, mAudio, deltaTime, glm::vec4(-15.0f, 0.0f, 15.0f, 15.0f), bulletObjects.at(i)->object->position, bulletObjects.at(i)->object->rotationAngle, tankModel.position);
			bulletObjects.at(i)->object->position = tmpBu.newPosition;
		}

		//Enemy Update

		float border = 2.0f;
		float Bulletborder = 1.0f;
		glm::vec4 playerCollider = glm::vec4(tankModel.position.x + border, tankModel.position.z + border, tankModel.position.x - border, tankModel.position.z - border); //perimeter of collider //top right bottom left

		for (size_t i = 0; i < enemyObjects.size(); i++)
		{
			enemyObjects.at(i)->object->Render();
			enemyObjects.at(i)->Tick(deltaTime);
			MovementPacket tmpE = objManager.Move(objManager.ENEMY, m_Game.enemyMoveSpeed, mAudio, deltaTime, glm::vec4(-15.0f, 0.0f, 15.0f, 15.0f), enemyObjects.at(i)->object->position, enemyObjects.at(i)->object->rotationAngle, tankModel.position);
			enemyObjects.at(i)->object->position = tmpE.newPosition;
			enemyObjects.at(i)->object->rotationAngle = tmpE.newRotation;

			//Collisons

			//Console_OutputLog("COLLIDER INFO\n[TOP:" + std::to_string(playerCollider.x) +"] [RIGHT: " + std::to_string(playerCollider.y) + "] [BOTTOM: " + std::to_string(playerCollider.z) + "] [LEFT: " + std::to_string(playerCollider.w) + "]\nME [X:" + std::to_string(enemyObjects.at(i)->object->position.x) + "] [Z: " + std::to_string(enemyObjects.at(i)->object->position.z) + "]",LOGINFO);

			//Hit Player
			if (((enemyObjects.at(i)->object->position.x > playerCollider.z) && (enemyObjects.at(i)->object->position.x < playerCollider.x)) && ((enemyObjects.at(i)->object->position.z > playerCollider.w) && (enemyObjects.at(i)->object->position.z < playerCollider.y))) {
				m_Game.lives -= 1;
				enemyObjects.at(i)->amAllowedAlive = false;
				mAudio.Play(mAudio.HIT);
			}

			//Hit Bullet

			for (size_t k = 0; k < bulletObjects.size(); k++)
			{
				glm::vec4 bulletCollider = glm::vec4(bulletObjects.at(k)->object->position.x + Bulletborder, bulletObjects.at(k)->object->position.z + Bulletborder, bulletObjects.at(k)->object->position.x - Bulletborder, bulletObjects.at(k)->object->position.z - Bulletborder); //perimeter of collider //top right bottom left
				if (((enemyObjects.at(i)->object->position.x > bulletCollider.z) && (enemyObjects.at(i)->object->position.x < bulletCollider.x)) && ((enemyObjects.at(i)->object->position.z > bulletCollider.w) && (enemyObjects.at(i)->object->position.z < bulletCollider.y))) {
					m_Game.score += 50;
					enemyObjects.at(i)->amAllowedAlive = false;
					bulletObjects.at(k)->deadLifeTime = 0.0f;
					mAudio.Play(mAudio.HIT);
				}
			}
		}

		//kill any enemies that are marked for death

		for (size_t i = 0; i < enemyObjects.size() - diff; i++)
		{
			if (!enemyObjects.empty()) {
				if (enemyObjects.size() >= i) {
					if (!enemyObjects.at(i)->amAllowedAlive) {
						Console_OutputLog("Killing Instance Of Enemy", LOGINFO);
						diff++;
						std::vector<Enemy*> tmpEnemies;

						for (size_t k = 0; k < enemyObjects.size(); k++)
						{
							if (k != i) {
								tmpEnemies.push_back(enemyObjects.at(k));
							}
						}

						delete enemyObjects[i];
						enemyObjects.erase(enemyObjects.begin(), enemyObjects.end());
						enemyObjects.clear();

						for (size_t k = 0; k < tmpEnemies.size(); k++) {
							if (k != i) {
								enemyObjects.push_back(tmpEnemies.at(k));
							}
						}
						tmpEnemies.erase(tmpEnemies.begin(), tmpEnemies.end());
						tmpEnemies.clear();
					}
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}

		// Render Text

		mScore.Render();
		mWaveNum.Render();
		mLivesText.Render();
	}

	// GAMEOVER

	else {

		
		for (size_t i = 0; i < enemyObjects.size(); i++)
		{
			delete enemyObjects[i];
		}
		enemyObjects.erase(enemyObjects.begin(), enemyObjects.end());
		enemyObjects.clear();
		
		//Render Text

		gameOverText.SetText("GAMEOVER\nSCORE: " + std::to_string(m_Game.score) + "\nPress c to continue");

		gameOverText.Render();
	}

	glutSwapBuffers();
}

void Update() {
	currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = ((currentTime - pasttime) * 0.001f);
	pasttime = currentTime;
	glutPostRedisplay();
	mAudio.Tick();
	m_Game.CheckGeneralInput(m_Game);
	if (m_Game.leave) {
		glutLeaveMainLoop();
	}
}

int main(int argc, char** argv) {
	
	try {
		Console_Banner();
		srand((unsigned int)time(NULL));

		Console_OutputLog("Initialising Game...", LOGINFO);

		m_Game.score = 0;
		m_Game.gameover = false;

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 50);
		glutInitWindowSize((int)mScreen.SCR_WIDTH, (int)mScreen.SCR_HEIGHT);

		glutCreateWindow("The Dev Forgot To Name Me");

		if (glewInit() != GLEW_OK) {
			Console_OutputLog("Glew INIT FAILED! The program cannot recover from this error", LOGFATAL);
			system("pause");
			exit(0);
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		if (!mAudio.AudioInit()) {
			Console_OutputLog("Audio Inialistation Failed!", LOGWARN);
		}

		glClearColor(1.0, 0.0, 0.0, 1.0);

		/*
			==============
			[ 3D OBJECTS ]
			==============
		*/

		tankModel = Model::Model("Resources/Models/Tank/Tank.obj", &mCam, "Tank", rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), "Resources/3DObject_Diffuse.vs", "Resources/3DObject_BlinnPhong.fs");
		mainModels.push_back(&tankModel);
		menuModels.push_back(&tankModel);

		/*
			============
			[ CUBEMAPS ]
			============
		*/

		cubeMap.Initalise(&mCam, "Resources/CubeMap/Witcher/", "Witcher Terrain Cube Map");

		/*
			===========
			[ SPRITES ]
		    ===========
		*/

		/* BACKGROUND */

		backdropSprite.Initalise(glm::vec3(1.0f, 1.0f, 5.0f), glm::vec3(2.0f, 2.0f, 2.0f), "Resources/back.png", "Resources/back.vs", "Resources/back.fs", backIndices, backVerts, "Backround Layer");

		//Assign to scenes

		menuSprites.push_back(&backdropSprite);

		
		glGenVertexArrays(1, &backdropSprite.VAO);
		glBindVertexArray(backdropSprite.VAO);

		glGenBuffers(1, &backdropSprite.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backdropSprite.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backIndices), backIndices, GL_STATIC_DRAW);

		glGenBuffers(1, &backdropSprite.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, backdropSprite.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(backVerts), backVerts, GL_STATIC_DRAW);

		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		/* CAMERA */

		mCam.initializeCamera();

		/* AUDIO */

		mAudio.Play(mAudio.AMBIENT);

		/* TEXT */
		mScore = TextLabel(mScreen, "SCORE: 0", "Resources/DIN1451.ttf", glm::vec2(-300.0f, 200.0f));
		mLivesText = TextLabel(mScreen, "LIVES: 3", "Resources/DIN1451.ttf", glm::vec2(-300.0f, 100.0f));
		mWaveNum = TextLabel(mScreen, "WAVE: 1", "Resources/DIN1451.ttf", glm::vec2(-300.0f, 150.0f));
		gameOverText = TextLabel(mScreen, "GAMEOVER\nSCORE: UNKNOWN\nPress c to continue", "Resources/DIN1451.ttf", glm::vec2(-300.0f, 200.0f));
		mainText = TextLabel(mScreen, "The Dev Forgot To Name Me\n1. Play\n2. Quit", "Resources/Arial.ttf", glm::vec2(-300.0f, 200.0f));
		highscoreText = TextLabel(mScreen, "Current Highscore: " + std::to_string(m_Game.highscore) , "Resources/Arial.ttf", glm::vec2(-300.0f, -200.0f));
		mScore.SetScale(static_cast<GLfloat>(0.65));
		mLivesText.SetScale(static_cast<GLfloat>(0.65));
		mWaveNum.SetScale(static_cast<GLfloat>(0.65));
		gameOverText.SetScale(static_cast<GLfloat>(0.75));
		mainText.SetScale(static_cast<GLfloat>(0.5));
		highscoreText.SetScale(static_cast<GLfloat>(0.5));

		m_Game.enemyList = &enemyObjects;
		m_Game.mCam = &mCam;

		glutDisplayFunc(Render);

		glutIdleFunc(Update);

		glutKeyboardFunc(Input::KeyboardDown);
		glutKeyboardUpFunc(Input::KeyboardUp);

		glutSpecialFunc(Input::specialCharDown);
		glutSpecialUpFunc(Input::specialCharUp);

		Console_OutputLog("Game Assets Initalised. Starting Game...", LOGINFO);

		glutMainLoop();
	}

	catch (...) {
		Console_OutputLog("Something went wrong and the application cannot recover\nError Code: Unknown", LOGFATAL);
		system("pause");
	}

	return 0;
}
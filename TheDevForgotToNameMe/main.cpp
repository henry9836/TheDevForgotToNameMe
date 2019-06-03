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

using namespace std;

//Classes

Camera m_Cam;
ScreenInfo m_Screen;
AudioSystem m_Audio;
TextLabel m_Score;
TextLabel m_GameOverText;
TextLabel m_MainText;
GameManager m_Game;
ObjectManager m_BabyObjManager;
ObjectManager m_FireObjManager;

Sprite babySprite;
Sprite fireSprite;
Sprite backdropSprite;

//Global Vars

float r = 1.0;
float b = 1.0;
float g = 1.0;

GLuint fireTexture = NULL;
GLuint babyTexture = NULL;
GLuint toasterTexture = NULL;
GLuint backgroundTexture = NULL;

GLuint firePro = NULL;
GLuint toasterPro = NULL;
GLuint babyPro = NULL;
GLuint backgroundPro = NULL;

GLuint fireVAO = NULL;
GLuint fireVBO = NULL;
GLuint fireEBO = NULL;
GLuint toasterVAO = NULL;
GLuint toasterVBO = NULL;
GLuint toasterEBO = NULL;
GLuint babyVAO = NULL;
GLuint babyVBO = NULL;
GLuint babyEBO = NULL;
GLuint backVAO = NULL;
GLuint backVBO = NULL;
GLuint backEBO = NULL;


glm::vec3 firePos = glm::vec3(0.1f, 0.1f, 0.0f);
glm::mat4 fireTransMat = glm::translate(glm::mat4(), firePos);
glm::vec3 rotZ = glm::vec3(0.0f, 0.0f, 1.0f);

float rotationAngle = 0;
float currentTime;
float deltaTime;
float pasttime;

bool BackTrackPlaying = false;
bool Babyisdying = false;

glm::mat4 fireRot = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotZ);

/* CAMERA */
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);


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

GLuint fireIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat fireVerts[] = {
	0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};

GLuint babyIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat babyVerts[] = {
	0.85f, 0.75f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.85f, 0.75f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.85f, -0.75f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.85f, -0.75f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};

GLuint hexIndices[] = {
	0, 1, 2,
	2, 3, 4,
	4, 5, 0,
	0, 2, 4,
};

GLfloat hexVerts[] = {
	0.7f, -0.9f, 0.0f,	1.0f, 0.0f, 0.0f, //bottom right	0
	0.85f, -0.7f, 0.0f,	1.0f, 0.0f, 1.0f, //right			1
	0.7f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, //top right		2
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, //top left		3
	0.35f, -0.7f, 0.0f,	1.0f, 1.0f, 0.0f, //left			4
	0.5f, -0.9f, 0.0f,	1.0f, 0.4f, 0.0f, //bottom left		5
};

GLuint quadIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat quadVerts[] = {
	0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};

void checkCollision(glm::vec4 box1, glm::vec4 box2)
{
	if ((box1.x > box2.x) && (box1.y < box2.x))
	{
		if ((box1.z < box2.z) && (box1.w > box2.z))
		{
			m_FireObjManager.ONTARGET = true;
		}
		if ((box1.z < box2.w) && (box1.w > box2.w))
		{
			m_FireObjManager.ONTARGET = true;
		}
	}
	if ((box1.x > box2.y) && (box1.y < box2.y))
	{
		if ((box1.z < box2.z) && (box1.w > box2.z))
		{
			m_FireObjManager.ONTARGET = true;
		}
		if ((box1.z < box2.w) && (box1.w > box2.w))
		{
			m_FireObjManager.ONTARGET = true;
		}
	}
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	r = (rand() % 10 + 1) / 10.0f;
	g = (rand() % 10 + 1) / 10.0f;
	b = (rand() % 10 + 1) / 10.0f;

	glClearColor(r, g, b, 1.0);

	/* CAMERA */

	m_Cam.calculate(m_Screen);

	/* Sprite Tick */

	glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);

	fireSprite.Tick(rotationAngle, rotationAxisZ, m_Cam);
	babySprite.Tick(rotationAngle, rotationAxisZ, m_Cam);
	backdropSprite.Tick(rotationAngle, rotationAxisZ, m_Cam);

	//MOVE OBJECTS

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {

		m_BabyObjManager.movement(m_Audio, deltaTime, m_Screen.SCR_WIDTH, m_Screen.SCR_HEIGHT, false);
		babySprite.position += m_BabyObjManager.objPos;

		m_FireObjManager.Target = babySprite.position;
		m_FireObjManager.movement(m_Audio, deltaTime, m_Screen.SCR_WIDTH, m_Screen.SCR_HEIGHT, true);
		fireSprite.position += m_FireObjManager.objPos;
	}

	float rotationAngle = 0;

	//CHECK COLLISIONS

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {
		glm::vec4 playerbox(m_BabyObjManager.objPos.y, babySprite.position.y - babySprite.scale.y, babySprite.position.x, babySprite.position.x + babySprite.scale.x); //up down left right
		glm::vec4 enemybox((fireSprite.position.y - 30), (fireSprite.position.y - 30) - (fireSprite.position.y - 30), (fireSprite.position.x - 30), (fireSprite.position.x - 30) + fireSprite.scale.x);
		checkCollision(playerbox, enemybox);
	}

	/* BACKROUND */

	backdropSprite.Render();

	if (!m_Game.gameover && m_Game.currentScreen == m_Game.MAIN) {
		m_MainText.Render();
	}

	else if (!m_Game.gameover && m_Game.currentScreen == m_Game.GAME) {

		/* BABY */

		babySprite.Render();

		/* FIRE */

		fireSprite.Render();

		/* TEXT */

		m_Score.Render();

	}

	else {
		m_GameOverText.Render();
	}

	glutSwapBuffers();
}

void Update() {
	currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = (currentTime - pasttime) * 0.1f;
	pasttime = currentTime;
	glutPostRedisplay();
	m_Audio.Tick();
	m_Game.CheckGeneralInput(m_Game);
}

int main(int argc, char** argv) {
	
	try {
		Console_Banner();
		srand((unsigned int)time(NULL));

		Console_OutputLog("Initializing Game...", LOGINFO);

		m_Game.score = 0;
		m_Game.gameover = false;

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100, 50);
		glutInitWindowSize((int)m_Screen.SCR_WIDTH, (int)m_Screen.SCR_HEIGHT);

		glutCreateWindow("The Dev Forgot To Name Me");

		if (glewInit() != GLEW_OK) {
			Console_OutputLog("Glew INIT FAILED! The program cannot recover from this error", LOGFATAL);
			system("pause");
		}

		if (!m_Audio.AudioInit()) {
			Console_OutputLog("Audio Inialistation Failed!", LOGWARN);
			system("pause");
		}

		glClearColor(1.0, 0.0, 0.0, 1.0);



		glGenTextures(1, &fireTexture);
		glBindTexture(GL_TEXTURE_2D, fireTexture);

		int width, height;

		/* FIRE */

		fireSprite.Initalise(glm::vec3(-150.0f, 0.0f, 0.0f), glm::vec3(90.0f, 90.0f, 90.0f), "Resources/fire.png", "Resources/fire.vs", "Resources/fire.fs", fireIndices, fireVerts, "fireSprite");

		glGenVertexArrays(1, &fireSprite.VAO);
		glBindVertexArray(fireSprite.VAO);

		glGenBuffers(1, &fireSprite.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fireSprite.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fireIndices), fireIndices, GL_STATIC_DRAW);

		glGenBuffers(1, &fireSprite.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, fireSprite.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(fireVerts), fireVerts, GL_STATIC_DRAW);

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



		/* BABY */

		babySprite.Initalise(glm::vec3(150.0f, 0.0f, 0.0f), glm::vec3(90.0f, 90.0f, 90.0f), "Resources/baby.png", "Resources/baby.vs", "Resources/baby.fs", babyIndices, babyVerts, "babySprite");

		glGenVertexArrays(1, &babySprite.VAO);
		glBindVertexArray(babySprite.VAO);

		glGenBuffers(1, &babySprite.EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, babySprite.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(babyIndices), babyIndices, GL_STATIC_DRAW);

		glGenBuffers(1, &babySprite.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, babySprite.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(babyVerts), babyVerts, GL_STATIC_DRAW);

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

		/* BACKGROUND */

		backdropSprite.Initalise(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(350.0f, 350.0f, 350.0f), "Resources/back.png", "Resources/back.vs", "Resources/back.fs", backIndices, backVerts, "Backround Layer");

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

		m_Cam.initializeCamera();

		/* AUDIO */

		m_Audio.Play(m_Audio.SPEECH);

		/* TEXT */
		m_Score = TextLabel(m_Screen, "SCORE: 0", "Resources/DIN1451.ttf", glm::vec2(-250.0f, 300.0f));
		m_GameOverText = TextLabel(m_Screen, "GAMEOVER", "Resources/DIN1451.ttf", glm::vec2(-240.0f, 300.0f));
		m_MainText = TextLabel(m_Screen, "Art\n-Henry Oliver\n\nMain Menu\n\nSelect a mode:\n1. Normal mode\n2. Lecturer/Easy mode", "Resources/Arial.ttf", glm::vec2(-240.0f, 300.0f));
		m_Score.SetScale(static_cast<GLfloat>(0.65));
		m_GameOverText.SetScale(static_cast<GLfloat>(0.5));
		m_MainText.SetScale(static_cast<GLfloat>(0.5));

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
		Console_OutputLog("Somethign went wrong when trying to lauch the game", LOGFATAL);
	}

	return 0;
}
#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <freeglut.h>
#include <iostream>
#include "ScreenInfo.h"

class Camera
{
public:
	void initializeCamera();
	void Tick(ScreenInfo m_Screen, float deltaTime);

	glm::mat4 getMVP(glm::vec3 postion, glm::vec3 scale, glm::mat4 rotationZ);

	glm::vec3 camPos;
	glm::vec3 camLookDir;
	glm::vec3 camUpDir;

	glm::mat4 rotMat;
	glm::vec4 newPos;

	glm::mat4 view;
	glm::vec3 camTar;
	glm::mat4 proj;

	float halfw = 0.0f;
	float halfh = 0.0f;
	float maxRenderDistance = 10000.0f;
	float minRenderDistance = 0.1f;
	float FOV = 90.0f;
	float timeElapsed = 0.0f;

	//Used for orbiting
	GLfloat radius = 1.0f;
	bool orbitCam = true;

	bool orthoMode = false;
};

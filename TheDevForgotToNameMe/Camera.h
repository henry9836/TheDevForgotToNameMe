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
	void calculate(ScreenInfo m_Screen);

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
};

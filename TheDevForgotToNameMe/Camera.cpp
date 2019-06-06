#include "Camera.h"
#include "ConsoleController.h"
#include "glm.hpp"
#include <iostream>
#include <freeglut.h>

void Camera::initializeCamera()
{
	Console_OutputLog("Initialising Camera...", LOGINFO);
	camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
	Console_OutputLog("Initialised Camera", LOGINFO);
}

void Camera::Tick(ScreenInfo m_Screen, float deltaTime)
{
	if (orbitCam) {
		timeElapsed += deltaTime;
		camPos.x = sin(timeElapsed) * radius;
		camPos.y = 1.5f;
		camPos.z = cos(timeElapsed) * radius;
		camTar = glm::vec3(0.0f, 0.0f, 0.0f);
		view = glm::lookAt(camPos, camTar, camUpDir);
		if (orthoMode) {
			halfw = (float)m_Screen.SCR_WIDTH * 0.5f;
			halfh = (float)m_Screen.SCR_HEIGHT * 0.5f;
			proj = glm::ortho(-halfw, halfw, -halfh, halfh, minRenderDistance, maxRenderDistance);
		}
		else {
			proj = glm::perspective(FOV / 2, (float)m_Screen.SCR_WIDTH / (float)m_Screen.SCR_HEIGHT, minRenderDistance, maxRenderDistance);
		}
	}
	else {
		newPos = glm::vec4(0, 0, 3, 1);
		camPos = glm::vec3(newPos);
		camTar = glm::vec3(0.0f, 0.0f, 0.0f);
		view = glm::lookAt(camPos, camTar, camUpDir);
		if (orthoMode) {
			halfw = (float)m_Screen.SCR_WIDTH * 0.5f;
			halfh = (float)m_Screen.SCR_HEIGHT * 0.5f;
			proj = glm::ortho(-halfw, halfw, -halfh, halfh, minRenderDistance, maxRenderDistance);
		}
		else {
			proj = glm::perspective(FOV / 2, (float)m_Screen.SCR_WIDTH / (float)m_Screen.SCR_HEIGHT, minRenderDistance, maxRenderDistance);
		}
	}

}

glm::mat4 Camera::getMVP(glm::vec3 postion, glm::vec3 scale, glm::mat4 rotationZ)
{
	glm::vec3 backObjPosition = postion;
	glm::mat4 backTranslationMatrix = glm::translate(glm::mat4(), backObjPosition);
	glm::vec3 objscaleBack = scale;
	glm::mat4 scaleMatrixBack = glm::scale(glm::mat4(), objscaleBack);
	glm::mat4 backModel = backTranslationMatrix * rotationZ * scaleMatrixBack;
	glm::mat4 backProj_calc = proj * view * backModel;
	return (backProj_calc);
}




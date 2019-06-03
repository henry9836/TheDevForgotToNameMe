#pragma once

#include <freeglut.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Audio.h"
#include "Input.h"


class ObjectManager
{
public:

	ObjectManager();
	~ObjectManager();
	void Reset();
	void movement(AudioSystem& audio2, GLfloat deltaTime, float ScreenW, float screenH, bool isEnemy);
	glm::vec3 objPos;
	glm::vec3 Target;
	const float speedBaby = 0.5f;
	const float speedFire = 0.1f;
	bool ONTARGET = false;
};
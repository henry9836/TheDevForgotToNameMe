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


class MovementPacket {
public:
	glm::vec3 newPosition;
	float newRotation;
};

class ObjectManager
{
public:
	enum OBJECTTYPE {
		PLAYER,
		ENEMY,
		BULLET
	};

	ObjectManager();
	~ObjectManager();
	void Reset();
	MovementPacket Move(OBJECTTYPE objType, float speed, AudioSystem& audio, GLfloat deltaTime, glm::vec2 maxWorldSize, glm::vec3 currentPos, float currentRotation);
	void movement(AudioSystem& audio2, GLfloat deltaTime, float ScreenW, float screenH, bool isEnemy);
	glm::vec3 objPos;
	glm::vec3 Target;
	const float speedBaby = 0.5f;
	const float speedFire = 0.1f;
	bool ONTARGET = false;
};
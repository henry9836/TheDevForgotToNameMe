#include "ObjectManager.h"

Input m_input;


ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Reset()
{
	objPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

MovementPacket ObjectManager::Move(OBJECTTYPE objType, float speed, AudioSystem& audio, GLfloat deltaTime, glm::vec2 maxWorldSize, glm::vec3 currentPos, float currentRotation) {
	
	MovementPacket currentState;
	
	currentState.newPosition = currentPos;
	currentState.newRotation = currentRotation;

	if (objType == PLAYER) {
		if (m_input.CheckKeyDown('w'))
		{
			currentState.newPosition.x += speed * deltaTime;
			currentState.newRotation = 270.0;
		}
		if (m_input.CheckKeyDown('s'))
		{
			currentState.newPosition.x -= speed * deltaTime;
			currentState.newRotation = 90.0f;
		}
		if (m_input.CheckKeyDown('a'))
		{
			currentState.newPosition.z -= speed * deltaTime;
			currentState.newRotation = 0.0f;
		}
		if (m_input.CheckKeyDown('d'))
		{
			currentState.newPosition.z += speed * deltaTime;
			currentState.newRotation = 180.0f;
		}
		/* OLD MOVEMENT */
		/*
		if (m_input.CheckKeyDown('w'))
		{
			currentState.newPosition.z -= speed * deltaTime;
		}
		if (m_input.CheckKeyDown('s'))
		{
			currentState.newPosition.z += speed * deltaTime;
		}
		if (m_input.CheckKeyDown('a'))
		{
			currentState.newPosition.x -= speed * deltaTime;
		}
		if (m_input.CheckKeyDown('d'))
		{
			currentState.newPosition.x += speed * deltaTime;
		}
		if (m_input.CheckKeyDown('q'))
		{
			currentState.newRotation += (speed * 5) * deltaTime;
		}
		if (m_input.CheckKeyDown('e'))
		{
			currentState.newRotation -= (speed * 5) * deltaTime;
		}
		*/
	}
	return currentState;
}

void ObjectManager::movement(AudioSystem& audio2, GLfloat deltaTime, float screenW, float screenH, bool isEnemy)
{
	glm::vec3 temp;
	temp = objPos;
	if (!isEnemy) {
		if (m_input.CheckKeyDown('w'))
		{

			if (temp.y < ((screenH - 100) / 2))
			{
				temp.y += speedBaby * deltaTime;
				objPos = temp;
			}

		}
		if (m_input.CheckKeyDown('a'))
		{
			if (temp.x > (0 - ((screenW + 240) / 2)))
			{
				temp.x -= speedBaby * deltaTime;
				objPos = temp;
			}
		}
		if (m_input.CheckKeyDown('s'))
		{
			if (temp.y > (0 - ((screenH - 100) / 2)))
			{
				temp.y -= speedBaby * deltaTime;
				objPos = temp;
			}
		}
		if (m_input.CheckKeyDown('d'))
		{
			if (temp.x < ((screenW - 450) / 2))
			{
				temp.x += speedBaby * deltaTime;
				objPos = temp;
			}
		}
	}
	else {
		if (objPos.x > (Target.x + 151)) {
			objPos.x -= speedFire * deltaTime;
			//go left
		}
		else if (objPos.x < (Target.x + 149)) {
			objPos.x += speedFire * deltaTime;
			//go right
		}
		if (objPos.y > Target.y) {
			objPos.y -= speedFire * deltaTime;
			//go down
		}
		else if (objPos.y < Target.y) {
			objPos.y += speedFire * deltaTime;
			//go up
		}
	}
}




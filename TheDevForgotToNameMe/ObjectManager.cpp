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




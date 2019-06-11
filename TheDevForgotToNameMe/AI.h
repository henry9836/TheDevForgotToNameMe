#pragma once

#include "3D.h"

class AIObject {
public:
	AIObject(Model* _Object) {
		this->object = _Object;
	};
	~AIObject() {
		delete this->object;
	};
	void Tick(float deltaTime) {

	};

	Model* object;
	bool amAllowedAlive = true;
	float moveSpeed = 5.0f;
};
#pragma once
#include <iostream>
#include <fmod.hpp>
#include "ConsoleController.h"

class AudioSystem {
public:

	bool AudioInit();
	void Play(int track);
	void Tick();

	enum Tracks {
		FIREBACK,
		BABYBACK,
		SPEECH,
		WON,
		LOST,
		BABYDIE,
		SHOOT,
		HIT,
		AMBIENT
	};

	FMOD::System* audioSystem;
	FMOD::Sound* fireBackTrack;
	FMOD::Sound* babyBackTrack;
	FMOD::Sound* speechTrack;
	FMOD::Sound* wonTrack;
	FMOD::Sound* lostTrack;
	FMOD::Sound* shoot;
	FMOD::Sound* hit;
	FMOD::Sound* ambient;
};
#include "Audio.h"

bool AudioSystem::AudioInit()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioSystem);
	if (result != FMOD_OK) {
		std::cout << "ERROR WITH INIT AUDIO" << std::endl;
		return false;
	}
	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK) {
		std::cout << "ERROR WITH INIT AUDIO" << std::endl;
		return false;
	}

	/* CREATE SOUNDS */

	result = audioSystem->createSound("Resources/BabyLoop.wav", FMOD_LOOP_NORMAL, 0, &babyBackTrack);
	if (result != FMOD_OK) {
		std::cout << "ERROR WITH INIT AUDIO: BABY LOOP" << std::endl;
		return false;
	}
	result = audioSystem->createSound("Resources/FireLoop.wav", FMOD_LOOP_NORMAL, 0, &fireBackTrack);
	if (result != FMOD_OK) {
		std::cout << "ERROR WITH INIT AUDIO: FIRE LOOP" << std::endl;
		return false;
	}
	result = audioSystem->createSound("Resources/about.wav", FMOD_DEFAULT, 0, &speechTrack);
	if (result != FMOD_OK) {
		std::cout << "ERROR WITH INIT AUDIO: SPEECH" << std::endl;
		return false;
	}
	result = audioSystem->createSound("Resources/Win.wav", FMOD_DEFAULT, 0, &wonTrack);
	if (result != FMOD_OK) {
		std::cout << "ERROR WITH INIT AUDIO: WON" << std::endl;
		return false;
	}
	result = audioSystem->createSound("Resources/Lose_Full.wav", FMOD_DEFAULT, 0, &lostTrack);
	if (result != FMOD_OK) {
		std::cout << "ERROR WITH INIT AUDIO: LOSE" << std::endl;
		return false;
	}

	return true;
}

void AudioSystem::Play(int track) {
	bool foundtrack = true;
	bool result = false;
	switch (track)
	{
	case BABYBACK: {
		result = audioSystem->playSound(babyBackTrack, 0, false, 0);
		break;
	}
	case FIREBACK: {
		result = audioSystem->playSound(fireBackTrack, 0, false, 0);
		break;
	}
	case SPEECH: {
		result = audioSystem->playSound(speechTrack, 0, false, 0);
		break;
	}
	case WON: {
		result = audioSystem->playSound(wonTrack, 0, false, 0);
		break;
	}
	case LOST: {
		result = audioSystem->playSound(lostTrack, 0, false, 0);
		break;
	}
	default: {
		foundtrack = false;
		std::cout << "Track " << track << " Doesn't Exist" << std::endl;
		break;
	}
	}

	if (foundtrack) {
		if (result != FMOD_OK) {
			std::cout << "ERROR WITH PLAYING AUDIO" << std::endl;
			return;
		}
	}
}

void AudioSystem::Tick()
{
	audioSystem->update();
}


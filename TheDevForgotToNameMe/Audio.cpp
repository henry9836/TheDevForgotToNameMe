#include "Audio.h"

bool AudioSystem::AudioInit()
{

	Console_OutputLog("Initalising Audio...", LOGINFO);

	FMOD_RESULT result;
	result = FMOD::System_Create(&audioSystem);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio FMOD_OK Check Failed!", LOGWARN);
		return false;
	}
	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio FMOD_OK Check Failed!", LOGWARN);
		return false;
	}

	/* CREATE SOUNDS */

	result = audioSystem->createSound("Resources/BabyLoop.wav", FMOD_LOOP_NORMAL, 0, &babyBackTrack);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track BabyLoop.wav", LOGWARN);
	}
	result = audioSystem->createSound("Resources/FireLoop.wav", FMOD_LOOP_NORMAL, 0, &fireBackTrack);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track FireLoop.wav", LOGWARN);
	}
	result = audioSystem->createSound("Resources/about.wav", FMOD_DEFAULT, 0, &speechTrack);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track about.wav", LOGWARN);
	}
	result = audioSystem->createSound("Resources/Win.wav", FMOD_DEFAULT, 0, &wonTrack);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track Win.wav", LOGWARN);
	}
	result = audioSystem->createSound("Resources/Lose_Full.wav", FMOD_DEFAULT, 0, &lostTrack);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track Lose_Full.wav", LOGWARN);
	}
	result = audioSystem->createSound("Resources/Sounds/shoot.wav", FMOD_DEFAULT, 0, &shoot);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track shoot.wav", LOGWARN);
	}
	result = audioSystem->createSound("Resources/Sounds/hit.wav", FMOD_DEFAULT, 0, &hit);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track hit.wav", LOGWARN);
	}
	result = audioSystem->createSound("Resources/Sounds/ambient.mp3", FMOD_LOOP_NORMAL, 0, &ambient);
	if (result != FMOD_OK) {
		Console_OutputLog("Cannot Initalise Audio Track ambient.mp3", LOGWARN);
	}

	Console_OutputLog("Initalised Audio...", LOGINFO);

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
	case SHOOT: {
		result = audioSystem->playSound(shoot, 0, false, 0);
		break;
	}
	case HIT: {
		result = audioSystem->playSound(hit, 0, false, 0);
		break;
	}
	case AMBIENT: {
		result = audioSystem->playSound(ambient, 0, false, 0);
		break;
	}
	default: {
		foundtrack = false;
		Console_OutputLog("Audio Track: " + std::to_string(track) + " was called but it doesn't exist", LOGWARN);
		break;
	}
	}

	if (foundtrack) {
		if (result != FMOD_OK) {
			Console_OutputLog("Audio Track: " + std::to_string(track) + " was called but cannot be played", LOGWARN);
			return;
		}
	}
}

void AudioSystem::Tick()
{
	audioSystem->update();
}


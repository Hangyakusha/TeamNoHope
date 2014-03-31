#include "SoundManager.h"
#include "Debug.h"

using namespace gg;

SoundManager::SoundManager() 
{
	init();
}

SoundManager::~SoundManager() 
{

}

void SoundManager::init()
{
	_device = alcOpenDevice(0);
	if(!_device)
		writeLog("Failed to open audio device!");

	writeLog("Audio device opened!!");

	_context = alcCreateContext(_device, 0);
	if(!alcMakeContextCurrent(_context))
	{
		writeLog("Failed to make context current!");
		checkAlError("alcMakeContextCurrent");
	}
}

void SoundManager::playSound(const Sound& sound)
{

}
#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <AL\al.h>
#include <AL\alc.h>

namespace NoHope
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

	private:
		
		static ALCdevice* device;
		static ALCcontext* context;

		static bool initialized;

		static void CreateContext();
	};
}

#endif
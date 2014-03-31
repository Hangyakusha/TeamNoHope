#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <AL/al.h>
#include <AL/alc.h>
#include "Sound.h"

namespace gg
{
	class SoundManager
	{
	public:

		SoundManager();
		~SoundManager();

		void init();
		void playSound(const Sound& sound);

	private:

		ALCdevice* _device;
		ALCcontext* _context;

	};
}

#endif
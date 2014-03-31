#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile/sndfile.h>

namespace gg
{
	class Sound
	{
	public:

		Sound(const std::string& fileName);
		Sound();
		~Sound();

		static Sound* load(const std::string& fileName);
		void play();

	private:

		Sound(Sound&);

		void init(const std::string& fileName);
		static void createContext();

		static ALCdevice* _device;
	 	static ALCcontext* _context;
		static bool _initialized;
		ALuint _source;
		ALuint _buffer;
		float* _data;

	};
}

#endif

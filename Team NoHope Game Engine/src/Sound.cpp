#include "Sound.h"
#include "Debug.h"
#include "Util.h"
#include "math.h"

//RESTRUCTURE
#include "sndfile/sndfile.h"

using namespace gg;

bool Sound::_initialized = false;
ALCdevice* Sound::_device = 0;
ALCcontext* Sound::_context = 0;

Sound::Sound(const std::string& fileName)
{
	init(fileName);
}

Sound::Sound()
{

}

Sound::~Sound()
{

}

Sound* Sound::load(const std::string& fileName)
{
	return new Sound(fileName);
}

void Sound::createContext()
{
	if(!_initialized)
	{
		_initialized = true;

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
}

void Sound::init(const std::string& fileName)
{
	Sound::createContext();

	//create _source
	alGenSources(1, &_source);
	checkAlError("alGen_sources");

	alSourcef(_source, AL_PITCH, 1);
	checkAlError("al_sourcef AL_PITCH");

	alSourcef(_source, AL_GAIN, 1);
	checkAlError("al_sourcef AL_GAIN");

	alSource3f(_source, AL_POSITION, 0, 0, 0);
	checkAlError("al_source3f AL_POSITION");

	alSource3f(_source, AL_VELOCITY, 0, 0, 0);
	checkAlError("al_source3f AL_VELOCITY");

	alSourcei(_source, AL_LOOPING, AL_TRUE);
	checkAlError("al_source3f AL_LOOPING");

	//create buffer
	alGenBuffers(1, &_buffer);
	checkAlError("alGenBuffers");

	//SOUNDFILE READING
	#ifdef __ANDROID__

		AAsset* asset = Util::loadSound(fileName);

		SF_VIRTUAL_IO virtualIO;
		virtualIO.get_filelen = &Util::getAssetLength;
		virtualIO.seek = &Util::seekAsset;
		virtualIO.read = &Util::readAsset;
		virtualIO.tell = &Util::tellAsset;

		SF_INFO soundInfo;
		SNDFILE* file = sf_open_virtual(&virtualIO, SFM_READ, &soundInfo, asset);

	#else

		SF_INFO soundInfo;
		SNDFILE* file = sf_open(fileName.c_str(), SFM_READ, &soundInfo);

	#endif

	if(!file)
	{
		int error = sf_error(file);
		writeLog("****** Failed to open sound file, error %d *******", file, error);
		writeLog(sf_error_number(error));
		return;
	}

	writeLog("frames: %d\n", soundInfo.frames);
	writeLog("samplerate: %d\n", soundInfo.samplerate);
	writeLog("channels: %d\n", soundInfo.channels);
	writeLog("format: %d\n", soundInfo.format);

	sf_count_t frames = soundInfo.frames * soundInfo.channels;

	short* data = new short[frames];

	sf_read_short(file, data, frames);

	writeLog("frames: %d\n", frames);

	alBufferData(_buffer, AL_FORMAT_STEREO16, data, frames * sizeof(short), soundInfo.samplerate);
	checkAlError("alBufferData");

	alSourcei(_source, AL_BUFFER, _buffer);
	checkAlError("alSourcei");

	sf_close(file);
}

void Sound::play()
{
	/*ALint state;
	alGetSourcei(_source, AL_SOURCE_STATE, &state);
	if(state != AL_PLAYING)*/
		alSourcePlay(_source);
}

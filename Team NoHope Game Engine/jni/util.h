#ifndef UTIL_H
#define UTIL_H

#include <Debug.h>
#include <stdlib.h>
#include <GL/opengl.h>
#include <string>

#ifdef __ANDROID__
#include "AssetManager.h"
#include <sndfile\sndfile.h>
#endif

namespace gg
{
	struct tgaHeader
	{
        GLubyte idLength;
        GLubyte colorMapType;
		GLubyte type;
		GLushort width;
		GLushort height;
		GLubyte depth;
		GLubyte descriptor;
	};

	class Util
	{
	public:

		static int randomRange(int low, int high)
		{
			return (rand() % (high - low)) + low; //does not include high
		}

		static float random()
		{
			return (rand() % 1000) / 1000.0f; //0..1
		}

		static float getTotalTime();

		static const std::string resourcePath;

		static std::string loadFile(const std::string& fileName);
		static GLubyte* loadTGA(const std::string& fileName, tgaHeader &header);

		#ifdef __ANDROID__

			static AAsset* loadSound(const std::string& fileName);

			static sf_count_t getAssetLength(void* asset);
			static sf_count_t seekAsset(sf_count_t offset, int whence, void* asset);
			static sf_count_t readAsset(void* buffer, sf_count_t count, void* asset);
			static sf_count_t tellAsset(void* asset);

		#else

			//static float* loadSound(const std::string& fileName, int& size);

		#endif

	};
}

#endif
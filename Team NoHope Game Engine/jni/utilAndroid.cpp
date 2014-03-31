#include "Util.h"
#include <ctime>
#include <string>
#include "AssetManager.h"
#include "android/input.h"

const std::string gg::Util::resourcePath = "";

float gg::Util::getTotalTime()
{
	static bool	initialized = false;
	static clock_t
		baseTime;
	
	if (!initialized)
	{
		baseTime = clock();
		initialized = true;
		return 0.0f;
	}

	float time = float(clock() - baseTime) / float(CLOCKS_PER_SEC);
	return time;
}

std::string gg::Util::loadFile(const std::string &fileName)
{
	//TODO: check for invalid filenames
	AAsset* asset = AAssetManager_open(gg::AssetManager::manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	off_t length = AAsset_getLength(asset);

	char* text = new char[length+1];
	if(AAsset_read(asset, text, length) < 1)
	{
		writeLog("File not loaded! Error! Error!");
	}

	text[length] = 0;

	AAsset_close(asset);
	text[length] = 0;
	std::string r(text);

	return r;
}

GLubyte* gg::Util::loadTGA(const std::string &fileName, tgaHeader &header)
{
	AAsset* asset = AAssetManager_open(gg::AssetManager::manager, fileName.c_str(), AASSET_MODE_UNKNOWN);

    AAsset_read(asset, &header.idLength, 1);
    AAsset_read(asset, &header.colorMapType, 1);
    AAsset_read(asset, &header.type, 1);
    AAsset_seek(asset, 9, SEEK_CUR);
    AAsset_read(asset, &header.width, 2);
    AAsset_read(asset, &header.height, 2);
    AAsset_read(asset, &header.depth, 1);
    AAsset_read(asset, &header.descriptor, 1);
    AAsset_seek(asset, header.idLength, SEEK_CUR);
    
	//writeLog("spritewidth: %d, height: %d, depth: %d", header.width, header.height, header.depth);

    //24bit / 8 = 3 (RGB), 32bit / 8 = 4 (RGBA)
    int componentCount = header.depth/8;
    
    int size = componentCount * header.width * header.height;
    GLubyte* data = new GLubyte[size];
    
    AAsset_read(asset, data, size);
    
    //data is now BGRA so we format it to RGBA
    for(int i = 0; i < size; i += componentCount)
    {
        GLubyte temp = data[i];
        
        //Switch red and blue
        data[i] = data[i+2];
        data[i+2] = temp;
    }
    
    AAsset_close(asset);

	return data;
}

AAsset* gg::Util::loadSound(const std::string& fileName)
{
	return AAssetManager_open(gg::AssetManager::manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
}

sf_count_t gg::Util::getAssetLength(void* asset)
{
	return AAsset_getLength((AAsset*)asset);
}

sf_count_t gg::Util::seekAsset(sf_count_t offset, int whence, void* asset)
{
	return AAsset_seek((AAsset*)asset, offset, whence);
}

sf_count_t gg::Util::readAsset(void* buffer, sf_count_t count, void* asset)
{
	return AAsset_read((AAsset*)asset, buffer, count);
}

sf_count_t gg::Util::tellAsset(void* asset)
{
	return AAsset_seek((AAsset*)asset, 0, SEEK_CUR);
}

//Provides filereading functionality under android.
//Hides FILE* reading under Windows.
// for Windows version of the file, see ../FileReader.cpp/.h

#include <FileReader.h>
#include "AssetManager.h"

using namespace gg;

FileReader::FileReader(const char* path)
{
	asset = AAssetManager_open(AssetManager::manager, path, 2);
	_length = AAsset_getLength(asset);
}

FileReader::~FileReader()
{
	AAsset_close(asset);
}

bool FileReader::seek(int offset, int relation)
{
	if(AAsset_seek(asset, offset, relation) != 1)
		return true;
	return false;
}

bool FileReader::read(unsigned int count, void*buffer)
{
	if(asset != NULL)
		if(AAsset_read(asset, buffer, count) >= 0)
			return true;
	return false;
}

unsigned int FileReader::length()
{
	return _length;
}
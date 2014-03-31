//Provides filereading functionality under Windows.
//Hides AssetManager* reading under Android.
// for Android version of the file, see jni/FileReader.cpp/.h

#include "FileReader.h"
#include "util.h"

using namespace NoHope;

FileReader::FileReader(const char* path)
{
	filePath = path;
	file = fopen(filePath.c_str(),"rb");

	if(!file)
	{
		writeLog("\n---------------\nFile opening failed! File not found?\n---------------\n");
		return;
	}

	fseek(file, 0, SEEK_END);
	_length = ftell(file);
	fseek(file, 0, SEEK_SET);
}

FileReader::~FileReader()
{
	fclose(file);
}
//Fseek = siirrä tiedoston pointteria offsetin verran relaatiosta poispäin
bool FileReader::seek(int offset, int relation)
{
	if(fseek(file, offset, relation) != 1)
		return true;
	return false;
}

bool FileReader::read(unsigned int count, void*buffer)
{
	if(file != NULL)
		if(fread(buffer, 1, count, file)==count)
			return true;
	return false;
}

unsigned int FileReader::length()
{
	return _length;
}
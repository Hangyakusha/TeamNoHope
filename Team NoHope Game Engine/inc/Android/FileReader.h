#ifndef FILEREADER_H
#define FILEREADER_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace gg
{
	class FileReader
	{

	public:

		FileReader(const char* path);
		~FileReader();
		
		bool seek(int offset,int relation);
		bool read(unsigned int count,void*buffer);
		unsigned int length();
		
	private:

		AAsset* asset;
		unsigned int _length;

	};	
}

#endif
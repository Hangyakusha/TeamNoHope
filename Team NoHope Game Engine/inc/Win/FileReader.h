#pragma once

#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>
#include <string>

namespace NoHope
{
	class FileReader
	{

	public:

		FileReader(const char* filePath);
		~FileReader();

		bool seek(int offset, int origin);
		bool read(unsigned int count, void* buffer);
		unsigned int length();

	private:

		FILE* file;
		std::string filePath;

		unsigned int _length;
	};
}

#endif
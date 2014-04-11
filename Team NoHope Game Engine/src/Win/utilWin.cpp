#include "Util.h"
//#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "sndfile/sndfile.h"
#include "GLFW/glfw3.h"

const std::string NoHope::Util::resourcePath = "../../../assets/";

float NoHope::Util::getTotalTime()
{
	return glfwGetTime();
}

std::string NoHope::Util::loadFile(const std::string& fileName)
{
	std::stringstream stream;
	std::ifstream file;
	file.open(fileName, std::ios::in);

	if(file.is_open())
	{
		stream << file.rdbuf();
		file.close();
		return stream.str();
	}
	else
	{
		writeLog("File not found!");
	}
	return "";
}

GLubyte* NoHope::Util::loadBinary(const std::string &fileName, int &fileSize)
{
	std::ifstream file;
	file.open(fileName, std::ios::binary|std::ios::ate);

	// get filesize
	fileSize = file.tellg();

	file.seekg (0, std::ios::beg);

	// make space for data
	GLubyte* data = new GLubyte[fileSize];

	// read to data
	file.read((char*)data, fileSize);

	file.close();

	return data;
}

GLubyte* NoHope::Util::loadTGA(const std::string &fileName, tgaHeader &header)
{
	std::ifstream file;
	file.open(fileName, std::ios::binary);

	file.read((char*)&header.idLength, 1);
	file.read((char*)&header.colorMapType, 1);
	file.read((char*)&header.type, 1);
	file.seekg(9, std::ios_base::cur);
	file.read((char*)&header.width, 2);
	file.read((char*)&header.height, 2);
	file.read((char*)&header.depth, 1);
	file.read((char*)&header.descriptor, 1);
	file.seekg(header.idLength, std::ios_base::cur);

	//24bit / 8 = 3 (RGB), 32bit / 8 = 4 (RGBA)
    int componentCount = header.depth/8;
    
    int size = componentCount * header.width * header.height;
    GLubyte* data = new GLubyte[size];
    
	file.read((char*)data, size);
    
    //data is now BGRA for some reason so we format it to RGBA
    for(int i = 0; i < size; i += componentCount)
    {
        GLubyte temp = data[i];
        
        //Switch red and blue
        data[i] = data[i+2];
        data[i+2] = temp;
    }
    
	file.close();

	return data;
}
/*
float* NoHope::Util::loadSound(const std::string& fileName, int& size)
{
	SF_INFO soundInfo;
	SNDFILE* file = sf_open(fileName.c_str(), SFM_READ, &soundInfo);

	if(!file)
	{
		writeLog("Failed to open sound file", file);
		return 0;
	}

	writeLog("frames: %d\n", soundInfo.frames);
	writeLog("samplerate: %d\n", soundInfo.samplerate);
	writeLog("channels: %d\n", soundInfo.channels);
	writeLog("format: %d\n", soundInfo.format);

	sf_count_t frames = soundInfo.frames * soundInfo.channels;
	size = frames;

	//float* data = new float[frames];
	float* data = new float[frames];

	sf_readf_float(file, data, frames);

	sf_close(file);

	return data;
}
*/
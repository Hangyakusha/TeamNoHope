#pragma once
#ifndef SHADER
#define SHADER

#include <OGLShader.h>


namespace NoHope
{
	class Shader : public OGLShader
	{
	public:
	Shader();
	~Shader();
	OGLShader* OGLShader;
	};
}

#endif
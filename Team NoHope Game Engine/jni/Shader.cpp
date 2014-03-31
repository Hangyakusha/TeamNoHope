#include "Debug.h"
#include "Shader.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace gg;

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath):
	_program(0),
	_vertexShader(0),
	_fragmentShader(0),
	_vertexFilePath(vertexFilePath),
	_fragmentFilePath(fragmentFilePath),
	_inUse(false)
{
	init();
}

Shader::~Shader() {}

bool Shader::init()
{
	createProgram();
	return true;
}

GLuint Shader::getUniformLocation(const char* name) const
{
	glUseProgram(_program);
	GLuint location = glGetUniformLocation(_program, name);
	checkGlError("Shader:getUniformLocation");
	return location;
}

void Shader::setUniform(const char* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
	checkGlError("Shader:SetUniformLocation");
}

void Shader::setUniform(const char* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
	checkGlError("Shader:SetUniformLocation");
}

void Shader::setUniform(const char* name, const float* matrixData)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrixData);
	checkGlError("Shader:SetUniformLocation");
}

GLuint Shader::program() const
{
	return _program;
}

GLuint Shader::loadShader(GLenum shaderType, const char* source) 
{
	GLuint shader = glCreateShader(shaderType);
	if (shader) 
	{
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) 
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				char* buf = (char*) malloc(infoLen);
				if (buf) 
				{
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					writeLog("Could not compile shader %d:\n%s\n",
					        shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}

void Shader::createProgram() 
{
	_vertexShader = loadShader(GL_VERTEX_SHADER, Util::loadFile(_vertexFilePath).c_str());
	if (!_vertexShader) 
	{
		writeLog("vertexshader failed!");
		return;
	}

	_fragmentShader = loadShader(GL_FRAGMENT_SHADER, Util::loadFile(_fragmentFilePath).c_str());
	if (!_fragmentShader) 
	{
		writeLog("fragmentshader failed!");
		return;
	}

	_program = glCreateProgram();
	checkGlError("glCreateProgram");

	if (_program) 
	{
		glAttachShader(_program, _vertexShader);
		checkGlError("glAttachShader");
		glAttachShader(_program, _fragmentShader);
		checkGlError("glAttachShader");

		glLinkProgram(_program);
		GLint linkStatus = GL_FALSE;

		glGetProgramiv(_program, GL_LINK_STATUS, &linkStatus);

		if (linkStatus != GL_TRUE) 
		{
			writeLog("Could not link program");
			GLint bufLength = 0;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) 
			{
				char* buf = (char*) malloc(bufLength);
				if (buf) 
				{
					glGetProgramInfoLog(_program, bufLength, NULL, buf);
					writeLog("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(_program);
			_program = 0;
		}
	}
}
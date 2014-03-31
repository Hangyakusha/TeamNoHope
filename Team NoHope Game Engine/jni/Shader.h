#ifndef SHADER_H
#define SHADER_H

#include "GL/opengl.h"
#include <string>
#include "math/Mat3.h"

namespace gg
{
	class Shader
	{
	public:
	
		Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
		~Shader();
	
		bool init();
		GLuint getUniformLocation(const char* name) const;
		void setUniform(const char* name, float value);
		void setUniform(const char* name, int value);
		void setUniform(const char* name, const float* matrixData);
		GLuint program() const;
	
	private:
	
		GLuint loadShader(GLenum shaderType, const char* source);
		void createProgram();
	
		std::string _vertexFilePath;
		std::string _fragmentFilePath;
		GLuint _program;
		GLuint _vertexShader;
		GLuint _fragmentShader;
		bool _inUse;
	};
}

#endif
#pragma once
#ifndef OGLSHADER
#define OGLSHADER

#include <Win32toAndroid.h>
#include <stdlib.h>

#include <Debug.h>
#include <FileReader.h>

namespace NoHope
{
	class OGLShader
	{
	public:
		OGLShader();
		~OGLShader();
		
		GLuint CreateShader(const char* fragPath, const char* vertPath);
	
	/*private:*/
		OGLShader(const OGLShader&);

		GLuint ReadShaderFile(const char* path, GLenum type);
		GLuint CreateProgram(GLuint VS, GLuint PS);
		bool FrmLinkShaderProgram( GLuint Program );
	
		GLuint LoadShader(GLenum shaderType, const char* pSource);
	};
}
#endif
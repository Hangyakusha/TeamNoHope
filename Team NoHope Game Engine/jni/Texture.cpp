#include "Debug.h"
#include "Texture.h"
#include "util.h"

#include <stdio.h>

#include <GL/opengl.h>

using namespace gg;

Texture::Texture(GLubyte* data, int width, int height, int depth):
	_data(data),
	_width(width),
	_height(height),
    _depth(depth)
{
	init();
}

Texture::Texture(GLubyte* data):
	_data(data),
	_width(10),
	_height(10)
{
	init();
}

Texture::~Texture()
{
	glDeleteTextures(1, &_textureId);
	delete[] _data;
}

void Texture::init()
{
    int format = _depth == 24 ? GL_RGB : GL_RGBA;
    
	glGenTextures(1, &_textureId);
	checkGlError("glGenTextures");

	glBindTexture(GL_TEXTURE_2D, _textureId);
	checkGlError("glBindTextures");

	glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, _data);
	checkGlError("glTexImage");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	checkGlError("glTexParameteri");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	checkGlError("glTexParameteri");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	checkGlError("glTexParameteri");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	checkGlError("glTexParameteri");

	glBindTexture(GL_TEXTURE_2D, 0);
	checkGlError("glBindTexture: 0");
}

void Texture::bind(gg::Shader *shader)
{
	glActiveTexture(GL_TEXTURE0);
	checkGlError("glACtiveTexture");

	glBindTexture(GL_TEXTURE_2D, _textureId);
	checkGlError("glBindTextures");

	shader->setUniform("vSampler", 0);
}

GLuint Texture::getTextureObject() const
{
	return _textureId;
}

Texture* Texture::load(const std::string &fileName)
{
	tgaHeader header;
	GLubyte* data = Util::loadTGA(fileName, header);
	writeLog("\ntexturesize: %d\n", sizeof(data));
	return new Texture(data, header.width, header.height, header.depth);
}

Texture* Texture::generateRandom(Vec2& size)
{
	const int length = size.x * size.y * 4;
	GLubyte* pixelData = new GLubyte[length];
	for(int i = 0; i < length; i++)
	{
		pixelData[i] = Util::randomRange(0, 255);
	}
	return new Texture(pixelData, (int)size.x, (int)size.y, 24);
}
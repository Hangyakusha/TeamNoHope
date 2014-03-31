#include "Debug.h"
#include "SpriteEntity.h"
#include "Graphics.h"
#include "Util.h"
#include <vector>

using namespace gg;

SpriteEntity::SpriteEntity(int x, int y, int width, int height, Texture* texture, Shader *shader):
	_shader(shader),
	_texture(texture)
{	
	init(x, y, width, height, Color(1.0f, 1.0f, 1.0f, 1.0f));
}

SpriteEntity::SpriteEntity(int x, int y, int width, int height, const Color& color, Shader *shader):
	_shader(shader),
	_texture(0)
{
	init(x, y, width, height, color);
}

SpriteEntity::~SpriteEntity() 
{
	delete _texture;
	delete _vertexData;
}

void SpriteEntity::init(int x, int y, int width, int height, const Color& color)
{
	setPosition(Vec2(x, y));

	std::vector<GLfloat> data(32);

	data[0] = -width / 2.0f;		data[1] = height / 2.0f; 
	data[8] = data[0];				data[9] = data[1] - height;
	data[16] = data[0] + width;		data[17] = data[1];
	data[24] = data[0] + width;		data[25] = data[1] - height;

	for(int i = 2; i < 32; i += 8)
	{
		data[i] = color.red;
		data[i+1] = color.green;
		data[i+2] = color.blue;
		data[i+3] = 1.0f;
	}

	data[6] = 0.0f;		data[7] = 1.0f;
	data[14] = 0.0f;	data[15] = 0.0f;
	data[22] = 1.0f;	data[23] = 1.0f;
	data[30] = 1.0f;	data[31] = 0.0f;

	_vertexData = new VertexData(data);

	const GLushort iData[] = { 0, 1, 2, 2, 1, 3 };
	std::vector<GLushort> indexData(iData, iData+6);

	_indexData = new IndexData(indexData);
}

void SpriteEntity::setColor(const Color& color)
{
	GLfloat colors[] = { color.red, color.green, color.blue, color.alpha };
	for(int i = 2; i < 32; i += 8)
	{
		_vertexData->setData(GL_ARRAY_BUFFER, sizeof(GLfloat)*i, sizeof(GLfloat)*4, colors);
	}
}

void SpriteEntity::draw()
{
	glUseProgram(_shader->program());

	if (_texture)
		_texture->bind(_shader);

	_shader->setUniform("projection", _projectionMatrix.data());
	_shader->setUniform("model", getMatrix().data());
	
	static const int stride = sizeof(GLfloat)*8;

	_vertexData->bindBuffers();
	_indexData->bindBuffers();

	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "position"), 2, stride, 0); //vertex positions
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "color"), 4, stride, sizeof(GLfloat)*2); //color
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "texCoords"), 2, stride, sizeof(GLfloat)*6); //texture coordinates

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawElements");
}

void SpriteEntity::update(float dt)
{
}
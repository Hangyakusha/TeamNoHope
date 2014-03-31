#include "VertexData.h"
#include "Debug.h"

using namespace gg;

VertexData::VertexData(std::vector<GLfloat> &data):
	_data(data)
{
	init();
}

VertexData::VertexData(std::vector<Vec3> &data)
{
	for(int i = 0; i < data.size(); i++)
	{
		_data.push_back(data[i].x);
		_data.push_back(data[i].y);
		_data.push_back(data[i].z);
	}

	init();
}

VertexData::VertexData(std::vector<Vec2> &data)
{
	for(int i = 0; i < data.size(); i++)
	{
		_data.push_back(data[i].x);
		_data.push_back(data[i].y);
	}

	init();
}

VertexData::~VertexData() 
{
}

void VertexData::bindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	checkGlError("Bindbuffer");
}

void VertexData::setAttribute(int location, int components, int stride, int offset)
{
	bindBuffers();

	glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    checkGlError("glVertexAttribPointer");

    glEnableVertexAttribArray(location);
    checkGlError("glEnableVertexAttribArray");
}

void VertexData::setData(int target, unsigned int offset, unsigned int size, void* data)
{
	bindBuffers();

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	checkGlError("glBufferSubData");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkGlError("unbindBuffer");
}

std::vector<GLfloat>& VertexData::getData()
{
	return _data;
}

void VertexData::init()
{
	//_data.shrink_to_fit();

	glGenBuffers(1, &_vertexBufferObject);
	checkGlError("glGenBuffers vbo");

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	checkGlError("glBindBuffer vbo");

	glBufferData(GL_ARRAY_BUFFER, _data.size()*sizeof(GLfloat), &_data[0], GL_DYNAMIC_DRAW);
	checkGlError("glBufferData");
}
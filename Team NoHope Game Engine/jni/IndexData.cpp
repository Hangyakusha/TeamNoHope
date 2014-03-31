#include "IndexData.h"
#include "Debug.h"

using namespace gg;

IndexData::IndexData(std::vector<GLushort> &data):
	_data(data)
{
	init();
}

IndexData::~IndexData() 
{
}

void IndexData::bindBuffers()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	checkGlError("Bind index buffer");
}

std::vector<GLushort>& IndexData::getData()
{
	return _data;
}

void IndexData::init()
{
	//const GLubyte indexData[] = { 0, 1, 2, 2, 1, 3 };
	//_data.shrink_to_fit();

	glGenBuffers(1, &_indexBuffer);
	checkGlError("glGenBuffers");

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	checkGlError("glBindBuffer");

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size()*sizeof(GLushort), &_data[0], GL_STATIC_DRAW);
	checkGlError("glBufferData");
}
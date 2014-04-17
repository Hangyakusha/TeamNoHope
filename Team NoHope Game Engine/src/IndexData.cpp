#include "IndexData.h"
#include "Debug.h"

using namespace NoHope;

IndexData::IndexData(std::vector<GLushort> &data, bool StaticArray):
	_data(data)
{
	init(StaticArray);
}

IndexData::~IndexData() 
{
}

void IndexData::bindBuffers()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	checkGlError("Bind index buffer");
}

void IndexData::SetIndexes(std::vector<GLushort> indexes)
{
	if (_data.size()>0)
		_data.clear();
	_data.reserve(indexes.size());

	for (int i = 0; i < indexes.size(); ++i)
		_data.push_back(indexes[i]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	checkGlError("glBindBuffer");

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size()*sizeof(GLushort), &_data[0], GL_DYNAMIC_DRAW);
	checkGlError("glBufferData");
}

std::vector<GLushort>& IndexData::getData()
{
	return _data;
}

void IndexData::init(bool StaticArray)
{
	//const GLubyte indexData[] = { 0, 1, 2, 2, 1, 3 };
	//_data.shrink_to_fit();

	glGenBuffers(1, &_indexBuffer);
	checkGlError("glGenBuffers");

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	checkGlError("glBindBuffer");

	if (StaticArray)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size()*sizeof(GLushort), &_data[0], GL_STATIC_DRAW);
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size()*sizeof(GLushort), &_data[0], GL_DYNAMIC_DRAW);

	checkGlError("glBufferData");
}
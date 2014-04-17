#pragma once

#ifndef INDEXDATA_H
#define INDEXDATA_H

#include "GL/opengl.h"
#include <vector>

namespace NoHope
{
	class IndexData
	{
	public:
		
		IndexData(std::vector<GLushort> &data, bool StaticArray = true);
		~IndexData();

		void bindBuffers();
		std::vector<GLushort>& getData();

		void SetIndexes(std::vector<GLushort> indexes);

	private:

		IndexData(IndexData&);
		void init(bool StaticArray);

		GLuint _indexBuffer;
		std::vector<GLushort> _data;
	};
}

#endif
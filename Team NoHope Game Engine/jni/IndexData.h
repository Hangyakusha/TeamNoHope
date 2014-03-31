#ifndef INDEXDATA_H
#define INDEXDATA_H

#include "GL/opengl.h"
#include <vector>

namespace gg
{
	class IndexData
	{
	public:

		IndexData(std::vector<GLushort> &data);
		~IndexData();

		void bindBuffers();
		std::vector<GLushort>& getData();

	private:

		IndexData(IndexData&);
		void init();

		GLuint _indexBuffer;
		std::vector<GLushort> _data;
	};
}

#endif
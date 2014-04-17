#pragma once

#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include "GL/opengl.h"
#include <vector>
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace NoHope
{
	class VertexData
	{
	public:
		
		VertexData(std::vector<GLfloat> &data);
		VertexData(std::vector<Vec3> &data);
		VertexData(std::vector<Vec2> &data);
		~VertexData();

		void bindBuffers();
		void setAttribute(int location, int components, int stride, int offset);
		void setData(int target, unsigned int offset, unsigned int size, void* data);
		std::vector<GLfloat>& getData();
		
		void SetNewData(std::vector<Vec2> &pos, std::vector<Vec4> &color, std::vector<Vec2> &texCoords);

	private:

		void init();

		GLuint _vertexBufferObject;
		std::vector<GLfloat> _data;
	};
}

#endif
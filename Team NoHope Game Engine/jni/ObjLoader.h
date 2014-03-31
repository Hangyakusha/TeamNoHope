#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Debug.h>
#include "GL/opengl.h"

#include "math/Vec3.h"
#include "math/Vec2.h"

namespace gg 
{
	class ObjLoader
	{

	public:

		ObjLoader();
		~ObjLoader();

		bool loadOBJ(const char* path, std::vector<Vec3> & out_vertices,
									   std::vector<Vec2> & out_uvs,
									   std::vector<Vec3> & out_normals,
									   std::vector<GLushort>& out_indices);
	private:

		ObjLoader(ObjLoader&);

		void openFile(const char* path);
		void parseData();
		void addVertices(const size_t bufferIndex);
		void addUvs(const size_t bufferIndex);
		void addNormals(const size_t bufferIndex);
		void addIndices(const size_t bufferIndex);

		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<Vec3> temp_vertices;
		std::vector<Vec2> temp_uvs;
		std::vector<Vec3> temp_normals;

		long lenght;
		char *buff;

		std::vector<std::string> _tokens;

	};
}
#endif
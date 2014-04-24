#pragma once

#ifndef MESH_H
#define MESH_H

#include "Entity.h"
#include "Shader.h"
#include "Texture.h"
#include "GL/opengl.h"
#include "VertexData.h"
#include "IndexData.h"
#include "Camera.h"
#include <string>
#include "Texture.h"

namespace NoHope
{
	class Mesh : public Entity
	{

	public:

		Mesh(Shader* shader, std::string filePath, Texture* texture);
		~Mesh();

		virtual void draw(Camera &_camera);
		virtual void update(float dt);

	private:

		void init(std::string filePath);

		Texture* _texture;
		VertexData* _vertexData;
		VertexData* _uvData;
		IndexData* _indexData;
		Shader* _shader;
		unsigned int size;
		Camera* _camera;

	};
}

#endif
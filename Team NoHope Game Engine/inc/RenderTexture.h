#pragma once

#ifndef RENDERTEXTURE_H
#define RENDERTEXTURE_H

#include "GL/opengl.h"
#include "Texture.h"
#include "SpriteEntity.h"
#include "Entity.h"
#include "Shader.h"
#include "VertexData.h"
#include "Color.h"
#include "Camera.h"

namespace NoHope
{
	class RenderTexture
	{
	public:

		RenderTexture();
		~RenderTexture();

		void draw(Entity& entity, Camera &_camera);
		void display();
		void clear(const Color& color);

	private:

		void init();
		void bind();
		void unBind();

		bool _bound;
		GLuint _frameBufferId;
		GLuint _depthBufferId;
		GLuint _stencilBufferId;
		Texture* _texture;
		VertexData* _vertexData;
		Shader* _shader;

		std::vector<GLfloat> _data;
		VertexData* _batchData;
		Texture* _batchTexture;
		Shader* _batchShader;
	};
}

#endif


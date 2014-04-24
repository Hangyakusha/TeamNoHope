#pragma once

#ifndef SPRITEENTITY_H
#define SPRITEENTITY_H

#include "Shader.h"
#include "Texture.h"
#include "GL/opengl.h"
#include "VertexData.h"
#include "IndexData.h"
#include "Entity.h"
#include "Color.h"

namespace NoHope 
{
	class SpriteEntity : public Entity
	{
	public:
	
		SpriteEntity(int x, int y, int width, int height, Texture* texture, Shader *shader);
		SpriteEntity(int x, int y, int width, int height, const Color& color, Shader *shader);
		~SpriteEntity();

		void setColor(const Color& color);
		void setVertexData(VertexData* vertexData);

		virtual void draw(Camera &_camera);
		virtual void update(float dt);
	
	private:
	
		void init(int x, int y, int width, int height, const Color& color);

		VertexData* _vertexData;
		IndexData* _indexData;
		Shader* _shader;
		Texture* _texture;

	};
}
#endif
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/opengl.h>
#include "Shader.h"
#include "math/Vec2.h"

namespace NoHope
{
	class Texture
	{
	public:

		Texture(GLubyte* data, int width, int height, int depth);
		Texture(GLubyte* data);
		~Texture();

		void bind(NoHope::Shader* shader);
		GLuint getTextureObject() const;

		static Texture* generateRandom(Vec2& size);
		static Texture* load(const std::string &fileName);
		static Texture* generateBlank();
		static Texture* blank;

		Vec2 getSize() const;

	private:

		void init();

		GLubyte* _data;
		GLuint _textureId;
        
		int _width;
		int _height;
        int _depth;
	};
}

#endif
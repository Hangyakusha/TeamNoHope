#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include "GL/opengl.h"
#include "Texture.h"
#include "Entity.h"
#include "Shader.h"
#include "VertexData.h"
#include "Color.h"

namespace gg
{
	class RenderView
	{
	public:

		RenderView();
		~RenderView();

		void draw(Entity& entity);
		void display();
		void clear(const Color& color);

		Shader* _shader;

	private:

		void init();
		void bind();
		void unBind();

		bool _bound;
	};
}

#endif


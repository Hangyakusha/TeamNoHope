#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include "Engine.h"
#include "math/Vec2.h"
#include "Shader.h"
#include <vector>

namespace gg
{
	class Scene : public Entity
	{
	friend class Engine;
	public:

		Scene();
		~Scene();

		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual void init() = 0;
		
		void setShader(Shader& shader);
		
	protected:

		Scene* parentScene;
		Engine* engine;

	private:

		Shader* _shader;

	};
}

#endif
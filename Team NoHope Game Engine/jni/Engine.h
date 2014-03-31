#ifndef ENGINE_H
#define ENGINE_H

#include "Scene.h"
#include "Graphics.h"
#include "Window.h"

namespace gg
{
	class Scene;

	class Engine
	{
	
	public:

		Engine(int width, int height);
		~Engine();

		void display(Scene& scene);

		//void started();
		//virtual void lostFocus() = 0;
		//virtual void gainedFocus() = 0;
		//virtual void closed() = 0;

	protected:

		Scene* currentScene;

	private:

		Engine(Engine&);
		void run();

		Graphics* _graphics;
		Window* _window;
	};
}

#endif
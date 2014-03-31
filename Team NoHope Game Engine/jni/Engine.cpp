#include "Engine.h"
#include "util.h"

using namespace gg;

Engine::Engine(int width, int height)
{
	_graphics = new Graphics(width, height);
}

Engine::~Engine()
{

}

void Engine::display(Scene& scene)
{
	scene.init();
	scene.engine = this;
	scene.parentScene = currentScene;
	this->currentScene = &scene;
	this->run();
}

void Engine::run()
{
	float dt = 0.0f;
	float oldTime = 0.0f;
	float newTime = 0.0f;

	while(_window->isOpen())
	{
		oldTime = newTime;
		newTime = gg::Util::getTotalTime();
		dt = newTime - oldTime;

		currentScene->update(dt);

		_graphics->clear(0, 0, 0);
		currentScene->draw();

        _window->pollEvents(currentScene);
	}
}




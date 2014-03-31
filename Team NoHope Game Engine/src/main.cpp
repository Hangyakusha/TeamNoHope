#include "Game.h"
#include "Window.h"
#include "Util.h"

int main()
{
	NoHope::Window* window = new NoHope::Window(640, 480, "NoHope");
	Game* game = new Game(640, 480);
	float dt = 0.0f;
	float oldTime = 0.0f;
	float newTime = 0.0f;

	while (window->isOpen())
	{
		oldTime = newTime;
		newTime = NoHope::Util::getTotalTime();
		dt = newTime - oldTime;
	
		game->update(dt);
		game->render();
		window->pollEvents();
	}
}

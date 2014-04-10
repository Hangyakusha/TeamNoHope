#include "Game.h"
#include "Window.h"
#include "Util.h"

int main()
{
	NoHope::Window* window = new NoHope::Window(1280, 720, "NoHope");
	Game* game = new Game(1280, 720);  //pelialueen koko t:Jesse
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

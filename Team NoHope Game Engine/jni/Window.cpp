#include "Window.h"

#define GLEW_STATIC
#include <GL/opengl.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "Util.h"

#include <stdio.h>

using namespace gg;

Window::Window(int width, int height, const char* title):
	_width(width),
	_height(height),
	_title(title) 
{
	init();	
}

Window::~Window() {}

void Window::init()
{
    /* Initialize the library */
    if (!glfwInit())
        return;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	
    if (!window)
    {
        glfwTerminate();
        return; 
    }

	//glfwSetKeyCallback(window, keyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	Game* game = new Game(1280, 720);
	float dt = 0.0f;
	float oldTime = 0.0f;
	float newTime = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		oldTime = newTime;
		newTime = gg::Util::getTotalTime();
		dt = newTime - oldTime;

		game->update(dt);
		game->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Window::pollEvents()
{

}

bool Window::isOpen()
{
    return true;
}
#include "Window.h"
#include "Util.h"

#include <stdio.h>

using namespace NoHope;

GLFWwindow* Window::window = 0;

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

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 0);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(_width, _height, "NoHope", NULL, NULL);
	
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

	//init fonts
	//Font::initFontLibrary();
}

void Window::close()
{
	glfwTerminate();
}

void Window::pollEvents()
{
	glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}

int Window::getKey(int key)
{
	return glfwGetKey(window, key);
}
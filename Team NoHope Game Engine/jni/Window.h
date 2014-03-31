#ifndef WINDOW_H
#define WINDOW_H

#define GLEW_STATIC
#include <GL/opengl.h>
#include <GLFW/glfw3.h>

namespace gg
{
    class Window
    {
    public:
        
        Window(int width, int height, const char* title);
        ~Window();
		bool isOpen();
		void pollEvents();
		void close();

		static int getKey(int key);
        
    private:
        
		void init();

		static GLFWwindow* window;
		int _width;
		int _height;
		const char* _title;

    };
}
#endif

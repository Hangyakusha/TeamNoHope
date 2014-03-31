#ifndef EGLWINDOW_H
#define EGLWINDOW_H

#include "Scene.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <android/sensor.h>
#include <android_native_app_glue.h>

namespace gg
{
    class EGLWindow
    {
    public:
        
        EGLWindow(int width, int height, const char* title);
        ~EGLWindow();
		bool isOpen();
		void pollEvents(Scene& scene);
		void close();

		static int getKey(int key);
        
		struct saved_state 
		{
			float angle;
			int32_t x;
			int32_t y;
		};
		
    private:
        
		void init();

		int _width;
		int _height;
		const char* _title;
		
		struct android_app* app;
		
		ASensorManager* sensorManager;
		const ASensor* accelerometerSensor;
		ASensorEventQueue* sensorEventQueue;

		int animating;
		EGLDisplay display;
		EGLSurface surface;
		EGLContext context;
		struct saved_state state;

    };
}
#endif

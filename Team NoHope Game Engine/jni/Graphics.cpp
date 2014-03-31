#include "Debug.h"
#include "Graphics.h"
#include "Util.h"
#include <GL/opengl.h>

using namespace gg;

int Graphics::screenHeight = 0;
int Graphics::screenWidth = 0;
float Graphics::aspectRatio = 0;

Graphics::Graphics(int width, int height)
{
	screenHeight = height;
    screenWidth = width;
	aspectRatio = screenWidth / (float)screenHeight;
	init();
}

Graphics::~Graphics() {}

void Graphics::clear(float r, float g, float b) const
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGlError("glBlendFunc");
    glEnable(GL_BLEND);
    checkGlError("glEnable GL_BLEND");

	glFrontFace(GL_CCW);
    checkGlError("glFrontFace");
	//glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
    checkGlError("glDisable GL_CULL_FACE");

	glEnable(GL_DEPTH_TEST);
    checkGlError("glEnable GL_DEPTH_TEST");
	//glClearDepthf(1.0f);
    //checkGlError("glClearDepthf");
	glDepthFunc(GL_LEQUAL);
    checkGlError("glDepthFunc");

	glClearColor(r, g, b, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");
}

void Graphics::init()
{
	printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

	writeLog("screenwidth:%d, screenheight:%d", screenWidth, screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
    checkGlError("glViewport");
}
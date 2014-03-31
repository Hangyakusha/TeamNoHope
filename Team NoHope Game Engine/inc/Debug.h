#pragma once

#ifndef DEBUG_H
#define DEBUG_H

#include "GL/opengl.h"
#include "AL/al.h"
#include "AL/alc.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifdef __ANDROID__
	#include <android/log.h>
	#ifndef LOG_TAG 
		#define  LOG_TAG    "libgame" 
	#endif
	#ifndef LOGI
		#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
	#endif
	#ifndef LOGE
		#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
	#endif

	static void writeLog(const char* text, ...)
	{
		va_list v;
		va_start(v, text);
		__android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, text, v);
		va_end(v);
	}
#else
	static void writeLog(const char* text, ...)
	{
		va_list v;
		va_start(v, text);
		vprintf(text, v);
		va_end(v);
	}
#endif

static void printGLString(const char *name, GLenum s) 
{
    const char *v = (const char *) glGetString(s);
    writeLog("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) 
{
    for (GLint error = glGetError(); error; error = glGetError()) 
	{
        writeLog("after %s() glError (0x%x)\n", op, error);
    }
}

static void checkAlError(const char* op)
{
	for (ALCenum error = alGetError(); error != AL_NO_ERROR; error = alGetError()) 
	{
        writeLog("after %s() glError (0x%x)\n", op, error);
    }
}

#endif
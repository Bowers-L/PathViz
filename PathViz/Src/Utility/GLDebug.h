/*
The purpose of this file is to report errors resulting from calling 
OpenGL functions to the terminal, since this is not done automatically 
and needs to be polled using glGetError()
*/


#pragma once

#include "Util.h"

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
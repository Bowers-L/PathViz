#include "GLDebug.h"
#include <glad/glad.h>
#include "Util.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		const char* errorString;

		//There aren't very many better ways to do this, unfortunately.
		switch (error) {
			case GL_INVALID_ENUM:
				errorString = "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				errorString = "GL_INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				errorString = "GL_INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:
				errorString = "GL_STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:
				errorString = "GL_STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:
				errorString = "GL_OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
		}

		PRINTLN("[OpenGL Error] (" << errorString << ")" << function << " " << file << ":" << line);
		return false;
	}

	return true;
}
#pragma once

#include <glad/glad.h>
#include "../Utility/GLDebug.h"

namespace rendering {

	//OpenGL Element Buffer used to store indices of vertices
	class ElementBuffer {
	private:
		GLuint m_ID;
		GLsizei m_Count;
	public:
		ElementBuffer(void* data, size_t size);

		GLsizei getCount() const;

		void bind() const;
		void unbind() const;
	};
}


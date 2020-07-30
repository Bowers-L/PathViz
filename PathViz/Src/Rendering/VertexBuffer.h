#pragma once

#include <glad/glad.h>
#include "../Utility/GLDebug.h"

namespace rendering {
	//GPU buffer allocated using OpenGL
	class VertexBuffer {
	private:
		GLuint m_ID;
		GLsizei m_Count;
	public:
		VertexBuffer(void* data, GLsizei size, GLsizei count);
		~VertexBuffer();

		GLsizei getCount() const;

		void bind() const;
		void unbind() const;
	};
}

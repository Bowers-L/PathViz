#pragma once

#include <glad/glad.h>
#include "../Utility/GLDebug.h"

namespace rendering {
	//GPU buffer allocated using OpenGL
	class VertexBuffer {
	private:
		GLuint m_ID;
	public:
		VertexBuffer(void* data);

		void bind();
		void unbind();
	};
}

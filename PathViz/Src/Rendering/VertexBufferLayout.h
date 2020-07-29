#pragma once

#include <vector>
#include <glad/glad.h>

#include "../Utility/Util.h"

namespace rendering {
	class VertexBufferLayout {
	private:
		std::vector<std::pair<GLenum, GLuint>> m_Elements;
		GLsizei m_Stride;

	public:
		VertexBufferLayout();

		void push(GLenum type, GLuint count);

		std::vector<std::pair<GLenum, GLuint>> getElements() const;
		GLsizei getStride() const;

		static unsigned int getSizeOfType(GLenum type);
	};
}

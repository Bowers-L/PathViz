#include "VertexBufferLayout.h"

namespace rendering {
	VertexBufferLayout::VertexBufferLayout()
		: m_Elements(std::vector<std::pair<GLenum, GLuint>>()), m_Stride(0)
	{
	}

	void VertexBufferLayout::push(GLenum type, GLuint count)
	{
		m_Elements.push_back(std::pair<GLenum, GLuint>(type, count));
		m_Stride += count * getSizeOfType(type);
	}

	std::vector<std::pair<GLenum, GLuint>> VertexBufferLayout::getElements() const
	{
		return m_Elements;
	}

	GLsizei VertexBufferLayout::getStride() const {
		return m_Stride;
	}

	unsigned int VertexBufferLayout::getSizeOfType(GLenum type) {
		switch (type) {
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}

		ASSERT(false);	//debug break because this should never happen
		return 0;
	}
}


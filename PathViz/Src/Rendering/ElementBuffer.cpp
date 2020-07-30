#include "ElementBuffer.h"

namespace rendering {
	//The code is basically the same as VertexBuffer except the target is GL_ELEMENT_ARRAY_BUFFER
	//instead of GL_ARRAY_BUFFER

	ElementBuffer::ElementBuffer(void* data, GLsizei size, GLsizei count)
	{
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

		m_Count = count;
	}

	ElementBuffer::~ElementBuffer() {
		glDeleteBuffers(1, &m_ID);
	}

	GLsizei ElementBuffer::getCount() const
	{
		return m_Count;
	}

	void ElementBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}

	void ElementBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}

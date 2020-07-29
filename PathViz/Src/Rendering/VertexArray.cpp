#include "VertexArray.h"

namespace rendering {
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_ID));
		m_Count = 0;
	}

	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		unsigned int i = 0;
		unsigned int offset = 0;

		vb.bind();
		for (std::pair<GLenum, GLuint> element : layout.getElements()) {
			GLCall(glVertexAttribPointer(i, element.second, element.first, GL_FALSE, layout.getStride(), (void*)offset));
			GLCall(glEnableVertexAttribArray(i));

			i++;
			offset += element.second * VertexBufferLayout::getSizeOfType(element.first);

		}

		m_Count = vb.getCount();
	}

	GLsizei VertexArray::getCount() const
	{
		return m_Count;
	}

	void VertexArray::bind() const
	{
		GLCall(glBindVertexArray(m_ID));
	}

	void VertexArray::unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
}



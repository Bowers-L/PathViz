#include "VertexArray.h"

namespace rendering {
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_ID));
		m_Count = 0;
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}

	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		unsigned int i = 0;
		unsigned int offset = 0;

		bind();
		vb.bind();
		for (std::pair<GLenum, GLuint> element : layout.getElements()) {
			//Specify Vertex Attribute
			/*For an attribute:
			index - The index of the attribute
			size - The number of components in the attribute (the count: for example position attributes usually have size 2 or 3)
			type - The data type of the components in this attribute
			normalized - Whether the data should be normalized
			stride - The number of bytes in between attributes (usually the size of the entire vertex)
			pointer - The byte offset of the attribute inside the vertex
			*/
			GLCall(glVertexAttribPointer(i, element.second, element.first, GL_FALSE, layout.getStride(), (void*)offset));
			GLCall(glEnableVertexAttribArray(i));

			i++;
			offset += element.second * VertexBufferLayout::getSizeOfType(element.first);

		}

		m_Count = vb.getCount();
		vb.unbind();
		unbind();
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



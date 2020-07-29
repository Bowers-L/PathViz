#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace rendering {
	class VertexArray {
	private:
		GLuint m_ID;
		GLsizei m_Count;
	public:
		VertexArray();

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		GLsizei getCount() const;

		void bind() const;
		void unbind() const;
	};
}

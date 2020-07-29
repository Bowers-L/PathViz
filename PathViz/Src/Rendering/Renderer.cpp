#include "Renderer.h"

namespace rendering {
	void Renderer::clear() {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void Renderer::drawArrays(const VertexArray& vao, const Shader& shader)
	{
		vao.bind();
		shader.bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, vao.getCount()));
		shader.unbind();
		vao.unbind();
	}

	void Renderer::drawElements(const VertexArray& vao, const ElementBuffer& ebo, const Shader& shader)
	{
		vao.bind();
		ebo.bind();
		shader.bind();
		GLCall(glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, nullptr));
		shader.unbind();
		ebo.unbind();
		vao.unbind();
	}
}
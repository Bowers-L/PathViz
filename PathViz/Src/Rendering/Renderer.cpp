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

	void Renderer::drawCircle(float originX, float originY, float radius, const Shader& shader)
	{
		float pi = 3.14159265;
		unsigned int numPoints = (unsigned int) (RESOLUTION * radius) + 1;	//+1 for the origin
		
		std::vector<float> points;
		points.push_back(originX);
		points.push_back(originY);
		points.push_back(0.0f);

		std::vector<unsigned int> indices;

		float degree = 0.0f;
		for (int i = 1; i < numPoints; i++) {
			points.push_back(originX + radius * cosf(degree));
			points.push_back(originY + radius * sinf(degree));
			points.push_back(0.0f);
			
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back((i == numPoints - 1) ? 1 : i + 1);

			degree += 2 * pi / numPoints;
		}

		VertexArray vao = VertexArray();
		VertexBuffer vbo = VertexBuffer((void *) points.data(), points.size() * sizeof(float), numPoints);
		VertexBufferLayout layout = VertexBufferLayout();
		layout.push(GL_FLOAT, 3);
		vao.addBuffer(vbo, layout);

		ElementBuffer ebo = ElementBuffer((void*) indices.data(), indices.size() * sizeof(float), numPoints * 3);

		Renderer::drawElements(vao, ebo, shader);
	}

	void Renderer::drawLine(float x1, float y1, float x2, float y2, float thickness, const Shader& shader)
	{
		glm::vec3 dir = glm::vec3::vec(x2 - x1, y2 - y1, 0.0f);
		dir = glm::normalize(glm::cross(dir, glm::vec3::vec(0.0f, 0.0f, 1.0f)));
		float dx = dir.x * thickness / 2;
		float dy = dir.y * thickness / 2;

		float vertices[]{
			x1 - dx, y1 - dy, 0.0f,
			x1 + dx, y1 + dy, 0.0f,
			x2 - dx, y2 - dy, 0.0f,
			x2 + dx, y2 + dy, 0.0f
		};

		unsigned int indices[]{
			0, 1, 2,
			2, 3, 1
		};

		VertexArray vao = VertexArray();
		VertexBuffer vbo = VertexBuffer((void*)vertices, sizeof(vertices), 4);
		VertexBufferLayout layout = VertexBufferLayout();
		layout.push(GL_FLOAT, 3);
		vao.addBuffer(vbo, layout);

		ElementBuffer ebo = ElementBuffer((void*)indices, sizeof(indices), 6);

		Renderer::drawElements(vao, ebo, shader);
	}
}
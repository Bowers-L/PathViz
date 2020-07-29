#pragma once

#include <glad/glad.h>

#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shaders/Shader.h"

namespace rendering {

	class Renderer {
	public:
		static void clear();
		static void drawArrays(const VertexArray& vao, const Shader& shader);
		static void drawElements(const VertexArray& vao, const ElementBuffer& ebo, const Shader& shader);
	};
}
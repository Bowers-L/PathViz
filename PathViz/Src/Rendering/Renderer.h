#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <ext.hpp>

#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shaders/Shader.h"
#include <vector>
#include <math.h>

#define RESOLUTION 200	//Number of points per radius unit for circles

namespace rendering {

	/*
	Set of static methods for rendering in OpenGL
	*/
	class Renderer {
	public:
		static void clear();
		static void drawArrays(const VertexArray& vao, const Shader& shader);
		static void drawElements(const VertexArray& vao, const ElementBuffer& ebo, const Shader& shader);

		static void drawCircle(float originX, float originY, float radius, const Shader& shader);
		static void drawLine(float x1, float y1, float x2, float y2, float thickness, const Shader& shader);
	};

}
/*
Path Visualizer using OpenGL
Author: Logan Bowers
*/

//External Dependencies
#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <ext.hpp>

//My Includes
#include "Utility/Util.h"
#include "Utility/GLDebug.h"

#include "Model/MapGraph.h"

#include "Rendering/Renderer.h"

#define WIDTH 1280
#define HEIGHT 760

static const bool DEBUG = true;
static const char* title = "Path Visualizer";

int init(GLFWwindow*& window);

using namespace model;
using namespace rendering;

int main(void) 
{


	Set<Location> locations = { 
		{ "A", 0, 0 }, 
		{ "B", 1, 0 }, 
		{ "C", 5, 2 },
		{ "D", 3, 3 },
		{ "E", 5, 10 },
		{ "F", 6, 0 },
		{ "G", 2, 10 },
		{ "H", 6, 5},
	};

	MapGraph map(locations, {});

	map.addPath("A", "B");
	map.addPath("A", "C");
	map.addPath("B", "D");
	map.addPath("B", "G");
	map.addPath("B", "C");
	map.addPath("C", "G");
	map.addPath("D", "F");
	map.addPath("E", "G");
	map.addPath("F", "G");
	map.addPath("F", "H");
	map.addPath("G", "H");

	//graph::Vertex start = map.getLabeledVertex("A");

	PRINTLN("Map: \n");
	PRINT(map.toString());

	//PRINTLN("Minimum Spanning Tree: \n");
	//PRINT(map.getMSTDesc({ "A", 0, 0 }));

	Route path = map.findShortestPathFromTo("A", "E");
	PRINT(path.routeDesc());


	/*Rendering Stuff*/

	GLFWwindow* window;

	//Initialize the window + OpenGL context
	if (init(window)) {
		return -1;
	}

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	Shader shader("PathViz/Src/Rendering/Shaders/Basic.shader");

	//Create Vertex Array
	VertexArray vao = VertexArray();
	VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices), 3);

	VertexBufferLayout layout;
	layout.push(GL_FLOAT, 3);
	vao.addBuffer(vbo, layout);

	shader.setUniform4f("u_Color", 0.4f, 0.2f, 0.2f, 1.0f);
	//shader.setUniformMat4f("u_MVP", (const float *) glm::value_ptr(glm::mat4(1.0f)));

	while (!glfwWindowShouldClose(window)) {

		Renderer::clear();

		/*Rendering Code*/
		Renderer::drawArrays(vao, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//window closed

	glfwTerminate();
	return 0;
}

int init(GLFWwindow*& window) {
	//initialize glfw
	if (!glfwInit()) {
		PRINTLN("Failed to initialize GLFW");
		return -1;
	}

	//Specify that this application is using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//get the window
	window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
	if (!window) {
		PRINTLN("Failed to initialize window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);	//set the framerate

	
	/*Initialize GLAD*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		PRINTLN("Failed to initialize GLAD");
		return -1;
	}

	return 0;
}
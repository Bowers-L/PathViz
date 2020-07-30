/*
Path Finder/Visualizer using OpenGL
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

	/*
	Set<Location> locations = {
		{ "A", 0, 4 }, 
		{ "B", -1, 2 }, 
		{ "C", 1, 2 },
		{ "D", -1, 0 },
		{ "E", 3, 0 },
		{ "F", -1, -2 },
		{ "G", 0, 0 },
		{ "H", 1, -2},
	};
	*/

	MapGraph map = MapGraph::generateRandomGraph(50, WIDTH, HEIGHT, 100);

	/*
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
	*/

	//graph::Vertex start = map.getLabeledVertex("A");

	PRINTLN("Map: \n");
	PRINT(map.toString());

	//PRINTLN("Minimum Spanning Tree: \n");
	//PRINT(map.getMSTDesc({ "A", 0, 0 }));

	Route route = map.findShortestPathFromTo("A", "O");
	PRINT(route.routeDesc());


	/*Rendering Stuff*/

	GLFWwindow* window;

	//Initialize the window + OpenGL context
	if (init(window)) {
		return -1;
	}

	float zoom = 1.0f;

	Shader shader("PathViz/Src/Rendering/Shaders/Basic.shader");


	shader.setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	//glm::mat4 view = glm::mat4(1.0f);
	//shader.setUniformMat4f("u_View", (const float *) glm::value_ptr(glm::translate(view, glm::vec3()
	shader.setUniformMat4f("u_Proj", (const float *) glm::value_ptr(glm::ortho((float) 0.0f, (float) WIDTH / zoom, (float) HEIGHT / zoom, 0.0f, -1.0f, 1.0f)));


	while (!glfwWindowShouldClose(window)) {

		Renderer::clear();

		/*Rendering Code*/
		shader.setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

		for (Location l : map.getLocations()) {
			Renderer::drawCircle(l.getPos().x, l.getPos().y, 3.0f, shader);
		}

		for (Path p : map.getPaths()) {
				Renderer::drawLine(	p.getU().getPos().x, p.getU().getPos().y,
									p.getV().getPos().x, p.getV().getPos().y,
									2.0f, shader);

		}

		shader.setUniform4f("u_Color", 0.90f, 0.86f, 0.0f, 1.0f);

		vec3 start = route.getPaths()->front().getU().getPos();
		Renderer::drawCircle(start.x, start.y, 3.0f, shader);
		for (Path p : *route.getPaths()) {
			Renderer::drawLine(	p.getU().getPos().x, p.getU().getPos().y,
								p.getV().getPos().x, p.getV().getPos().y,
								2.0f, shader);

			Renderer::drawCircle(p.getV().getPos().x, p.getV().getPos().y, 3.0f, shader);
		}

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
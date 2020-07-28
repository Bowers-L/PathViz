/*
Path Visualizer using OpenGL
Author: Logan Bowers
*/

//External Dependencies
#include <glad/glad.h>
#include <glfw3.h>

//My Includes
#include "Utility/Util.h"
#include "Utility/GLDebug.h"

#include "Model/MapGraph.h"

#include "Shaders/Shader.h"

#define WIDTH 1280
#define HEIGHT 760

static const bool DEBUG = true;
static const char* title = "Path Visualizer";

int init(GLFWwindow*& window);

int main(void) 
{


	Set<model::Location> locations = { 
		{ "A", 0, 0 }, 
		{ "B", 1, 0 }, 
		{ "C", 5, 2 },
		{ "D", 3, 3 },
		{ "E", 5, 10 },
		{ "F", 6, 0 },
		{ "G", 2, 10 },
		{ "H", 6, 5},
	};

	model::MapGraph map(locations, {});

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

	model::Route path = map.findShortestPathFromTo("A", "B");
	PRINT(path.routeDesc());

	
	

	/*Rendering Stuff*/
	GLFWwindow* window;

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int VAO;
	unsigned int VBO;


	//Initialize the window + OpenGL context
	if (init(window)) {
		return -1;
	}


	Shader shader("PathViz/Src/Shaders/Basic.shader");

	//Create Vertex Array
	GLCall(glGenVertexArrays(1, &VAO));

	//Create a buffer on the GPU and assign an id to the buffer to VBO
	GLCall(glGenBuffers(1, &VBO));	

	GLCall(glBindVertexArray(VAO));

	//Bind the buffer object to the target GL_ARRAY_BUFFER
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));	

	//Copy the vertex data into the buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void*)vertices, GL_STATIC_DRAW));	


	//Specify Vertex Attribute
	/*For an attribute:
	index - The index of the attribute
	size - The number of components in the attribute (the count: for example position attributes usually have size 2 or 3)
	type - The data type of the components in this attribute
	normalized - Whether the data should be normalized
	stride - The number of bytes in between attributes (usually the size of the entire vertex)
	pointer - The byte offset of the attribute inside the vertex
	*/

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (const void*) 0));

	GLCall(glEnableVertexAttribArray(0));

	shader.setUniform4f("u_Color", 0.4f, 0.2f, 0.2f, 1.0f);

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

		/*Rendering Code*/
		shader.bind();
		GLCall(glBindVertexArray(VAO));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

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
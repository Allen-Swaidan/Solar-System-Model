#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "shader.h"
#include "screen.h"

void window_reshape_callback(GLFWwindow* window, int newWidth, int newHeight) {
	float aspect = (float)newWidth / (float)newHeight; // new width&height provided by the callback
	glViewport(0, 0, newWidth, newHeight);			   // sets screen region associated with framebuffer
	glm::mat4 pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

int main(void)
{	
	//specifying Opengl version
	if (!glfwInit()) 
	{ 
		exit(EXIT_FAILURE); 
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	
	//creating window
	GLFWwindow* window = glfwCreateWindow(800, 800, "General Relativity Simulation", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) 
	{ 
		exit(EXIT_FAILURE); 
	}
	glfwSwapInterval(1);

	Screen screen;
	glfwSetWindowSizeCallback(window, window_reshape_callback);
	screen.initalize(window);

	while (!glfwWindowShouldClose(window))
	{
		screen.display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
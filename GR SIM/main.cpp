#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include<glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "screen.h"

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
	GLFWwindow* window = glfwCreateWindow(800, 800, "Chapter2 - program1", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) 
	{ 
		exit(EXIT_FAILURE); 
	}
	glfwSwapInterval(1);

	Screen screen;
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
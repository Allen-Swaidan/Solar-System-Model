#ifndef SCREEN_H
#define SCREEN_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include<glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include "shader.h"
#include "shape.h"
#include "buffer.h"

class Screen
{
public:

	Screen();
	void initalize(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

private:

	//allocate variables used in display() function so that they won’t need to be allocated during rendering
	Buffer buffer;
	GLuint renderingProgram;
	Shape shapeOne, shapeTwo, shapeThree, shapeFour, shapeFive;
	int width, height;

	float cameraX, cameraY, cameraZ, aspect, //camera position
		  cubeLocX, cubeLocY, cubeLocZ, //cube position
		  pyrLocX, pyrLocY, pyrLocZ;	// pyramid position


	glm::mat4 pMat, vMat;
	std::stack<glm::mat4> mvStack;

};
#endif 


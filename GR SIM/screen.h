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
#include "sphere.h"

#define numVAOs 1
#define numVBOs 2

#define GLFW_KEY_W 87
#define GLFW_KEY_A 65
#define GLFW_KEY_S 83
#define GLFW_KEY_D 68

class Screen
{
public:

	Screen();
	void initalize(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);
	void setupVertices(void);

private:
	//allocate variables used in display() function so that they won’t need to be allocated during rendering
	Buffer buffer;
	GLuint renderingProgram;
	Shape shapeOne, shapeTwo, shapeThree, shapeFour, shapeFive;
	Sphere sphereOne, sphereTwo, sphereThree, sphereFour, sphereFive;

	int width, height;
	GLuint mvLoc, projLoc;
	double xpos, ypos;
	float cameraX, cameraY, cameraZ, aspect, //camera position
		  cubeLocX, cubeLocY, cubeLocZ, //cube position
		  pyrLocX, pyrLocY, pyrLocZ,
		  sphereLocX, sphereLocY, sphereLocZ;	// pyramid position

	glm::mat4 pMat, vMat;
	std::stack<glm::mat4> mvStack;
	
	GLuint vao[numVAOs]; // OpenGL requires these values be specified in arrays
	GLuint vbo[numVBOs];

};
#endif 


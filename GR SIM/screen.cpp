#include "screen.h"

Screen::Screen()
{
	aspect = 0.0f;
	height = 0.0f;
	width = 0.0f;
	renderingProgram = 0;
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 0.0f;
	cubeLocX = 0.0f;
	cubeLocY = 0.0f;
	cubeLocZ = 0.0f;
	pyrLocX = 0.0f;
	pyrLocY = 0.0f;
	pyrLocZ = 0.0f;
	pMat = glm::mat4();
	vMat = glm::mat4();
}

void Screen::initalize(GLFWwindow* window)
{
	Shader::Instance()->createProgram();
	Shader::Instance()->createShaders();
	Shader::Instance()->compileShaders();
	Shader::Instance()->attachShaders();
	renderingProgram = Shader::Instance()->linkProgram();
	
	cameraX = 0.0f;
	cameraY = 2.0f;
	cameraZ = 25.0f;

	cubeLocX = 0.0f;
	cubeLocY = -2.0f;
	cubeLocZ = 0.0f;

	pyrLocX = 0.0f;
	pyrLocY = 2.0f;
	pyrLocZ = 0.0f;

	//build perspective matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees

}


void Screen::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);

	//loads the program onto the gpu
	glUseProgram(renderingProgram); 

	//build view matrix
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mvStack.push(vMat);

	Shader::Instance()->SendUniformData("proj_matrix", glm::value_ptr(pMat)); 

	//motion of the prism == sun
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	
	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	shapeOne.pyramid();
	mvStack.pop();
	
	//motion of the big cube == planet
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 4.0f, 0.0f, cos((float)currentTime) * 4.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	shapeTwo.cube();
	mvStack.pop();

	//motion of the smaller cube == moon
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 2.0f, 0.0f, -cos((float)currentTime) * 2.0f));
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0, 0.0, 1.0));
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));
	
	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	shapeThree.cube();
	mvStack.pop();

	//bigger cube thats further away
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 5.0f, 0.0f, cos((float)currentTime) * 5.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	shapeFour.cube();
	mvStack.pop();
	
	//octahedron
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 5.0f, 0.0f, cos((float)currentTime) * 5.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	shapeFive.octahedron();
	mvStack.pop();
	
	mvStack.pop();
	mvStack.pop();
	mvStack.pop();
	mvStack.pop();

	mvStack.pop();
	
}



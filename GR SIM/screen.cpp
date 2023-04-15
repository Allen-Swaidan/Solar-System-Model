#include "screen.h"

Screen::Screen()
{
	Screen::aspect = 0;
	Screen::cameraX = 0.0f;
	Screen::cameraY = 0.0f;
	Screen::cameraZ = 0.0f;
	Screen::cubeLocX = 0.0f;
	Screen::cubeLocY = 0.0f;
	Screen::cubeLocZ = 0.0f;
	Screen::height = 0;
	Screen::width = 0;
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
	cameraZ = 11.0f;

	cubeLocX = 0.0f;
	cubeLocY = -2.0f;
	cubeLocZ = 0.0f;

	pyrLocX = 0.0f;
	pyrLocY = 2.0f;
	pyrLocZ = 0.0f;
}

void Screen::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	//loads the program onto the gpu
	glUseProgram(renderingProgram);
	Shape shapeOne, shapeTwo;

	//build perspective matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees

	//build view matrix
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mvStack.push(vMat);

	//getting the uniform variables for move matrix and projection matrix 
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//pyramid == sun
	shapeOne.pyramid();

	//motion of the prism
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	
	//sending information to the mv_matrix
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 18); 
	mvStack.pop();
	
	//cube == planet
	shapeTwo.cube();
	
	//motion of the big cube
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 4.0f, 0.0f, cos((float)currentTime) * 4.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0, 1.0, 0.0));
	
	//sending information to mv_matrix and drawing cube
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mvStack.pop();

	//smaller cube == moon
	//motion of the smaller cube
	mvStack.push(mvStack.top());
	//mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)currentTime) * 2.0, cos((float)currentTime) * 2.0));
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 2.0f, 0.0f, -cos((float)currentTime) * 2.0f));
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0, 0.0, 1.0));
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));

	//sending information to the mv_matrix and drawing cube
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	mvStack.pop();
	mvStack.pop();
	mvStack.pop();
	mvStack.pop();
}

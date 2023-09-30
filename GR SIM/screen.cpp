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
	xpos = 0;
	ypos = 0;
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
	cameraY = 5.0f;
	cameraZ = 45.0f;

	cubeLocX = 0.0f;
	cubeLocY = -2.0f;
	cubeLocZ = 0.0f;

	pyrLocX = 0.0f;
	pyrLocY = 2.0f;
	pyrLocZ = 0.0f;

	sphereLocX = 0.0f;
	sphereLocY = 2.0f;
	sphereLocZ = 0.0f;

	//build perspective matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees

}

void Screen::setupVertices(void) 
{
	std::vector<int> ind = sphereOne.getIndices();
	std::vector<glm::vec3> vert = sphereOne.getVertices();
	std::vector<glm::vec2> tex = sphereOne.getTexCoords();
	std::vector<glm::vec3> norm = sphereOne.getNormals();
	std::vector<float> pvalues; // vertex positions
	std::vector<float> tvalues; // texture coordinates
	std::vector<float> nvalues; // normal vectors

	int numIndices = sphereOne.getNumIndices();
	for (int i = 0; i < numIndices; i++) 
	{
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);
		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);
		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);
	}

	//implement the glUniform function to send VBO to mv matrix uniform and glAttribPointer
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(2, vbo);
	// put the vertices into buffer #0
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

	// put the texture coordinates into buffer #1
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);
	// put the normals into buffer #2
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);

	/*buffer.createBuffer(48);
	buffer.FillVBO(Buffer::VERTEX_BUFFER, pvalues.size(), &pvalues[0], Buffer::SINGLE);
	buffer.FillVBO(Buffer::VERTEX_BUFFER, nvalues.size(), &nvalues[0], Buffer::SINGLE);
	buffer.LinkBuffer("position", Buffer::VERTEX_BUFFER, Buffer::XYZ, Buffer::FLOAT);
	buffer.LinkBuffer("varyingColor", Buffer::COLOR_BUFFER, Buffer::RGBA, Buffer::FLOAT);
	buffer.Render(Buffer::TRIANGLES);
	buffer.DestroyBuffer();*/
}

static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	glfwGetCursorPos(window, &xpos, &ypos);
	std::cout << xpos << " : " << ypos << std::endl;

}

//recording mouse position only when cursor is inside screen
void cursorEnterCallBack(GLFWwindow *window, int entered)
{
	bool inside = entered;

	if (inside == true)
	{	
		std::cout << "Entered Window" << std::endl;
		glfwSetCursorPosCallback(window, cursor_position_callback);
	}
	else
	{
		std::cout << "Left Window" << std::endl;
	}

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

	//Sphere!!!!!!!
	//Sun
	sphereOne;
	setupVertices();

	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime * 10.0f, glm::vec3(100.0f, 100.0f, 100.0f));
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 5.0f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, sphereOne.getNumIndices());
	mvStack.pop();
	mvStack.pop();
	
	//Earth
	sphereTwo;
	setupVertices();

	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime) * 10.0f, 0.0f, cos((float)currentTime) * 10.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, sphereTwo.getNumIndices());
	//mvStack.pop();
	
	//moon
	sphereThree;
	setupVertices();

	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime*2.0f) * 2.0f, 0.0f, cos((float)currentTime*2.0f) * 2.0f));
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * 2.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, sphereThree.getNumIndices());
	mvStack.pop();

	//bigger planet
	sphereFour;
	setupVertices();

	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime*10.0f) * 15.0f, 0.0f, cos((float)currentTime*10.0f) * 15.0f));
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime), glm::vec3(5.0f, 5.0f, 5.0f));
	mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, sphereFour.getNumIndices());
	mvStack.pop();
	
	//if key input is detected, move the current position of the camera

	int stateOne = glfwGetKey(window, GLFW_KEY_W);
	int stateTwo = glfwGetKey(window, GLFW_KEY_A);
	int stateThree = glfwGetKey(window, GLFW_KEY_S);
	int stateFour = glfwGetKey(window, GLFW_KEY_D);

	if (stateOne == GLFW_PRESS)
	{
		cameraZ -= 1.0f;
	}
	if (stateTwo == GLFW_PRESS)
	{
		cameraX -= 1.0f;
	}
	if (stateThree == GLFW_PRESS)
	{
		cameraZ += 1.0f;
	}
	if (stateFour == GLFW_PRESS)
	{
		cameraX += 1.0f;
	}

	//glfwGetCursorPos(window, &xpos, &ypos);
	//glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetCursorEnterCallback(window, cursorEnterCallBack);


}



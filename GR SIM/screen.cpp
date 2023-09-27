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
	cameraZ = 15.0f;

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
	std::vector<int> ind = mySphere.getIndices();
	std::vector<glm::vec3> vert = mySphere.getVertices();
	std::vector<glm::vec2> tex = mySphere.getTexCoords();
	std::vector<glm::vec3> norm = mySphere.getNormals();
	std::vector<float> pvalues; // vertex positions
	std::vector<float> tvalues; // texture coordinates
	std::vector<float> nvalues; // normal vectors

	int numIndices = mySphere.getNumIndices();
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
	mySphere;
	setupVertices();

	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));

	Shader::Instance()->SendUniformData("mv_matrix", glm::value_ptr(mvStack.top()));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
	mvStack.pop();


	/*
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
	*/
}



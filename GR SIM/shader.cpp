#include<fstream>
#include <iostream>
#include <string>
#include "shader.h"

Shader* Shader::Instance()
{
	static Shader* shaderObject = new Shader();
	return shaderObject;
}

Shader::Shader()
{
	vertCompiled = 0;
	fragCompiled = 0;
	linked = 0;
	vfProgram = 0;
	vShader = 0;
	fShader = 0;
}

GLuint Shader::GetShaderProgramID()
{
	return vfProgram;
}

//reading shader code from vertex and fragment shader files
std::string Shader::readShaderSource(const char* filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";

	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

//generating a vertex and fragment shader and storing the integer ID in the variables
bool Shader::createShaders()
{
	vShader = glCreateShader(GL_VERTEX_SHADER);
	if (vShader == 0)
	{
		std::cout << "Error creating vertex shader object" << std::endl;
		return false;
	}
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fShader == 0)
	{
		std::cout << "Error creating fragment shader" << std::endl;
		return false;
	}
	return true;
}

//creating a program object
bool Shader::createProgram()
{
	vfProgram = glCreateProgram();
	if (vfProgram == 0)
	{
		std::cout << "Error creating shader program ID" << std::endl;
		return false;
	}
	return true;
}

bool Shader::compileShaders()
{
	//storing glsl code from shader files
	std::string vertShaderStr = readShaderSource("vertShader.glsl");
	std::string fragShaderStr = readShaderSource("fragShader.glsl");
	
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();

	//loads the GLSL code from the strings into the empty shader object
	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);

	glCompileShader(vShader);

	//error handling
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		std::cout << "Vertex compilation failed" << std::endl;
		printShaderLog(vShader);
		return false;
	}

	glCompileShader(fShader);

	//error handling
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		std::cout << "Fragment compilation failed" << std::endl;
		printShaderLog(fShader);
		return false;
	}
	return true;
}

void Shader::attachShaders()
{
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
}

GLuint Shader::linkProgram()
{
	glLinkProgram(vfProgram);
	glUseProgram(vfProgram); //TRY THIS
	checkOpenGLError();
	
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		std::cout << "linking failed" << std::endl;
		printProgramLog(vfProgram);
	}
	return vfProgram;
}

bool Shader::SendUniformData(const std::string& uniformName, GLint data)
{
	GLint ID = glGetUniformLocation(vfProgram, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << "not found or not used" << std::endl;
		return false;
	}

	glUniform1i(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLuint data)
{
	GLint ID = glGetUniformLocation(vfProgram, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << "not found or not used" << std::endl;
		return false;
	}

	glUniform1ui(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat data)
{
	GLint ID = glGetUniformLocation(vfProgram, uniformName.c_str());
	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << "not found or not used" << std::endl;
		return false;
	}

	glUniform1f(ID, data);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y)
{
	GLint ID = glGetUniformLocation(vfProgram, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << "not found or not used" << std::endl;
		return false;
	}

	glUniform2f(ID, x, y);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z)
{
	GLint ID = glGetUniformLocation(vfProgram, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << "not found or not used" << std::endl;
		return false;
	}

	glUniform3f(ID, x, y, z);
	return true;
}

bool Shader::SendUniformData(const std::string& uniformName, const glm::mat4& data)
{
	GLint ID = glGetUniformLocation(vfProgram, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << "not found or not used" << std::endl;
		return false;
	}
	
	glUniformMatrix4fv(ID, 1, GL_FALSE, &data[0][0]);
	return true;
}

//for passing glm::value_ptr(data) arguments
bool Shader::SendUniformData(const std::string& uniformName, const GLfloat* data)
{
	GLint ID = glGetUniformLocation(vfProgram, uniformName.c_str());

	if (ID == -1)
	{
		std::cout << "Shader variable " << uniformName << "not found or not used" << std::endl;
		return false;
	}

	glUniformMatrix4fv(ID, 1, GL_FALSE, data);
	return true;
}

//error handling
bool Shader::checkOpenGLError()
{
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cout << "glError:" << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

//error handling
void Shader::printShaderLog(GLuint shader)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log:" << log << std::endl;
		free(log);
	}
}

//error handling
void Shader::printProgramLog(int prog)
{
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0)
	{
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}
#include "buffer.h"

Buffer::Buffer()
{
	m_VAO = 0;
	m_vertexVBO = 0;
	m_colorVBO = 0;
	m_textureVBO = 0;
	m_totalVertices = 0;
}

void Buffer::createBuffer(GLuint totalVertices)
{
	glGenBuffers(1, &m_vertexVBO);
	glGenBuffers(1, &m_colorVBO);
	glGenBuffers(1, &m_textureVBO);
	glGenVertexArrays(1, &m_VAO);
	m_totalVertices = totalVertices;
}

void Buffer::FillVBO(VBOType VBOType, GLsizeiptr buffersize, GLfloat* data, FillType filltype)
{
	glBindVertexArray(m_VAO);
	
	if (VBOType == VERTEX_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
	}
	else if (VBOType == COLOR_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
	}

	glBufferData(GL_ARRAY_BUFFER, buffersize, data, filltype);
	glBindVertexArray(0);
	
}

void Buffer::LinkBuffer(const std::string& attribute, VBOType VBOType, ComponentType componentType, DataType dataType)
{
	GLuint shaderProgramID = Shader::Instance()->GetShaderProgramID();
	
	GLint ID = glGetAttribLocation(shaderProgramID, attribute.c_str());

	glBindVertexArray(m_VAO);
	
	if (VBOType == VERTEX_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
	}
	if (VBOType == COLOR_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
	}
	if (VBOType == TEXTURE_BUFFER)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_textureVBO);
	}

	glVertexAttribPointer(ID, componentType, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(ID);

	glBindVertexArray(0);
	
}

void Buffer::Render(DrawType drawType)
{
	glBindVertexArray(m_VAO);
	glDrawArrays(drawType, 0, m_totalVertices / 3);
	glBindVertexArray(0);
}

void Buffer::DestroyBuffer()
{
	glDeleteBuffers(1, &m_vertexVBO);
	glDeleteBuffers(1, &m_colorVBO);
	glDeleteBuffers(1, &m_textureVBO);
	glDeleteVertexArrays(1, &m_VAO);
}


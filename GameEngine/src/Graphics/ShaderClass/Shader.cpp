#include "gepch.h"

#include "Shader.h"

Shader::Shader()
{
	m_vertexSource = getFileContents("assets/shaders/default.vert");
	m_fragmentSource = getFileContents("assets/shaders/default.frag");
}

Shader::Shader(const char* vertexFileName, const char* fragmentFileName)
{
	m_vertexSource = getFileContents(vertexFileName);
	m_fragmentSource = getFileContents(fragmentFileName);

	CompileShaders();
	Activate();
}

std::string Shader::getFileContents(const char* fileName)
{
	std::ifstream in(fileName);
	if (in.fail())
	{
		FATAL("Failed to Open File");
	}

	std::string result;
	std::string line;

	while (std::getline(in, line))
	{
		result += (line + "\n");
	}

	return result;
}

void Shader::CompileShaders()
{
	ID = glCreateProgram();

	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSrc = m_vertexSource.c_str();
	glShaderSource(vertexID, 1, &vertexSrc, nullptr);
	glCompileShader(vertexID);
	handleErrors(GL_VERTEX_SHADER, m_vertexSource, vertexID);
		
	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSrc = m_fragmentSource.c_str();
	glShaderSource(fragmentID, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentID);
	handleErrors(GL_FRAGMENT_SHADER, m_fragmentSource, fragmentID);

	glAttachShader(ID, vertexID);
	glAttachShader(ID, fragmentID);
	glLinkProgram(ID);
	glValidateProgram(ID);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::handleErrors(GLuint type, const std::string& source, GLuint shaderID)
{
	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, message);
		
		if (type == GL_VERTEX_SHADER)
		{
			FATAL("Failed to Compile Vertex Shader");
		}
		else
		{
			FATAL("Failed to Compile Fragment Shader");
		}
		
		FATAL(message);

		glDeleteShader(shaderID);
	}
	else
	{
		if (type == GL_VERTEX_SHADER)
		{
			INFO("Compiled Vertex Shader");
		}
		else
		{
			INFO("Compiled Fragment Shader");
		}
	}
}

void Shader::setUniformVar(const glm::mat4& uniform, const char* uniformName) const
{
	GLuint location = glGetUniformLocation(ID, uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(uniform));
}

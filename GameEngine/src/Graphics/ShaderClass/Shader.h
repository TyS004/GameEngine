#pragma once

#include "Logging/Log.h"

class Shader
{
public:
	GLuint ID;
	
	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);

	std::string getFileContents(const char* fileName);

	void Activate();
	void Delete();

	void CompileShaders();
	void handleErrors(GLuint type, const std::string& source, GLuint shaderID);

	void setUniformMat4f(const glm::mat4& uniform, const char* uniformName) const;
	void setTextureUniform(uint32_t tex);

private:
	std::string m_vertexSource, m_fragmentSource;
	GLuint m_program;
};

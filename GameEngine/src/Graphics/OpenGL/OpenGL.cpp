#include "gepch.h"

#include "OpenGL.h"
#include "Graphics/ShaderClass/Shader.h"

OpenGL::OpenGL()
	: Render()
{
	Init();
}

OpenGL::~OpenGL()
{

}

void OpenGL::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		WARN("Failed to Start OpenGl");
	}
	else
	{
		TRACE("Started OpenGl Successfully!");
	}
	glEnable(GL_DEPTH_TEST);
}

void OpenGL::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
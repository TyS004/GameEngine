#include "gepch.h"

#include "OpenGL.h"
#include "Graphics/ShaderClass/Shader.h"

OpenGL::OpenGL()
	: Render()
{
	Init();
	InitShaders();
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
}

void OpenGL::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::CreateBuffers()
{
	GLfloat vertices[] =
	{
		//POSITION (X,Y,Z)  //COLOR (R,G,B)
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	VAO VAO1;
	VBO VBO1(vertices, sizeof(vertices));

	//Bind Array Vertex
	VAO1.Bind();

	//Set Attributes
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), 0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), 3 * sizeof(float));

	TRACE("Created Buffers");
}

void OpenGL::DrawTriangle()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OpenGL::InitShaders()
{
	shader.CompileShaders();
	shader.Activate();
}

void OpenGL::OnUpdate(const glm::mat4& trans)
{
	shader.setUniformVar(trans);
}
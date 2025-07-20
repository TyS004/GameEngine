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

	QUAD_VBO = std::make_unique<VBO>(QUAD_BUFFER, sizeof(QUAD_BUFFER));
	m_VAO1 = std::make_unique<VAO>();
	m_quadShader = std::make_unique<Shader>("assets/shaders/quad.vert", "assets/shaders/quad.frag");

	m_VAO1->Bind();
	QUAD_VBO->Bind();
	m_VAO1->LinkAttribute(*QUAD_VBO, 0, 2, GL_FLOAT, 4 * sizeof(float), 0);
	m_VAO1->LinkAttribute(*QUAD_VBO, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));
	m_VAO1->Unbind();
	QUAD_VBO->Unbind();
}

void OpenGL::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL::ResizeViewport(uint32_t width, uint32_t height)
{
	float targetAspect = 16.0f / 9.0f;
	float windowAspect = (float)width / (float)height;

	if (windowAspect > targetAspect)
	{
		int newWidth = (int)(height * targetAspect);
		int xOffset = (width - newWidth) / 2;
		glViewport(xOffset, 0, newWidth, height);
	}
	else
	{
		int newHeight = (int)(width / targetAspect);
		int yOffset = (height - newHeight) / 2;
		glViewport(0, yOffset, width, newHeight);
	}
}

void OpenGL::RenderQuad(const Texture& frameTexture)
{
	frameTexture.Bind();

	m_quadShader->Activate();
	m_quadShader->setTextureUniform(0);
	glActiveTexture(GL_TEXTURE0);

	m_VAO1->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_VAO1->Unbind();

	frameTexture.Unbind();
}
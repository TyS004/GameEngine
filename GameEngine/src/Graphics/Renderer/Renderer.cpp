#include "gepch.h"

#include "Renderer.h"
#include "Graphics/ShaderClass/Shader.h"

#include "Application.h"

namespace GameEngine
{
	Renderer::Renderer()
	{
		Init();
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			WARN("Failed to Start Renderer");
		}
		else
		{
			TRACE("Started Renderer Successfully!");
		}
		glEnable(GL_DEPTH_TEST);

		//Quad VBO Init
		m_quadVBO = std::make_unique<VBO>(QUAD_BUFFER, sizeof(QUAD_BUFFER));
		m_VAO = std::make_unique<VAO>();
		m_quadShader = std::make_unique<Shader>("assets/shaders/quad.vert", "assets/shaders/quad.frag");
		m_quadShader->Activate();

		m_VAO->Bind();
		m_quadVBO->Bind();
		m_VAO->LinkAttribute(*m_quadVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), 0);
		m_VAO->LinkAttribute(*m_quadVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));
		m_VAO->Unbind();
		m_quadVBO->Unbind();

		//FBO Init
		m_FBOTexture = std::make_unique<Texture>(START_WINDOW_WIDTH, START_WINDOW_HEIGHT);
		m_FBO = std::make_unique<FBO>(*m_FBOTexture);
		m_RBO = std::make_unique<RBO>(*m_FBO);

		//Default Shader Init
		//m_defaultShader = new Shader();
		//m_defaultShader->CompileShaders();
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::ResizeViewport(uint32_t width, uint32_t height)
	{
		float targetAspect = 16.0f / 9.0f;
		float windowAspect = (float)width / (float)height;

		if (windowAspect > targetAspect)
		{
			int newWidth = (int)(height * targetAspect);
			UpdateFrameBufferTexture(newWidth, height);
		}
		else
		{
			int newHeight = (int)(width / targetAspect);
			UpdateFrameBufferTexture(width, newHeight);
		}
	}

	//Not in Use may get used in Future
	void Renderer::RenderQuad(const Texture& frameTexture)
	{
		frameTexture.Bind();

		m_quadShader->Activate();
		m_quadShader->setTextureUniform(0);
		glActiveTexture(GL_TEXTURE0);

		m_VAO->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_VAO->Unbind();

		frameTexture.Unbind();
	}

	void Renderer::UpdateFrameBufferTexture(float width, float height)
	{
		m_FBOTexture = std::make_unique<Texture>(width, height);
		m_FBO = std::make_unique<FBO>(*m_FBOTexture);
		m_RBO = std::make_unique<RBO>(*m_FBO);
	}

	void Renderer::SubmitMesh(const MeshComponet& cubeRenderer, const TransformComponet& transform, const Shader& shader)
	{
		shader.setUniformMat4f(transform.Transform, "model");

		VAO VAO1;
		VBO VBO1(cubeRenderer.m_buffer, sizeof(cubeRenderer.m_buffer));
		VAO1.Bind();
		VBO1.Bind();

		VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
		VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
		VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));

		VAO1.Unbind();
		VBO1.Unbind();

		VAO1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		VAO1.Unbind();
	}

	FBO Renderer::GetFBO() const
	{
		return *m_FBO;
	}
	
	Texture Renderer::GetFBOTexture() const
	{
		return *m_FBOTexture;
	}

	RBO Renderer::GetRBO() const
	{
		return *m_RBO;
	}
}
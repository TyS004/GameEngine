#pragma once

#include "Logging/Log.h"

#include "Graphics/ShaderClass/Shader.h"

#include "Graphics/Buffer/VBO.h"
#include "Graphics/Buffer/VAO.h"
#include "Graphics/Buffer/Texture.h"
#include "Graphics/Buffer/FBO.h"
#include "Graphics/Buffer/RBO.h"

namespace GameEngine
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Init();
		void Clear(float r, float g, float b, float a);

		void ResizeViewport(uint32_t width, uint32_t height);
		void RenderQuad(const Texture& frameTexture);
		void UpdateFrameBufferTexture(float width, float height);

		FBO GetFBO() const;
		Texture GetFBOTexture() const;
		RBO GetRBO() const;

	private:
		const float QUAD_BUFFER[24] =
		{
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		std::unique_ptr<VBO> m_quadVBO;
		std::unique_ptr<Shader> m_quadShader;
		std::unique_ptr<VAO> m_VAO;
		
		std::unique_ptr<Texture> m_FBOTexture;
		std::unique_ptr<FBO> m_FBO;
		std::unique_ptr<RBO> m_RBO;
	};
}

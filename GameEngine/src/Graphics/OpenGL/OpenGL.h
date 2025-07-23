#pragma once

#include "Logging/Log.h"

#include "Graphics/ShaderClass/Shader.h"

#include "Graphics/Buffer/VBO.h"
#include "Graphics/Buffer/VAO.h"
#include "Graphics/Buffer/Texture.h"

namespace GameEngine
{
	class Render
	{
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
	protected:
		Render() {}
	};

	class OpenGL : public Render
	{
	public:
		OpenGL();
		~OpenGL();

		void Init() override;
		void Clear() override;

		void ResizeViewport(uint32_t width, uint32_t height);
		void RenderQuad(const Texture& frameTexture);

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

		std::unique_ptr<VBO> QUAD_VBO;
		std::unique_ptr<Shader> m_quadShader;
		std::unique_ptr<VAO> m_VAO1;
	};
}

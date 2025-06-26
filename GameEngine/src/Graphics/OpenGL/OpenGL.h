#pragma once

#include "Logging/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Graphics/ShaderClass/Shader.h"

#include "Graphics/VBO.h"
#include "Graphics/VAO.h"

struct Vertex2D
{
	float x, y;
	Vertex2D(float x = 0, float y = 0) :
		x(x), y(y) {}
};

struct Vertex3D
{
	float x, y, z;
	Vertex3D(float x = 0, float y = 0, float z = 0) :
		x(x), y(y), z(z) {}
};

class Render
{
public:
	virtual void Init() = 0;
	virtual void Clear() = 0;
	virtual void DrawTriangle() = 0;
	virtual void CreateBuffers() = 0;
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
	void DrawTriangle() override;
	void CreateBuffers() override;

	void InitShaders();
	void OnUpdate(const glm::mat4& trans);

private:
	Shader shader = Shader();
};

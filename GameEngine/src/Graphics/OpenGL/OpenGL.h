#pragma once

#include "Logging/Log.h"

#include "Graphics/ShaderClass/Shader.h"

#include "Graphics/Buffer/VBO.h"
#include "Graphics/Buffer/VAO.h"

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
};

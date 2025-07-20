#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 aTextCoord;

out vec2 textCoord;

void main()
{
	gl_Position = position;
	textCoord = aTextCoord;
};
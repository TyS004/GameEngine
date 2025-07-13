#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextCoord;

out vec3 ourColor;
out vec2 textCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * position;

	ourColor = aColor;
	textCoord = aTextCoord;
};
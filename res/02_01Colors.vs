#version 330

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 prj;

void main()
{
	gl_Position = prj * view * model * vec4(aPos, 1.0);
}
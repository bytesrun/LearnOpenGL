#version 330 core
layout (location = 0) vec4 aPos;
uniform float off;
void main()
{
    gl_Position = vec4(aPos.x + off, aPos.y, aPos.z, 1.0f);
}
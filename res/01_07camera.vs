#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 ourTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    //gl_Position = model * vec4(aPos, 1.0);
    //ourColor = vec4(aColor, 1.0);
    ourTexCoord = aTexCoord;
}
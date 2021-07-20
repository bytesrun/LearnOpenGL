#version 330 core
in vec4 ourColor;
in vec2 ourTexCoord;

out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = texture(texture1, ourTexCoord) * ourColor;
    FragColor = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), 0.2) * ourColor;
}
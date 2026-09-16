#version 460 core
out vec4 FragColor;

in vec3 ourColor;
uniform float red;

void main()
{
    FragColor = vec4(red,ourColor.xy,1.0);
}
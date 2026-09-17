#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float u_PositionX;
void main()
{
    gl_Position = vec4(aPos + vec3(u_PositionX, 0.0, 0.0), 1.0);
    ourColor = aColor;
}
#version 440

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in vec4 color;

out vec4 fragmentColor;

void main()
{
    gl_Position.xy = vertexPos;
    gl_Position.z  = 0.0;
    gl_Position.w  = 1.0;

    fragmentColor = color;
}
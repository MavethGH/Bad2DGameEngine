#version 440

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;

out vec2 fragmentPos;
out vec4 fragmentColor;
out vec2 fragmentUv;

void main()
{
    gl_Position.xy = vertexPos;
    gl_Position.z  = 0.0;
    gl_Position.w  = 1.0;

    fragmentPos = vertexPos;
    fragmentColor = color;
    fragmentUv = uv;
}
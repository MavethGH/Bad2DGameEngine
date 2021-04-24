#version 440
//#define PI 3.1415926535897932384626433832795

out vec4 color;

uniform float time;
uniform vec2 res;

in vec4 fragmentColor;

void main()
{
    color = fragmentColor;
}
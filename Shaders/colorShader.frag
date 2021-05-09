#version 440
// Don't ask
//#define PI 3.1415926535897932384626433832795

out vec4 color;

uniform float time;
uniform sampler2D textureSampler;

in vec2 fragmentPos;
in vec4 fragmentColor;
in vec2 fragmentUv;

void main()
{
    vec4 textureColor = texture(textureSampler, fragmentUv);

    // Wacky colors
    /*
    float r = fragmentColor.r * (cos(fragmentPos.x * 4.0 + time) + 1.0) * 0.5;
    float g = fragmentColor.g * (cos(fragmentPos.y * 8.0 + time) + 1.0) * 0.5;
    float b = fragmentColor.b * (cos(fragmentPos.x * 2.0 + time) + 1.0) * 0.5;
    color = vec4(r, g, b, fragmentColor.a) / textureColor;
    */
    color = textureColor;
}
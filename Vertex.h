#pragma once

#include <GL/glew.h>

struct Vertex
{
    struct Position
    {
        float x;
        float y;
    } position;

    struct Color
    {
        float r;
        float g;
        float b;
        float a;
    } color;
};
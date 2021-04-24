#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite() : _vboID(0)
{

}

Sprite::~Sprite()
{
    // Free up space occupied by VBO
    if (_vboID)
    {
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::init(float x, float y, float width, float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    // Create buffer to store VBO
    if (!_vboID)
    {
        glGenBuffers(1, &_vboID);
    }

    // Vertex coordinates
    // Top Left
    float tlX = x;
    float tlY = y + height;
    // Top Right
    float trX = x + width;
    float trY = y + height;
    // Bottom Left
    float blX = x;
    float blY = y;
    // Bottom Right
    float brX = x + width;
    float brY = y;


    // OpenGL will read this as 2 triangles, which make a square
    Vertex vertexBufferData[12];
    vertexBufferData[0].position = {tlX, tlY};
    vertexBufferData[1].position = {trX, trY};
    vertexBufferData[2].position = {blX, blY};
    vertexBufferData[3].position = {trX, trY};
    vertexBufferData[4].position = {brX, brY};
    vertexBufferData[5].position = {blX, blY};

    // Make them all green by default
    for (Vertex v : vertexBufferData)
    {
        v.color = {0.0f, 1.0f, 0.0f, 1.0f};
    }

    // Upload VBO to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
    // Setup
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glEnableVertexAttribArray(0);

    // Position pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glDisableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    // Color pointer
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glDisableVertexAttribArray(1);

    // Draw stuff
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Cleanup
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite() : _vboID(0), _iboID(0)
{

}

Sprite::~Sprite()
{
    // Free up space occupied by VBO and IBO
    if (_vboID)
    {
        glDeleteBuffers(1, &_vboID);
    }
    if (_iboID)
    {
        glDeleteBuffers(1, &_iboID);
    }
}

void Sprite::init(float x, float y, float width, float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    // Create buffer to store Vertex Buffer Object
    if (!_vboID)
    {
        glGenBuffers(1, &_vboID);
    }

    // Create buffer to store Index Buffer Object
    if (!_iboID)
    {
        glGenBuffers(1, &_iboID);
    }

    // Index Buffer data
    GLuint indices[6] = { 0, 1, 2, 2, 3, 1 };

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
    Vertex vertexBufferData[4];
    vertexBufferData[0].position = {tlX, tlY};
    vertexBufferData[1].position = {trX, trY};
    vertexBufferData[2].position = {blX, blY};
    vertexBufferData[3].position = {brX, brY};

    // Make them all green by default
    for (Vertex &v : vertexBufferData)
    {
        v.color = {0.0f, 1.0f, 0.0f, 1.0f};
    }

    // Upload VBO to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Upload IBO to the GPU
    glGenBuffers(1, &_iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Sprite::draw()
{
    // Setup
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // Position pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // Color pointer
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));


    // Draw stuff
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // Cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
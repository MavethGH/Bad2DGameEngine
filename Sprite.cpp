#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite() : _vboID(0), _iboID(0), _vaoID(0)
{

}

Sprite::~Sprite()
{
    // Free up space occupied by buffers
    if (_vboID) glDeleteBuffers(1, &_vboID);
    if (_iboID) glDeleteBuffers(1, &_iboID);
    if (_vaoID) glDeleteBuffers(1, &_vaoID);
}

void Sprite::init(float x, float y, float width, float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    // Create buffer to store Vertex Array Object
    if (!_vaoID) glGenBuffers(1, &_vaoID);

    // Create buffer to store Vertex Buffer Object
    if (!_vboID) glGenBuffers(1, &_vboID);

    // Create buffer to store Index Buffer Object
    if (!_iboID) glGenBuffers(1, &_iboID);

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
    vertexBufferData[0].uv = {0.0f, 1.0f};

    vertexBufferData[1].position = {trX, trY};
    vertexBufferData[1].uv = {1.0f, 1.0f};

    vertexBufferData[2].position = {blX, blY};
    vertexBufferData[2].uv = {0.0f, 0.0f};

    vertexBufferData[3].position = {brX, brY};
    vertexBufferData[3].uv = {1.0f, 0.0f};

    // Make them all white by default
    for (Vertex &v : vertexBufferData)
    {
        v.color = {255, 255, 255, 255};
    }

    // Create and bind Vertex Array Object
    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    // Upload VBO to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

    // Position pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // Color pointer
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // UV pointer
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    // Upload IBO to the GPU
    glGenBuffers(1, &_iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Sprite::draw()
{
    // Setup
    glBindVertexArray(_vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);

    // Draw stuff
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(const void *data, const unsigned int size)
{
    size_ = size;
    glGenBuffers(1, &id_);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer &&other)
{
    id_ = other.id_;
    other.id_ = 0;
}

VertexBuffer &VertexBuffer::operator=(VertexBuffer &&other)
{
    id_ = other.id_;
    other.id_ = 0;
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id_);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Update(const void *data, const unsigned int size)
{
    size_ = size;
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

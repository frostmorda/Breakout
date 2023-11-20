#include "index_buffer.h"

IndexBuffer::IndexBuffer(const void *data, const unsigned int size)
{
    glGenBuffers(1, &id_);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(IndexBuffer &&other)
{
    id_ = other.id_;
    other.id_ = 0;
}

IndexBuffer &IndexBuffer::operator=(IndexBuffer &&other)
{
    id_ = other.id_;
    other.id_ = 0;
    return *this;
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id_);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

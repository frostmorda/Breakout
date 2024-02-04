#include "vertex_array.h"
#include <iostream>

VertexArray::VertexArray(VertexBuffer *vertex_buffer, const VertexBufferLayout &layout)
{
    glGenVertexArrays(1, &id_);
    size_ = vertex_buffer->GetSize() / layout.GetStride();
    AddBuffer(vertex_buffer, layout);
}

VertexArray::VertexArray(VertexArray &&other) noexcept
{
    id_ = other.id_;
    size_ = other.size_;
    other.id_ = 0;
    other.size_ = 0;
}

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept
{
    id_ = other.id_;
    size_ = other.size_;
    other.id_ = 0;
    other.size_ = 0;
    return *this;
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id_);
}

void VertexArray::Bind() const
{
    glBindVertexArray(id_);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer *vertex_buffer, const VertexBufferLayout &layout)
{
    Bind();
    vertex_buffer->Bind();
    const auto &layout_buffer = layout.GetBufferLayout();
    GLbyte *offset = nullptr;
    for (unsigned int i = 0; i < layout_buffer.size(); ++i)
    {
        const auto &current_layout_buffer = layout_buffer[i];
        GLuint current_atrib_index = elements_count_ + i;
        glVertexAttribPointer(current_atrib_index, current_layout_buffer.size, current_layout_buffer.type, current_layout_buffer.normalize, layout.GetStride() * sizeof(float), offset);
        glEnableVertexAttribArray(current_atrib_index);
        offset += current_layout_buffer.size * sizeof(GLfloat);
    }
    elements_count_ += static_cast<unsigned int>(layout_buffer.size());
}

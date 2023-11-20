#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout() : stride_(0)
{
}

const unsigned int VertexBufferLayout::GetStride() const
{
    return stride_;
}

const std::vector<BufferLayout> &VertexBufferLayout::GetBufferLayout() const
{
    return buffer_layout_;
}

void VertexBufferLayout::AddBufferLayout(BufferLayout bl)
{
    buffer_layout_.push_back(bl);
    stride_ += bl.size;
}

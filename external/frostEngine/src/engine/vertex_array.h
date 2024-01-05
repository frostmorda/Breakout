#ifndef SRC_ENGINE_VERTEX_ARRAY_H_
#define SRC_ENGINE_VERTEX_ARRAY_H_

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

#include <glad/glad.h>
#include <memory>

class VertexArray
{
public:
    VertexArray() = delete;
    VertexArray(const VertexArray &) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray(VertexBuffer* vertex_buffer, const VertexBufferLayout &layout);
    VertexArray(VertexArray &&other) noexcept;
    VertexArray &operator=(VertexArray &&other) noexcept;
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    const unsigned int GetSize() const { return size_; }

private:
    unsigned int size_;
    GLuint id_;
};
#endif // SRC_ENGINE_VERTEX_ARRAY_H_

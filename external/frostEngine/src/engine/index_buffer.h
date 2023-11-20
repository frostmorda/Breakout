#ifndef SRC_ENGINE_INDEX_BUFFER_H_
#define SRC_ENGINE_INDEX_BUFFER_H_

#include <glad/glad.h>
class IndexBuffer
{
public:
    IndexBuffer() = delete;
    IndexBuffer(const IndexBuffer &) = delete;
    IndexBuffer &operator=(const IndexBuffer &) = delete;
    IndexBuffer(const void *data, const unsigned int size);
    IndexBuffer(IndexBuffer &&other);
    IndexBuffer &operator=(IndexBuffer &&other);
    ~IndexBuffer();
    void Bind();
    void Unbind();

private:
    GLuint id_;
};
#endif // SRC_ENGINE_INDEX_BUFFER_H_

#ifndef SRC_ENGINE_VERTEX_BUFFER_LAYOUT_H_
#define SRC_ENGINE_VERTEX_BUFFER_LAYOUT_H_

#include <glad/glad.h>
#include <vector>

struct BufferLayout
{
    GLint size;
    GLenum type;
    GLboolean normalize;
};
class VertexBufferLayout
{
public:
    VertexBufferLayout();
    const unsigned int GetStride() const;
    const std::vector<BufferLayout> &GetBufferLayout() const;
    void AddBufferLayout(BufferLayout bl);

private:
    std::vector<BufferLayout> buffer_layout_;
    unsigned int stride_;
};
#endif // SRC_ENGINE_VERTEX_BUFFER_LAYOUT_H_

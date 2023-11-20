#ifndef SRC_ENGINE_TEXTURE_H_
#define SRC_ENGINE_TEXTURE_H_

#include <string>
#include <glad/glad.h>

class Texture
{
public:
    Texture() = delete;
    Texture(const Texture &) = delete;
    Texture &operator=(Texture &other) = delete;
    Texture(const std::string &path, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT, GLuint min_filter = GL_LINEAR, GLuint mag_filte = GL_LINEAR);
    Texture(Texture &&other) noexcept;
    Texture &operator=(Texture &&other) noexcept;
    ~Texture() = default;
    void Bind() const;
    void Unbind() const;

private:
    GLuint id_;
    GLuint wrap_s_;
    GLuint wrap_t_;
    GLuint min_filter_;
    GLuint mag_filter_;
};
#endif // SRC_ENGINE_TEXTURE_H_

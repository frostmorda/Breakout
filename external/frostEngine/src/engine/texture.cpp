#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string &path, GLuint wrap_s, GLuint wrap_t, GLuint min_filter, GLuint mag_filter)
    : wrap_s_(wrap_s), wrap_t_(wrap_t), min_filter_(min_filter), mag_filter_(mag_filter)
{
    glGenTextures(1, &id_);
    int widht, height, chanel;
    unsigned char *data = stbi_load(path.c_str(), &widht, &height, &chanel, 0);
    if (data)
    {
        GLenum format;
        if (chanel == 1)
        {
            format = GL_RED;
        }
        else if (chanel == 3)
        {
            format = GL_RGB;
        }
        else if (chanel == 4)
        {
            format = GL_RGBA;
        }
        Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, format, widht, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_);
        Unbind();
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }
    stbi_image_free(data);
}

Texture::Texture(Texture &&other) noexcept
{
    id_ = other.id_;
    wrap_s_ = other.wrap_s_;
    wrap_t_ = other.wrap_t_;
    min_filter_ = other.min_filter_;
    mag_filter_ = other.mag_filter_;
    other.id_ = 0;
}

Texture &Texture::operator=(Texture &&other) noexcept
{
    id_ = other.id_;
    wrap_s_ = other.wrap_s_;
    wrap_t_ = other.wrap_t_;
    min_filter_ = other.min_filter_;
    mag_filter_ = other.mag_filter_;
    other.id_ = 0;
    return *this;
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

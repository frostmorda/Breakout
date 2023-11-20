#ifndef SRC_ENGINE_SHADER_H_
#define SRC_ENGINE_SHADER_H_

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader() = delete;
    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;
    Shader(const std::string &vertex_shader_source_file_path, const std::string &fragment_shader_source_file_path);
    Shader(Shader &&other) noexcept;
    Shader &operator=(Shader &&other) noexcept;
    void Use() const;
    void SetUniform(const std::string &name, float value) const;
    void SetUniform(const std::string &name, float first, float second) const;
    void SetUniform(const std::string &name, float first, float second, float third) const;
    void SetUniform(const std::string &name, float first, float second, float third, float fourth) const;
    void SetUniform(const std::string &name, bool value) const;
    void SetUniform(const std::string &name, int value) const;
    void SetUniform(const std::string &name, const glm::mat4 &matrix4) const;
    void SetUniform(const std::string &name, const glm::vec2 &vector2) const;
    void SetUniform(const std::string &name, const glm::vec3 &vector3) const;
    void SetUniform(const std::string &name, const glm::vec4 &vector4) const;
    ~Shader();

private:
    GLuint id_;
    GLuint CompileShader(const std::string &shader_source_file_path, const GLenum shader_type);
};

#endif // SRC_ENGINE_SHADER_H_

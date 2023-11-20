#include "shader.h"

Shader::Shader(const std::string &vertex_shader_source_file_path, const std::string &fragment_shader_source_file_path)
{
    GLuint vertex_shader = CompileShader(vertex_shader_source_file_path, GL_VERTEX_SHADER);
    GLuint fragment_shader = CompileShader(fragment_shader_source_file_path, GL_FRAGMENT_SHADER);
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_shader);
    glAttachShader(id_, fragment_shader);
    glLinkProgram(id_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::Shader(Shader &&other) noexcept
{
    id_ = other.id_;
    other.id_ = 0;
}

Shader &Shader::operator=(Shader &&other) noexcept
{
    glDeleteProgram(id_);
    id_ = other.id_;
    other.id_ = 0;
    return *this;
}

void Shader::Use() const
{
    glUseProgram(id_);
}

void Shader::SetUniform(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetUniform(const std::string &name, float first, float second) const
{
    glUniform2f(glGetUniformLocation(id_, name.c_str()), first, second);
}

void Shader::SetUniform(const std::string &name, float first, float second, float third) const
{
    glUniform3f(glGetUniformLocation(id_, name.c_str()), first, second, third);
}

void Shader::SetUniform(const std::string &name, float first, float second, float third, float fourth) const
{
    glUniform4f(glGetUniformLocation(id_, name.c_str()), first, second, third, fourth);
}

void Shader::SetUniform(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetUniform(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetUniform(const std::string &name, const glm::mat4 &matrix4) const
{
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &matrix4[0][0]);
}

void Shader::SetUniform(const std::string &name, const glm::vec2 &vector2) const
{
    SetUniform(name, vector2.x, vector2.y);
}

void Shader::SetUniform(const std::string &name, const glm::vec3 &vector3) const
{
    SetUniform(name, vector3.x, vector3.y, vector3.z);
}

void Shader::SetUniform(const std::string &name, const glm::vec4 &vector4) const
{
    SetUniform(name, vector4.x, vector4.y, vector4.z, vector4.w);
}

Shader::~Shader()
{
    glDeleteProgram(id_);
}

GLuint Shader::CompileShader(const std::string &shader_source_file_path, const GLenum shader_type)
{
    std::fstream file;
    file.open(shader_source_file_path);
    if (!file.is_open())
    {
        std::cerr << "Cant open file!!!" << std::endl;
    }
    std::stringstream buf;
    buf << file.rdbuf();
    file.close();
    GLuint shader;
    shader = glCreateShader(shader_type);
    std::string str = buf.str();
    const char *shader_source = str.c_str();
    glShaderSource(shader, 1, &shader_source, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar info_log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, info_log);
        std::cerr << "ERROR:SHADER:Shader compile error:\n"
                  << info_log << std::endl;
    }
    return shader;
}

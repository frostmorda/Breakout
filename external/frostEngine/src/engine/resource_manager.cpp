#include <fstream>
#include <sstream>
#include "resource_manager.h"

std::unordered_map<std::string, std::unique_ptr<Shader>> ResourceManager::shaders_;
std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::textures_;
std::unordered_map<std::string, std::unique_ptr<VertexArray>> ResourceManager::vertexes_ararays_;
std::unordered_map<std::string, std::unique_ptr<VertexBuffer>> ResourceManager::vertexes_buffers_;
std::unordered_map<std::string, std::unique_ptr<GameModel>> ResourceManager::game_models_;
std::unordered_map<std::string, std::vector<float>> ResourceManager::game_model_data_;
std::unordered_map<std::string, std::unique_ptr<Camera>> ResourceManager::camera_;
std::unordered_map<char, std::unique_ptr<GameModel>> ResourceManager::glyphs_;
std::string ResourceManager::executable_path_;

void ResourceManager::LoadShader(const std::string &shader_name, const std::string &vertex_shader_source_file_path, const std::string &fragment_shader_source_file_path)
{
    shaders_[shader_name] = std::make_unique<Shader>(vertex_shader_source_file_path, fragment_shader_source_file_path);
}

void ResourceManager::LoadShader(const std::string &shader_name, Shader shader)
{
    shaders_[shader_name] = std::make_unique<Shader>(std::move(shader));
}

Shader *ResourceManager::GetShader(const std::string &shader_name)
{
    return shaders_[shader_name].get();
}

void ResourceManager::LoadTexture(const std::string &texture_name, const std::string &path, int format, GLuint wrap_s, GLuint wrap_t, GLuint min_filter, GLuint mag_filte)
{
    textures_[texture_name] = std::make_unique<Texture>(path, format, wrap_s, wrap_t, min_filter, mag_filte);
}

void ResourceManager::LoadTexture(const std::string &texture_name, Texture texture)
{
    textures_[texture_name] = std::make_unique<Texture>(std::move(texture));
}

Texture *ResourceManager::GetTexture(const std::string &texture_name)
{
    return textures_[texture_name].get();
}

void ResourceManager::LoadVertexArray(const std::string &vertex_array_name, const std::string &vertex_buffer_name, const VertexBufferLayout &layout)
{
    auto vb = GetVertexBuffer(vertex_buffer_name);
    vertexes_ararays_[vertex_array_name] = std::make_unique<VertexArray>(vb, layout);
}

void ResourceManager::LoadVertexArray(const std::string &vertex_array_name, VertexArray vertex_array)
{
    vertexes_ararays_[vertex_array_name] = std::make_unique<VertexArray>(std::move(vertex_array));
}

VertexArray *ResourceManager::GetVertexArray(const std::string &vertex_array_name)
{
    return vertexes_ararays_[vertex_array_name].get();
}

void ResourceManager::LoadVertexBuffer(const std::string &vertex_buffer_name, const std::string &model_name)
{
    auto data = GetGameModelData(model_name);
    vertexes_buffers_[vertex_buffer_name] = std::make_unique<VertexBuffer>(data.data(), data.size());
}

void ResourceManager::LoadVertexBuffer(const std::string &vertex_buffer_name, const std::vector<float> &model_data)
{
    vertexes_buffers_[vertex_buffer_name] = std::make_unique<VertexBuffer>(model_data.data(), model_data.size());
}

VertexBuffer *ResourceManager::GetVertexBuffer(const std::string &vertex_buffer_name)
{
    return vertexes_buffers_[vertex_buffer_name].get();
}

void ResourceManager::LoadGameModel(const std::string &game_model_name, const std::string &shader_name, const std::string &texture_name, const std::string &vertex_array_name, const glm::vec3 &position, const glm::vec3 &size, const float rotation, const glm::vec3 &color, const std::string &model_matrix_name, const std::string &game_model_color_name, const std::string &texture_name_shader)
{
    game_models_[game_model_name] = std::make_unique<GameModel>(GetShader(shader_name), GetTexture(texture_name), GetVertexArray(vertex_array_name), position, size, rotation, color, model_matrix_name, game_model_color_name, texture_name_shader);
}

GameModel *ResourceManager::GetGameModel(const std::string &game_model_name)
{
    return game_models_[game_model_name].get();
}

void ResourceManager::LoadGlyphs(const std::string &glyphs_texture_path, const std::string &glyphs_file_path, const std::string &shader_name)
{
    LoadTexture("glyphs_texture", glyphs_texture_path, 4, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    std::vector<std::vector<char>> symbols;
    DataFromFile(glyphs_file_path, symbols);
    auto rows = symbols.size();
    auto columns = symbols[0].size();
    std::vector<float> model_data{
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f};
    LoadVertexBuffer("glyphs_buffer", model_data);
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t column = 0; column < columns; ++column)
        {
            float x1 = static_cast<float>(column) / columns;
            float y1 = static_cast<float>(row) / rows;
            float x2 = static_cast<float>(column + 1) / columns;
            float y2 = static_cast<float>(row + 1) / rows;
            std::vector<float> tex_coord{
                x1, y2,
                x2, y1,
                x1, y1,
                x1, y2,
                x2, y2,
                x2, y1};
            VertexBufferLayout vlo;
            BufferLayout bl{2, GL_FLOAT, GL_FALSE};
            vlo.AddBufferLayout(bl);
            std::string name = "glyphs_vertex_array_";
            name += symbols[row][column];
            LoadVertexArray(name, "glyphs_buffer", vlo);
            auto va = GetVertexArray(name);
            LoadVertexBuffer(name, tex_coord);
            va->AddBuffer(GetVertexBuffer(name), vlo);
            glyphs_[symbols[row][column]] = std::make_unique<GameModel>(GetShader(shader_name), GetTexture("glyphs_texture"), GetVertexArray(name), glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), 0, glm::vec3(1, 1, 1), "model", "color", "image");
        }
    }
}

GameModel *ResourceManager::GetGlyph(char symbol)
{
    return glyphs_[symbol].get();
}

void ResourceManager::SetExecutablePath(const std::string &executable_path)
{
    auto found = executable_path.find_last_of("/\\");
    executable_path_ = executable_path.substr(0, found) + "\\";
}

std::string ResourceManager::GetExecutablePath()
{
    return executable_path_;
}

void ResourceManager::LoadGameModelData(const std::string &modle_name, const std::string &path)
{
    std::vector<std::vector<float>> data;
    DataFromFile(path, data);
    for (auto &row : data)
    {
        for (auto &val : row)
        {
            game_model_data_[modle_name].push_back(val);
        }
    }
}

std::vector<float> ResourceManager::GetGameModelData(const std::string &modle_name)
{
    return game_model_data_[modle_name];
}

void ResourceManager::LoadCamera(const std::string &camera_name, glm::vec3 position, glm::vec3 world_up, float yaw, float pitch)
{
    camera_[camera_name] = std::make_unique<Camera>(position, world_up, yaw, pitch);
}

void ResourceManager::LoadCamera(const std::string &camera_name, float pos_x, float pos_y, float pos_z, float world_up_x, float world_up_y, float world_up_z, float yaw, float pitch)
{
    camera_[camera_name] = std::make_unique<Camera>(glm::vec3(pos_x, pos_y, pos_z), glm::vec3(world_up_x, world_up_y, world_up_z), yaw, pitch);
}

void ResourceManager::LoadCamera(const std::string &camera_name, Camera camera)
{
    camera_[camera_name] = std::make_unique<Camera>(std::move(camera));
}

Camera *ResourceManager::GetCamera(const std::string &camera_name)
{
    return camera_[camera_name].get();
}

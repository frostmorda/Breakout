#include <fstream>
#include <sstream>
#include "resource_manager.h"

std::unordered_map<std::string, std::shared_ptr<Shader>> ResourceManager::shaders_;
std::unordered_map<std::string, std::shared_ptr<Texture>> ResourceManager::textures_;
std::unordered_map<std::string, std::shared_ptr<VertexArray>> ResourceManager::vertexes_ararays_;
std::unordered_map<std::string, std::shared_ptr<VertexBuffer>> ResourceManager::vertexes_buffers_;
std::unordered_map<std::string, std::shared_ptr<GameModel>> ResourceManager::game_models_;
std::unordered_map<std::string, std::vector<float>> ResourceManager::game_model_data_;
std::unordered_map<std::string, std::shared_ptr<Camera>> ResourceManager::camera_;
std::string ResourceManager::executable_path_;

void ResourceManager::LoadShader(const std::string &shader_name, const std::string &vertex_shader_source_file_path, const std::string &fragment_shader_source_file_path)
{
    shaders_[shader_name] = std::make_shared<Shader>(vertex_shader_source_file_path, fragment_shader_source_file_path);
}

void ResourceManager::LoadShader(const std::string &shader_name, Shader shader)
{
    shaders_[shader_name] = std::make_shared<Shader>(std::move(shader));
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string &shader_name)
{
    return shaders_[shader_name];
}

void ResourceManager::LoadTexture(const std::string &texture_name, const std::string &path, GLuint wrap_s, GLuint wrap_t, GLuint min_filter, GLuint mag_filte)
{
    textures_[texture_name] = std::make_shared<Texture>(path, wrap_s, wrap_t, min_filter, mag_filte);
}

void ResourceManager::LoadTexture(const std::string &texture_name, Texture texture)
{
    textures_[texture_name] = std::make_shared<Texture>(std::move(texture));
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string &texture_name)
{
    return textures_[texture_name];
}

void ResourceManager::LoadVertexArray(const std::string &vertex_array_name, const std::string &vertex_buffer_name, const VertexBufferLayout &layout)
{
    auto vb = GetVertexBuffer(vertex_array_name);
    vertexes_ararays_[vertex_array_name] = std::make_shared<VertexArray>(std::move(vb), layout);
}

void ResourceManager::LoadVertexArray(const std::string &vertex_array_name, VertexArray vertex_array)
{
    vertexes_ararays_[vertex_array_name] = std::make_shared<VertexArray>(std::move(vertex_array));
}

std::shared_ptr<VertexArray> ResourceManager::GetVertexArray(const std::string &vertex_array_name)
{
    return vertexes_ararays_[vertex_array_name];
}

void ResourceManager::LoadVertexBuffer(const std::string &vertex_buffer_name, const std::string &model_name)
{
    auto data = GetGameModelData(model_name);
    vertexes_buffers_[vertex_buffer_name] = std::make_shared<VertexBuffer>(data.data(), data.size());
}

std::shared_ptr<VertexBuffer> ResourceManager::GetVertexBuffer(const std::string &vertex_buffer_name)
{
    return vertexes_buffers_[vertex_buffer_name];
}

void ResourceManager::LoadGameModel(const std::string &game_model_name, const std::string &shader_name, const std::string &texture_name, const std::string &vertex_array_name, const glm::vec3 &position, const glm::vec3 &size, const float rotation, const glm::vec3 &color, const std::string &model_matrix_name, const std::string &game_model_color_name, const std::string &texture_name_shader)
{
    game_models_[game_model_name] = std::make_shared<GameModel>(GetShader(shader_name), GetTexture(texture_name), GetVertexArray(vertex_array_name), position, size, rotation, color, model_matrix_name, game_model_color_name, texture_name_shader);
}

std::shared_ptr<GameModel> ResourceManager::GetGameModel(const std::string &game_model_name)
{
    return game_models_[game_model_name];
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
    std::ifstream f;
    f.open(path);
    if (!f.is_open())
    {
        std::cerr << "not open!" << std::endl;
        return;
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    std::string data = buffer.str();
    f.close();
    size_t found = 0;
    size_t start = 0;

    while (found != std::string::npos)
    {
        std::string num = data.substr(start);
        if (isdigit(num[0]) || num[0] == '-')
        {
            float val = stof(num);
            std::cout << val << " ";
            game_model_data_[modle_name].push_back(val);
        }
        found = data.find_first_of(" \n", found + 1);
        start = found + 1;
    }
}

std::vector<float> ResourceManager::GetGameModelData(const std::string &modle_name)
{
    return game_model_data_[modle_name];
}

void ResourceManager::LoadCamera(const std::string &camera_name, glm::vec3 position, glm::vec3 world_up, float yaw, float pitch)
{
    camera_[camera_name] = std::make_shared<Camera>(position, world_up, yaw, pitch);
}

void ResourceManager::LoadCamera(const std::string &camera_name, float pos_x, float pos_y, float pos_z, float world_up_x, float world_up_y, float world_up_z, float yaw, float pitch)
{
    camera_[camera_name] = std::make_shared<Camera>(glm::vec3(pos_x, pos_y, pos_z), glm::vec3(world_up_x, world_up_y, world_up_z), yaw, pitch);
}

void ResourceManager::LoadCamera(const std::string &camera_name, Camera camera)
{
    camera_[camera_name] = std::make_shared<Camera>(std::move(camera));
}

std::shared_ptr<Camera> &ResourceManager::GetCamera(const std::string &camera_name)
{
    return camera_[camera_name];
}

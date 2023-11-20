#ifndef SRC_ENGINE_RESOURCE_MANAGER_H_
#define SRC_ENGINE_RESOURCE_MANAGER_H_

#include <unordered_map>
#include <memory>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "camera.h"
#include "game_model.h"

class ResourceManager
{
public:
    ResourceManager() = delete;
    static void LoadShader(const std::string &shader_name, const std::string &vertex_shader_source_file_path, const std::string &fragment_shader_source_file_path);
    static void LoadShader(const std::string &shader_name, Shader shader);
    static std::shared_ptr<Shader> GetShader(const std::string &shader_name);

    static void LoadTexture(const std::string &texture_name, const std::string &path, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT, GLuint min_filter = GL_LINEAR, GLuint mag_filte = GL_LINEAR);
    static void LoadTexture(const std::string &texture_name, Texture texture);
    static std::shared_ptr<Texture> GetTexture(const std::string &texture_name);

    static void LoadVertexArray(const std::string &vertex_array_name, const std::string &vertex_buffer_name, const VertexBufferLayout &layout);
    static void LoadVertexArray(const std::string &vertex_array_name, VertexArray vertex_array);
    static std::shared_ptr<VertexArray> GetVertexArray(const std::string &vertex_array_name);

    static void LoadVertexBuffer(const std::string &vertex_buffer_name, const std::string &model_name);
    static std::shared_ptr<VertexBuffer> GetVertexBuffer(const std::string &vertex_buffer_name);

    static void LoadGameModel(const std::string &game_model_name, const std::string &shader_name, const std::string &texture_name, const std::string &vertex_array_name, const glm::vec3 &position, const glm::vec3 &size, const float rotation, const glm::vec3 &color, const std::string &model_matrix_name, const std::string &game_model_color_name);
    static std::shared_ptr<GameModel> GetGameModel(const std::string &game_model_name);

    static void SetExecutablePath(const std::string &executable_path);
    static std::string GetExecutablePath();

    static void LoadGameModelData(const std::string &modle_name, const std::string &path);
    static std::vector<float> GetGameModelData(const std::string &modle_name);

    static void LoadCamera(const std::string &camera_name, glm::vec3 position = kPosition, glm::vec3 world_up = kWorldUp, float yaw = kYaw, float pitch = kPitch);
    static void LoadCamera(const std::string &camera_name, float pos_x, float pos_y, float pos_z, float world_up_x, float world_up_y, float world_up_z, float yaw, float pitch);
    static void LoadCamera(const std::string &camera_name, Camera camera);
    static std::shared_ptr<Camera> &GetCamera(const std::string &camera_name);

private:
    static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_;
    static std::unordered_map<std::string, std::shared_ptr<Texture>> textures_;
    static std::unordered_map<std::string, std::shared_ptr<VertexArray>> vertexes_ararays_;
    static std::unordered_map<std::string, std::shared_ptr<VertexBuffer>> vertexes_buffers_;
    static std::unordered_map<std::string, std::shared_ptr<GameModel>> game_models_;
    static std::unordered_map<std::string, std::vector<float>> game_model_data_;
    static std::unordered_map<std::string, std::shared_ptr<Camera>> camera_;
    static std::string executable_path_;
};
#endif // SRC_ENGINE_RESOURCE_MANAGER_H_
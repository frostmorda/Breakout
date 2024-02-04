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
    static Shader *GetShader(const std::string &shader_name);

    static void LoadTexture(const std::string &texture_name, const std::string &path, int format = 0, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT, GLuint min_filter = GL_LINEAR, GLuint mag_filte = GL_LINEAR);
    static void LoadTexture(const std::string &texture_name, Texture texture);
    static Texture *GetTexture(const std::string &texture_name);

    static void LoadVertexArray(const std::string &vertex_array_name, const std::string &vertex_buffer_name, const VertexBufferLayout &layout);
    static void LoadVertexArray(const std::string &vertex_array_name, VertexArray vertex_array);
    static VertexArray *GetVertexArray(const std::string &vertex_array_name);

    static void LoadVertexBuffer(const std::string &vertex_buffer_name, const std::string &model_name);
    static void LoadVertexBuffer(const std::string &vertex_buffer_name, const std::vector<float> &model_data);
    static VertexBuffer *GetVertexBuffer(const std::string &vertex_buffer_name);

    static void LoadGameModel(const std::string &game_model_name, const std::string &shader_name, const std::string &texture_name, const std::string &vertex_array_name, const glm::vec3 &position, const glm::vec3 &size, const float rotation, const glm::vec3 &color, const std::string &model_matrix_name, const std::string &game_model_color_name, const std::string &texture_name_shader);
    static GameModel *GetGameModel(const std::string &game_model_name);

    static void LoadGlyphs(const std::string &glyphs_texture_path, const std::string &glyphs_file_path, const std::string &shader_name);
    static GameModel *GetGlyph(char symbol);

    static void SetExecutablePath(const std::string &executable_path);
    static std::string GetExecutablePath();

    static void LoadGameModelData(const std::string &modle_name, const std::string &path);
    static std::vector<float> GetGameModelData(const std::string &modle_name);

    static void LoadCamera(const std::string &camera_name, glm::vec3 position = kPosition, glm::vec3 world_up = kWorldUp, float yaw = kYaw, float pitch = kPitch);
    static void LoadCamera(const std::string &camera_name, float pos_x, float pos_y, float pos_z, float world_up_x, float world_up_y, float world_up_z, float yaw, float pitch);
    static void LoadCamera(const std::string &camera_name, Camera camera);
    static Camera *GetCamera(const std::string &camera_name);

    template <class T>
    static inline void DataFromFile(const std::string &file_path, std::vector<std::vector<T>> &data)
    {
        std::ifstream file(file_path);
        std::string line;
        if (file)
        {

            while (std::getline(file, line))
            {
                std::istringstream string_stream(line);
                T val;
                std::vector<T> row;
                while (string_stream >> val)
                {
                    row.push_back(val);
                }
                data.push_back(row);
            }
        }
        else
        {
            std::cerr << "Cant find file!" << std::endl;
        }
    }

private:
    static std::unordered_map<std::string, std::unique_ptr<Shader>> shaders_;
    static std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;
    static std::unordered_map<std::string, std::unique_ptr<VertexArray>> vertexes_ararays_;
    static std::unordered_map<std::string, std::unique_ptr<VertexBuffer>> vertexes_buffers_;
    static std::unordered_map<std::string, std::unique_ptr<GameModel>> game_models_;
    static std::unordered_map<std::string, std::vector<float>> game_model_data_;
    static std::unordered_map<std::string, std::unique_ptr<Camera>> camera_;
    static std::unordered_map<char, std::unique_ptr<GameModel>> glyphs_;
    static std::string executable_path_;
};
#endif // SRC_ENGINE_RESOURCE_MANAGER_H_

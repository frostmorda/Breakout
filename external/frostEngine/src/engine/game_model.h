#ifndef SRC_ENGINE_GAME_MODEL_H_
#define SRC_ENGINE_GAME_MODEL_H_

#include <memory>
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"

class GameModel
{
public:
    GameModel();
    GameModel(Shader *shader, Texture *texture, VertexArray *vertex_array, const glm::vec3 &position, const glm::vec3 &size, const float rotation, const glm::vec3 &color, const std::string &model_matrix_name, const std::string &game_model_color_name, const std::string &texture_name);
    GameModel(const GameModel &other) = delete;
    GameModel &operator=(const GameModel &other) = delete;
    GameModel(GameModel &&other);
    GameModel &operator=(GameModel &&other);
    ~GameModel();
    void Draw();
    void SetShader(Shader *shader);
    void SetTexture(Texture *texture);
    void SetVertexArray(VertexArray *vertex_array);
    void SetPosition(const glm::vec3 &position);
    void SetSize(const glm::vec3 &size);
    void SetRotation(const float rotation);
    void SetColor(const glm::vec3 &color);

private:
    Shader *shader_;
    Texture *texture_;
    VertexArray *vertex_array_;
    glm::vec3 position_;
    glm::vec3 size_;
    float rotation_;
    glm::vec3 color_;
    std::string model_matrix_name_;
    std::string game_model_color_name_;
    std::string texture_name_;
    void Transformation();
};
#endif // SRC_ENGINE_GAME_MODEL_H_

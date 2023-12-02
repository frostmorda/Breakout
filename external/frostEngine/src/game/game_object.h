#ifndef SRC_GAME_GAME_OBJECT_H_
#define SRC_GAME_GAME_OBJECT_H_

#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "../engine/game_model.h"
class GameObject
{
public:
    GameObject(std::shared_ptr<GameModel> game_model, glm::vec3 position, glm::vec3 size, glm::vec3 color, float rotation = 0.f);
    ~GameObject();
    void Draw();
    void SetPosition(glm::vec3 position) { position_ = position; }
    void SetSize(glm::vec3 size) { size_ = size; }
    void SetColor(glm::vec3 color) { color_ = color; }

private:
    void Update();
    glm::vec3 position_;
    glm::vec3 size_;
    glm::vec3 color_;
    float rotation_;
    std::shared_ptr<GameModel> game_model_;
};
#endif // SRC_GAME_GAME_OBJECT_H_

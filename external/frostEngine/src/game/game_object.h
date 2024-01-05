#ifndef SRC_GAME_GAME_OBJECT_H_
#define SRC_GAME_GAME_OBJECT_H_

#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "../engine/game_model.h"
class GameObject
{
public:
    GameObject(GameModel* game_model, glm::vec3 position, glm::vec3 size, glm::vec3 color, float rotation = 0.f);
    ~GameObject();
    void Draw();

    void SetPosition(glm::vec3 position) { position_ = position; }
    const glm::vec3 GetPosition() const { return position_; }

    void SetSize(glm::vec3 size) { size_ = size; }
    const glm::vec3 GetSize() const { return size_; }

    void SetColor(glm::vec3 color) { color_ = color; }
    const glm::vec3 GetColor() const { return color_; }

    void Destroy() { is_destroyed = true; }
    const bool IsDestroyed() { return is_destroyed; }

private:
    void Update();
    glm::vec3 position_;
    glm::vec3 size_;
    glm::vec3 color_;
    float rotation_;
    GameModel* game_model_;
    bool is_destroyed = false;
};
#endif // SRC_GAME_GAME_OBJECT_H_

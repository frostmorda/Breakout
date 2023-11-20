#ifndef SRC_GAME_GAME_OBJECT_H_
#define SRC_GAME_GAME_OBJECT_H_

#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "../engine/game_model.h"
class GameObject
{
public:
    GameObject(std::shared_ptr<GameModel> GameModel);
    ~GameObject();
    void Draw();

private:
    std::shared_ptr<GameModel> game_model_;
};
#endif // SRC_GAME_GAME_OBJECT_H_

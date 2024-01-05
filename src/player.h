#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "../external/frostEngine/src/game/game_object.h"

class Player : public GameObject
{
public:
    Player(GameModel* game_model, glm::vec3 position, glm::vec3 size, glm::vec3 color, float velocity, float rotation = 0.f) : GameObject(game_model, position, size, color, rotation), velocity_(velocity) {}
    ~Player() {}
    const float GetVelocity() const { return velocity_; }
    void SetVelocity(float velocity) { velocity_ = velocity; }
    void MoveLeft(float dt);
    void MoveRight(float width, float dt);

private:
    float velocity_;
};
#endif // SRC_PLAYER_H_

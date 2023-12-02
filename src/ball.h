#ifndef SRC_BALL_H_
#define SRC_BALL_H_

#include "../external/frostEngine/src/game/game_object.h"

class Ball : public GameObject
{
public:
    Ball(std::shared_ptr<GameModel> game_model, glm::vec3 position, float radius, glm::vec3 color, glm::vec2 velocity, float rotation = 0.f) : GameObject(game_model, position, glm::vec3(radius * 2, radius * 2, 0), color), velocity_(velocity), radius_(radius) {}
    const bool IsStuck() const { return stuck_; }
    void StuckState(bool stuck_state) { stuck_ = stuck_state; }
    void Move(float dt, unsigned int width);

private:
    glm::vec2 velocity_;
    float radius_;
    bool stuck_ = true;
};

#endif // SRC_BALL_H_

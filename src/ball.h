#ifndef SRC_BALL_H_
#define SRC_BALL_H_

#include "../external/frostEngine/src/game/game_object.h"

class Ball : public GameObject
{
public:
    Ball(GameModel *game_model, glm::vec3 position, float radius, glm::vec3 color, glm::vec2 velocity, float rotation = 0.f) : GameObject(game_model, position, glm::vec3(radius * 2, radius * 2, 0), color), velocity_(velocity), radius_(radius) {}
    const bool IsStuck() const { return stuck_; }
    void StuckState(bool stuck_state) { stuck_ = stuck_state; }
    void Move(float dt, unsigned int width, unsigned int height);
    const glm::vec2 GetVelocity() const { return velocity_; }
    void SetVelocity(glm::vec2 velocity) { velocity_ = velocity; }
    bool IsBallOut() { return ball_out_; }
    void BallOutState(bool ball_out_state) { ball_out_ = ball_out_state; }

private:
    glm::vec2 velocity_;
    float radius_;
    bool stuck_ = true;
    bool ball_out_ = false;
};

#endif // SRC_BALL_H_

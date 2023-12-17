#ifndef SRC_GAME_COLLISION_H_
#define SRC_GAME_COLLISION_H_

#include "game_object.h"
#include <tuple>
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
using CollisionInfo = std::tuple<bool, Direction, glm::vec2>;
class Collision
{
public:
    Collision() = delete;
    static CollisionInfo CheckBoxCollision(const std::shared_ptr<GameObject> &first, const std::shared_ptr<GameObject> &second);

private:
    static Direction VectorDirection(glm::vec2 target);
};
#endif // SRC_GAME_COLLISION_H_

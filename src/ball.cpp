#include "ball.h"

void Ball::Move(float dt, unsigned int width)
{
    auto velocity = dt * velocity_;
    auto position = GetPosition();
    position.x += velocity.x;
    position.y += velocity.y;
    if (position.x <= 0)
    {
        velocity_.x = -velocity_.x;
        position.x = 0;
    }
    else if (position.x >= width - GetSize().x)
    {
        velocity_.x = -velocity_.x;
        position.x = width - GetSize().x;
    }
    if (position.y <= 0)
    {
        velocity_.y = -velocity_.y;
        position.y = 0;
    }
    SetPosition(position);
}

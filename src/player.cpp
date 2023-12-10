#include "player.h"

void Player::MoveLeft(float dt)
{
    auto position = GetPosition();
    if (position.x >= 0)
    {
        position.x -= velocity_ * dt;
        SetPosition(position);
    }
}

void Player::MoveRight(float width, float dt)
{
    auto position = GetPosition();
    if (position.x <= width - GetSize().x)
    {
        position.x += velocity_ * dt;
        SetPosition(position);
    }
}

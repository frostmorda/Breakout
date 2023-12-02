#include "player.h"

void Player::MoveLeft()
{
    auto position = GetPosition();
    if (position.x >= 0)
    {
        position.x -= velocity_;
        SetPosition(position);
    }
}

void Player::MoveRight(float width)
{
    auto position = GetPosition();
    if (position.x <= width - GetSize().x)
    {
        position.x += velocity_;
        SetPosition(position);
    }
}

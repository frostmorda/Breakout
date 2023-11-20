#include "game_object.h"

GameObject::GameObject(std::shared_ptr<GameModel> game_model) : game_model_(game_model)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
    game_model_->Draw();
}

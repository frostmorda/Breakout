#include "game_object.h"

GameObject::GameObject(std::shared_ptr<GameModel> game_model, glm::vec3 position, glm::vec3 size, glm::vec3 color, float rotation)
    : game_model_(game_model), position_(position), size_(size), color_(color), rotation_(rotation)
{
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
    Update();
    game_model_->Draw();
}

void GameObject::Update()
{
    game_model_->SetPosition(position_);
    game_model_->SetSize(size_);
    game_model_->SetRotation(rotation_);
    game_model_->SetColor(color_);
}

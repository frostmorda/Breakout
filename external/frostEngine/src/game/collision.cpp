#include "collision.h"

CollisionInfo Collision::CheckBoxCollision(GameObject *first, GameObject *second)
{
    glm::vec2 first_center(first->GetPosition().x + first->GetSize().x / 2, first->GetPosition().y + first->GetSize().y / 2);
    glm::vec2 second_center(second->GetPosition().x + second->GetSize().x / 2, second->GetPosition().y + second->GetSize().y / 2);
    glm::vec2 difference = first_center - second_center;
    glm::vec2 clamped = glm::clamp(difference, -glm::vec2(second->GetSize().x / 2, second->GetSize().y / 2), glm::vec2(second->GetSize().x / 2, second->GetSize().y / 2));
    glm::vec2 closest = second_center + clamped;
    difference = closest - first_center;
    if (glm::length(difference) < glm::length(glm::vec2(first->GetSize().x / 2, first->GetSize().y / 2)))
    {
        return std::make_tuple(true, VectorDirection(difference), difference);
    }
    return std::make_tuple(false, Direction::UP, glm::vec2(0, 0));
}

Direction Collision::VectorDirection(glm::vec2 target)
{
    std::vector<glm::vec2> direction{
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, -1.0f),
        glm::vec2(-1.0f, 0.0f),
        glm::vec2(1.0f, 0.0f)};
    float max = 0;
    int index_direction = -1;
    for (int i = 0; i < direction.size(); ++i)
    {
        float dot_product = glm::dot(glm::normalize(target), direction[i]);
        if (dot_product > max)
        {
            max = dot_product;
            index_direction = i;
        }
    }
    return static_cast<Direction>(index_direction);
}

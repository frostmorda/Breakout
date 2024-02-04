#include "text.h"

Text::Text(const std::string &text, const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color) : text_(text), position_(position), size_(size), color_(color)
{
}

void Text::Draw()
{
    for (int i = 0; i < text_.size(); ++i)
    {
        auto letter_position = position_;
        letter_position.x += i * size_.x;
        auto letter = ResourceManager::GetGlyph(text_[i]);
        letter->SetPosition(letter_position);
        letter->SetSize(size_);
        letter->SetColor(color_);
        letter->Draw();
    }
}

void Text::SetText(const std::string &text)
{
    text_ = text;
}

void Text::SetPosition(const glm::vec3 &position)
{
    position_ = position;
}

void Text::SetSize(const glm::vec3 &size)
{
    size_ = size;
}

void Text::SetColor(const glm::vec3 &color)
{
    color_ = color;
}

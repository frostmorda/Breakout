#ifndef SRC_ENGINE_TEXT_H_
#define SRC_ENGINE_TEXT_H_
#include "resource_manager.h"

class Text
{
public:
    Text() = delete;
    Text(const std::string &text, const glm::vec3 &position = glm::vec3(0, 0, 0), const glm::vec3 &size = glm::vec3(30, 60, 0), const glm::vec3 &color = glm::vec3(1, 1, 1));
    void Draw();
    void SetText(const std::string &text);
    void SetPosition(const glm::vec3 &position);
    void SetSize(const glm::vec3 &size);
    void SetColor(const glm::vec3 &color);

private:
    std::string text_;
    glm::vec3 position_;
    glm::vec3 size_;
    glm::vec3 color_;
};

#endif // SRC_ENGINE_TEXT_H_

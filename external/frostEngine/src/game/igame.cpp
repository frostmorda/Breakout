#include "igame.h"

IGame::IGame(const unsigned int width, const unsigned int height, const std::string &window_name) : width_(width), height_(height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    if (!window_)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window_);
    if (!gladLoadGL())
    {
        std::cerr << "Failed initialize GLAD" << std::endl;
    }
    glViewport(0, 0, width_, height_);
}

IGame::IGame() : IGame(kDefaultWidgth, kDefaultHeight, kDefaultWindowName)
{
}

IGame::~IGame()
{
    glfwTerminate();
}

const bool IGame::IsWindowClosed() const
{
    return !glfwWindowShouldClose(window_);
}

bool IGame::CheckBoxCollision(const std::shared_ptr<GameObject> &first, const std::shared_ptr<GameObject> &second)
{
    bool collision_x_axis = first->GetPosition().x + first->GetSize().x >= second->GetPosition().x && second->GetPosition().x + second->GetSize().x >= first->GetPosition().x;
    bool collision_y_axis = first->GetPosition().y + first->GetSize().y >= second->GetPosition().y && second->GetPosition().y + second->GetSize().y >= first->GetPosition().y;
    return collision_x_axis && collision_y_axis;
}

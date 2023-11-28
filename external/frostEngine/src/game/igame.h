#ifndef SRC_GAME_IGAME_H_
#define SRC_GAME_IGAME_H_

#include "game_object.h"
#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_PAUSE,
    GAME_WIN,
    GAME_LOSE
};
const unsigned int kDefaultHeight = 600;
const unsigned int kDefaultWidgth = 800;
const std::string kDefaultWindowName = "Default Window";
class IGame
{
public:
    IGame(const unsigned int width, const unsigned int height, const std::string &window_name);
    IGame();
    virtual ~IGame();
    virtual void Initialization() = 0;
    virtual void ProcessInpud() = 0;
    virtual void Update(float delta_time) = 0;
    virtual void Render() = 0;

    GLFWwindow *GetWindow() { return window_; }

    const float GetLastFrame() const { return last_frame_; }
    void SetLastFrame(float frame) { last_frame_ = frame; }

    const float GetDeltaTime() const { return delta_time_; }
    void SetDeltaTime(float delta_time) { delta_time_ = delta_time; }

    const int GetWidth() const { return width_; }
    const int GetHeight() const { return height_; }

    const bool IsWindowClosed() const;

private:
    unsigned int width_;
    unsigned int height_;
    GameState state_;
    bool Keys[1024];
    std::unordered_map<std::string, std::shared_ptr<GameObject>> game_objects_;
    GLFWwindow *window_;
    float last_frame_ = 0;
    float delta_time_ = 0;
};
#endif // SRC_GAME_IGAME_H_

#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include "../external/frostEngine/src/game/igame.h"
#include "../external/frostEngine/src/engine/resource_manager.h"

class Game : public IGame
{
public:
    Game() : IGame() {}
    Game(const unsigned int width, const unsigned int height, const std::string &window_name) : IGame(width, height, window_name) {}
    ~Game() {}
    void Initialization() override;
    void ProcessInpud() override;
    void Update(float delta_time) override{};
    void Render() override;
};

#endif // SRC_GAME_H_

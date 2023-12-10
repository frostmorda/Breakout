#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include "../external/frostEngine/src/game/igame.h"
#include "../external/frostEngine/src/engine/resource_manager.h"
#include "game_level.h"
#include "player.h"
#include "ball.h"

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
    void Collision() override;

private:
    std::shared_ptr<Player> player_;
    std::shared_ptr<GameLevel> game_level_;
    std::shared_ptr<Ball> ball_;
    void BallCollusion(std::shared_ptr<GameObject> game_object);
};

#endif // SRC_GAME_H_

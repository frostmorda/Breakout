#ifndef SRC_GAME_LEVEL_H_
#define SRC_GAME_LEVEL_H_
#include "../external/frostEngine/src/engine/resource_manager.h"
#include "../external/frostEngine/src/game/game_object.h"

class GameLevel
{
public:
    GameLevel(std::string &file_path, std::shared_ptr<GameModel> game_model, unsigned int level_width, unsigned int level_height);
    ~GameLevel() {}
    void Draw();

private:
    std::vector<GameObject> objects_;
};

#endif // SRC_GAME_LEVEL_H_

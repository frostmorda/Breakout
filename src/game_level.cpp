#include "game_level.h"

GameLevel::GameLevel(std::string &file_path, std::shared_ptr<GameModel> game_model, unsigned int level_width, unsigned int level_height)
{
    std::vector<std::vector<unsigned int>> data;
    ResourceManager::DataFromFile(file_path, data);
    for (int i = 0; i < data.size(); ++i)
    {
        for (int j = 0; j < data[0].size(); j++)
        {
            if (data[i][j] > 0)
            {
                glm::vec3 position(level_width / data[0].size() * j, level_height / data.size() * i, 0);
                glm::vec3 size(level_width / data[0].size(), level_height / data.size(), 0);
                glm::vec3 color;
                if (data[i][j] == 1)
                {
                    color = glm::vec3(0.976f, 0.22f, 0.04f);
                }
                else if (data[i][j] == 2)
                {
                    color = glm::vec3(0.675f, 0.486f, 0);
                }
                else if (data[i][j] == 3)
                {
                    color = glm::vec3(1, 0.643f, 0.255f);
                }
                objects_.push_back(std::make_shared<GameObject>(game_model, position, size, color));
            }
        }
    }
}

void GameLevel::Draw()
{
    for (auto &block : objects_)
    {
        block->Draw();
    }
}

#include "game.h"
#include "../external/frostEngine/src/game/collision.h"

void WindowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Game::Initialization()
{
    ResourceManager::LoadGameModelData("block", ResourceManager::GetExecutablePath() + "res/models/block");
    VertexBufferLayout vlo;
    BufferLayout bl{2, GL_FLOAT, GL_FALSE};
    vlo.AddBufferLayout(bl);
    vlo.AddBufferLayout(bl);
    ResourceManager::LoadVertexBuffer("block", "block");
    ResourceManager::LoadVertexArray("block", "block", vlo);
    ResourceManager::LoadShader("block", ResourceManager::GetExecutablePath() + "res/shaders/block_vertex_shader.glsl", ResourceManager::GetExecutablePath() + "res/shaders/block_fragment_shader.glsl");
    ResourceManager::LoadTexture("block", ResourceManager::GetExecutablePath() + "res/textures/block.png");
    ResourceManager::LoadTexture("background", ResourceManager::GetExecutablePath() + "res/textures/background.png");
    ResourceManager::LoadGameModel("block", "block", "block", "block", glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), 0, glm::vec3(0.3f, 0.5f, 0.7f), "model", "color", "image");
    ResourceManager::LoadGameModel("background", "block", "background", "block", glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), 0, glm::vec3(0.3f, 0.5f, 0.7f), "model", "color", "image");
    auto gm = ResourceManager::GetGameModel("block");
    auto bg = ResourceManager::GetGameModel("background");

    game_level_ = std::make_unique<GameLevel>(ResourceManager::GetExecutablePath() + "/res/levels/level1", gm, GetWidth(), GetHeight() / 2);
    player_ = std::make_unique<Player>(gm, glm::vec3(GetWidth() / 2.f - 37.5f, GetHeight() - 10.f, 0), glm::vec3(75, 10, 0), glm::vec3(0.2f, 0.5f, 0.4f), 200);
    ball_ = std::make_unique<Ball>(gm, player_->GetPosition() - glm::vec3(-player_->GetSize().x / 2 + 7, 14, 0), 7.0f, glm::vec3(1, 1, 0), glm::vec2(-300.f));
    background_ = std::make_unique<GameObject>(bg, glm::vec3(0, 0, 0), glm::vec3(GetWidth(), GetHeight(), 0), glm::vec3(1, 1, 1));

    glfwSetFramebufferSizeCallback(GetWindow(), WindowSizeCallback);
}

void Game::ProcessInpud()
{
    if (glfwGetKey(GetWindow(), GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(GetWindow(), true);
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_A) || glfwGetKey(GetWindow(), GLFW_KEY_LEFT))
    {
        player_->MoveLeft(GetDeltaTime());
        if (ball_->IsStuck())
        {
            ball_->SetPosition(player_->GetPosition() - glm::vec3(-player_->GetSize().x / 2 + 7, 14, 0));
        }
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_D) || glfwGetKey(GetWindow(), GLFW_KEY_RIGHT))
    {
        player_->MoveRight(GetWidth(), GetDeltaTime());
        if (ball_->IsStuck())
        {
            ball_->SetPosition(player_->GetPosition() - glm::vec3(-player_->GetSize().x / 2 + 7, 14, 0));
        }
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_SPACE))
    {
        ball_->StuckState(false);
    }
}

void Game::Render()
{
    glClearColor(0, 0, 0, 1.f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float curent_frame = glfwGetTime();
    SetDeltaTime(curent_frame - GetLastFrame());
    SetLastFrame(curent_frame);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()), 0.0f, -1.0f, 1.0f);
    auto shader = ResourceManager::GetShader("block");
    shader->Use();
    shader->SetUniform("projection", projection);

    if (!ball_->IsStuck() && player_->GetHealth() > 0)
    {
        ball_->Move(GetDeltaTime(), GetWidth(), GetHeight());
        Collision();
        if (ball_->IsBallOut())
        {
            player_->LoseHealth();
            ball_->StuckState(true);
            ball_->BallOutState(false);
            ball_->SetPosition(player_->GetPosition() - glm::vec3(-player_->GetSize().x / 2 + 7, 14, 0));
        }
    }
    ball_->Draw();
    game_level_->Draw();
    player_->Draw();
    background_->Draw();

    glfwSwapBuffers(GetWindow());
    glfwPollEvents();
}

void Game::Collision()
{
    BallCollision(player_.get());
    for (auto &block : game_level_->GetGameObjectsList())
    {
        if (!block->IsDestroyed())
        {
            BallCollision(block.get());
        }
    }
}

void Game::BallCollision(GameObject *game_object)
{
    CollisionInfo col_info = Collision::CheckBoxCollision(ball_.get(), game_object);
    if (std::get<0>(col_info))
    {
        if (game_object != player_.get())
        {
            game_object->Destroy();
        }
        if (std::get<1>(col_info) == Direction::LEFT || std::get<1>(col_info) == Direction::RIGHT)
        {
            glm::vec2 velocity(-ball_->GetVelocity().x, ball_->GetVelocity().y);
            ball_->SetVelocity(velocity);
        }
        else
        {
            ball_->SetVelocity(-ball_->GetVelocity());
            if (game_object == player_.get())
            {
                float player_center = player_->GetPosition().x + player_->GetSize().x / 2;
                float distance = ball_->GetPosition().x + ball_->GetSize().x / 2 - player_center;
                float ball_velocity_x;
                if (distance > 0)
                {
                    ball_velocity_x = -ball_->GetVelocity().x;
                }
                else
                {
                    ball_velocity_x = ball_->GetVelocity().x;
                }
                float ball_velocity_y = -glm::abs(ball_->GetVelocity().y);
                ball_->SetVelocity(glm::vec2(ball_velocity_x, ball_velocity_y));
            }
        }
    }
}

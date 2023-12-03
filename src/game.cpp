#include "game.h"

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
    ResourceManager::LoadGameModel("block", "block", "block", "block", glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), 0, glm::vec3(0.3f, 0.5f, 0.7f), "model", "color", "image");
    auto gm = ResourceManager::GetGameModel("block");

    game_level_ = std::make_shared<GameLevel>(ResourceManager::GetExecutablePath() + "/res/levels/level1", gm, GetWidth(), GetHeight() / 2);
    player_ = std::make_shared<Player>(gm, glm::vec3(GetWidth() / 2.f - 37.5f, GetHeight() - 10.f, 0), glm::vec3(75, 10, 0), glm::vec3(0.2f, 0.5f, 0.4f), 5);
    ball_ = std::make_shared<Ball>(gm, player_->GetPosition() - glm::vec3(-player_->GetSize().x / 2 + 7, 14, 0), 7.0f, glm::vec3(1, 1, 0), glm::vec2(-100.f));

    glfwSetFramebufferSizeCallback(GetWindow(), WindowSizeCallback);
}

void Game::ProcessInpud()
{
    if (glfwGetKey(GetWindow(), GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(GetWindow(), true);
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_A))
    {
        player_->MoveLeft();
        if (ball_->IsStuck())
        {
            ball_->SetPosition(player_->GetPosition() - glm::vec3(-player_->GetSize().x / 2 + 7, 14, 0));
        }
    }
    if (glfwGetKey(GetWindow(), GLFW_KEY_D))
    {
        player_->MoveRight(GetWidth());
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

    if (!ball_->IsStuck())
    {
        ball_->Move(GetDeltaTime(), GetWidth());
    }
    ball_->Draw();
    game_level_->Draw();
    player_->Draw();

    glfwSwapBuffers(GetWindow());
    glfwPollEvents();
}

void Game::Collision()
{
}

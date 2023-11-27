#ifndef SRC_GAME_H_
#define SRC_GAME_H_
#include "../external/frostEngine/src/game/igame.h"
#include "../external/frostEngine/src/engine/resource_manager.h"

void WindowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

class Game : public IGame
{
public:
    Game() : IGame() {}
    ~Game() {}
    void Initialization() override
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

        glfwSetFramebufferSizeCallback(GetWindow(), WindowSizeCallback);
    };
    void ProcessInpud() override
    {
        if (glfwGetKey(GetWindow(), GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(GetWindow(), true);
        }
    };
    void Update(float delta_time) override{};
    void Render() override
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
        auto gm = ResourceManager::GetGameModel("block");
        gm->SetPosition(glm::vec3(0.f, 0, 0));
        gm->SetSize(glm::vec3(200.f, 100.f, 0));
        gm->SetColor(glm::vec3(0.3f, 0.5f, 0.7f));
        gm->Draw();
        gm->SetPosition(glm::vec3(200.f, 0, 0));
        gm->SetColor(glm::vec3(0.5f, 0.0f, 0.1f));
        gm->Draw();
        gm->SetPosition(glm::vec3(400.f, 0, 0));
        gm->SetColor(glm::vec3(0.1f, 0.7f, 0.1f));
        gm->Draw();
        gm->SetPosition(glm::vec3(600.f, 0, 0));
        gm->SetColor(glm::vec3(0.5f, 0.7f, 0.2f));
        gm->Draw();
        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    };
};

#endif // SRC_GAME_H_

#include <iostream>
#include "game/igame.h"
#include "engine/resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

float lastX = 400;
float lastY = 300;
bool first_mouse = true;
void WindowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (first_mouse)
    {
        lastX = xpos;
        lastY = ypos;
        first_mouse = false;
    }
    float x_offset = xpos - lastX;
    float y_offset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    ResourceManager::GetCamera("camera")->ProcessMouseMovement(x_offset, y_offset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double y_offset)
{
    ResourceManager::GetCamera("camera")->ProcessMouseScroll(static_cast<float>(y_offset));
}
class Game : public IGame
{
public:
    Game() : IGame() {}
    ~Game() {}
    void Initialization()
    {
        ResourceManager::LoadGameModelData("cube", ResourceManager::GetExecutablePath() + "model");
        VertexBufferLayout vlo;
        BufferLayout bl{3, GL_FLOAT, GL_FALSE};
        vlo.AddBufferLayout(bl);
        ResourceManager::LoadVertexBuffer("cube", "cube");
        ResourceManager::LoadVertexArray("cube", "cube", vlo);
        ResourceManager::LoadShader("cube", ResourceManager::GetExecutablePath() + "vertex.glsl", ResourceManager::GetExecutablePath() + "fragment.glsl");
        ResourceManager::LoadGameModel("cube", "cube", "cube", "cube", glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 0, glm::vec3(0.3f, 0.5f, 0.7f), "modelMatrix", "color");
        ResourceManager::LoadCamera("camera", Camera(glm::vec3(0.0, 0.f, 3.f)));

        glfwSetFramebufferSizeCallback(GetWindow(), WindowSizeCallback);
        glfwSetInputMode(GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(GetWindow(), mouse_callback);
        glfwSetScrollCallback(GetWindow(), scroll_callback);
    };
    void ProcessInpud()
    {
        if (glfwGetKey(GetWindow(), GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(GetWindow(), true);
        }
        if (glfwGetKey(GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            ResourceManager::GetCamera("camera")->ProcessKeyBoard(CameraMovement::FORWARD, GetDeltaTime());
        }
        if (glfwGetKey(GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            ResourceManager::GetCamera("camera")->ProcessKeyBoard(CameraMovement::BACKWARD, GetDeltaTime());
        }
        if (glfwGetKey(GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            ResourceManager::GetCamera("camera")->ProcessKeyBoard(CameraMovement::LEFT, GetDeltaTime());
        }
        if (glfwGetKey(GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            ResourceManager::GetCamera("camera")->ProcessKeyBoard(CameraMovement::RIGHT, GetDeltaTime());
        }
    };
    void Update(float delta_time){};
    void Render()
    {
        float curent_frame = glfwGetTime();
        SetDeltaTime(curent_frame - GetLastFrame());
        SetLastFrame(curent_frame);
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(ResourceManager::GetCamera("camera")->GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
        auto view = ResourceManager::GetCamera("camera")->GetViewMatrix();
        auto shader = ResourceManager::GetShader("cube");
        shader->Use();
        shader->SetUniform("projection", projection);
        shader->SetUniform("view", view);
        auto gm = ResourceManager::GetGameModel("cube");
        gm->SetSize(glm::vec3(0.3f, 0.3f, 0.3f));
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {

                    gm->SetColor(glm::vec3(0.3f * i + 0.1f, 0.4f * j + 0.2f, 0.2f * k + 0.3f));
                    gm->SetPosition(glm::vec3(0.31f * i, 0.31f * j, 0.31f * k));
                    gm->Draw();
                }
            }
        }
    };
};
int main(int argc, char **argv)
{
    ResourceManager::SetExecutablePath(argv[0]);
    Game g;
    g.Initialization();
    while (!glfwWindowShouldClose(g.GetWindow()))
    {
        glClearColor(0, 0, 0, 1.f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        g.ProcessInpud();
        g.Render();
        glfwSwapBuffers(g.GetWindow());
        glfwPollEvents();
    }
    return 0;
}
#ifndef SRC_ENGINE_CAMERA_H_
#define SRC_ENGINE_CAMERA_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float kYaw = -90.0f;
const float kPitch = 0.0f;
const float kMovementSpeed = 2.5f;
const float kMouseSensivity = 0.33f;
const float kZoom = 45.0f;
const glm::vec3 kPosition = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 kWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 kFront = glm::vec3(0.0f, 0.0f, -1.0f);

class Camera
{
public:
    Camera(glm::vec3 position = kPosition, glm::vec3 world_up = kWorldUp, float yaw = kYaw, float pitch = kPitch);
    Camera(float pos_x, float pos_y, float pos_z, float world_up_x, float world_up_y, float world_up_z, float yaw, float pitch);
    glm::mat4 GetViewMatrix();
    void ProcessKeyBoard(CameraMovement direction, float delta_time);
    void ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float y_offset);
    const float GetZoom() const;
    const glm::vec3 GetPosition() const;

private:
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 world_up_;

    float yaw_;
    float pitch_;
    float movement_speed_;
    float mouse_sensivity_;
    float zoom_;

    void UpdateCameraVectors();
};

#endif // SRC_ENGINE_CAMERA_H_

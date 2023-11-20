#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 world_up, float yaw, float pitch)
    : position_(position), world_up_(world_up), yaw_(yaw), pitch_(pitch_), movement_speed_(kMovementSpeed), mouse_sensivity_(kMouseSensivity), zoom_(kZoom), front_(kFront)
{
    UpdateCameraVectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float world_up_x, float world_up_y, float world_up_z, float yaw, float pitch) : movement_speed_(kMovementSpeed), mouse_sensivity_(kMouseSensivity), zoom_(kZoom), front_(kFront)
{
    position_ = glm::vec3(pos_x, pos_y, pos_z);
    world_up_ = glm::vec3(world_up_x, world_up_y, world_up_z);
    yaw_ = yaw;
    pitch_ = pitch;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::ProcessKeyBoard(CameraMovement direction, float delta_time)
{
    float velocity = movement_speed_ * delta_time;
    switch (direction)
    {
    case CameraMovement::FORWARD:
        position_ += front_ * velocity;
        break;
    case CameraMovement::BACKWARD:
        position_ -= front_ * velocity;
        break;
    case CameraMovement::LEFT:
        position_ -= right_ * velocity;
        break;
    case CameraMovement::RIGHT:
        position_ += right_ * velocity;
    default:
        break;
    }
}

void Camera::ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch)
{
    x_offset *= mouse_sensivity_;
    y_offset *= mouse_sensivity_;

    yaw_ += x_offset;
    pitch_ += y_offset;
    if (constrainPitch)
    {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float y_offset)
{
    zoom_ -= static_cast<float>(y_offset);
    if (zoom_ < 1.0f)
        zoom_ = 1.0f;
    if (zoom_ > 45.0f)
        zoom_ = 45.0f;
}

const float Camera::GetZoom() const
{
    return zoom_;
}

const glm::vec3 Camera::GetPosition() const
{
    return position_;
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
}

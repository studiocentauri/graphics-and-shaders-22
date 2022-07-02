#include "rendering/Camera.h"

Camera::Camera(glm::vec3 position_, glm::vec3 worldUp_, float yaw_, float pitch_)
{
    position = position_;
    worldUp = worldUp_;
    yaw = yaw_;
    pitch = pitch_;
    lookAt = glm::vec3(0.0f, 0.0f, -1.0f);
    movementSpeed = CAM_SPEED;
    mouseSensitivity = CAM_SENSITIVITY;
    fieldOfView = CAM_FOV;

    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + lookAt, up);
}

void Camera::process_keyboard(CAMERA_MOVEMENT direction, float deltaTime)
{
    glm::vec3 displacement(0.0f);

    switch (direction)
    {
    case CAM_FORWARD:
        displacement += lookAt * movementSpeed * deltaTime;
        break;
    case CAM_BACKWARD:
        displacement -= lookAt * movementSpeed * deltaTime;
        break;
    case CAM_RIGHT:
        displacement += right * movementSpeed * deltaTime;
        break;
    case CAM_LEFT:
        displacement -= right * movementSpeed * deltaTime;
        break;
    case CAM_UP:
        displacement += up * movementSpeed * deltaTime;
        break;
    case CAM_DOWN:
        displacement -= up * movementSpeed * deltaTime;
        break;
    default:
        break;
    }

#if FPS_CAM
    displacement.y = 0.0f;
#endif

    position += displacement;
}

void Camera::process_mouse(float xoffset, float yoffset, float deltaTime, GLboolean constraintPitch)
{
    xoffset *= mouseSensitivity * deltaTime * 60.0f;
    yaw += xoffset;

    yoffset *= mouseSensitivity * deltaTime * 60.0f;
    pitch -= yoffset;
    if (constraintPitch)
    {
        pitch = glm::clamp(pitch, -CAMERA_MAX_PITCH, CAMERA_MAX_PITCH);
    }

    update_camera_vectors();
}

void Camera::process_scroll(float yoffset)
{
    fieldOfView -= yoffset;
    fieldOfView = glm::clamp(fieldOfView, MIN_FOV, MAX_FOV);
}

void Camera::update_camera_vectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    lookAt = glm::normalize(front);
    right = glm::normalize(glm::cross(lookAt, worldUp));
    up = glm::normalize(glm::cross(right, lookAt));
}

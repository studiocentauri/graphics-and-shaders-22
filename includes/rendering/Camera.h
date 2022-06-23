#ifndef CAMERA_H
#define CAMERA_H

#include "thirdparty/glad/glad.h"
#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"
#include "Config.h"

enum CAMERA_MOVEMENT
{
    CAM_FORWARD,
    CAM_BACKWARD,
    CAM_LEFT,
    CAM_RIGHT,
    CAM_UP,
    CAM_DOWN,
};

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 worldUp;
    glm::vec3 right, up;
    float yaw, pitch;
    float movementSpeed;
    float mouseSensitivity;
    float fieldOfView;

    Camera(glm::vec3 position_ = glm::vec3(0.0f), glm::vec3 worldUp_ = WORLD_UP, float yaw_ = YAW, float pitch_ = PITCH);

    glm::mat4 get_view_matrix();
    void process_keyboard(CAMERA_MOVEMENT direction, float deltaTime);
    void process_mouse(float xoffset, float yoffset, float deltaTime, GLboolean constraintPitch = true);
    void process_scroll(float yoffset);

private:
    void update_camera_vectors();
};

#endif
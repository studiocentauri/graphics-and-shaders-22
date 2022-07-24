#ifndef CAMERA_H
#define CAMERA_H

// Third-party Headers
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Custom Headers
#include "Config.h"

// Directions for Camera Movement
enum CAMERA_MOVEMENT
{
    CAM_FORWARD,
    CAM_BACKWARD,
    CAM_LEFT,
    CAM_RIGHT,
    CAM_UP,
    CAM_DOWN,
};

// Camera class for Renderer
class Camera
{
public:
    glm::vec3 position;     // Camera position
    glm::vec3 lookAt;       // Look At vector for Camera / Local front vector for camera
    glm::vec3 worldUp;      // Vector for the World's up direction
    glm::vec3 right;        // Local right vector for camera
    glm::vec3 up;           // Local up vector for camera
    float yaw;              // Angle with Y axis
    float pitch;            // Angle with X axis
    float movementSpeed;    // Move speed for camera
    float mouseSensitivity; // Rotate speed for camera
    float fieldOfView;      // FOV or Zoom for camera

    // Camera Constructor
    Camera(glm::vec3 position_ = CAMERA_ORIGIN, glm::vec3 worldUp_ = WORLD_UP, float yaw_ = YAW, float pitch_ = PITCH);
    // Returns the camera's view matrix
    glm::mat4 get_view_matrix();
    // Processes movement for the camera
    void process_keyboard(CAMERA_MOVEMENT direction, float deltaTime);
    // Processes rotation for the camera
    void process_mouse(float xoffset, float yoffset, float deltaTime, GLboolean constraintPitch = true);
    // Processes zoom for the camera
    void process_scroll(float yoffset);

private:
    // Updates the local basis vectors for the camera
    void update_camera_vectors();
};

#endif // !CAMERA_H

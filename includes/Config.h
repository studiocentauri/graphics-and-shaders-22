#ifndef CONFIG_H
#define CONFIG_H

// Renderer Settings
#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6
#define OPENGL_PROFILE_USED GLFW_OPENGL_CORE_PROFILE
#define LOADED_SHADERS_COUNT 3
#define LOADED_TEXTURES_COUNT 10
#define ENABLE_BLINN_PHONG 1
#define ENABLE_GAMMA_CORRECTION 1

// Window Settings
#define WINDOW_NAME "Graphics And Shaders"
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 800
#define ENABLE_FULLSCREEN 0
#define ENABLE_FIXED_ASPECT_RATIO 1
#define ASPECT_RATIO_X 16
#define ASPECT_RATIO_Y 10
#define ENABLE_WINDOW_BOUNDS 1
#define WINDOW_SIZE_LIMITS glm::vec4(80.0f, 50.0f, 1600.0f, 1000.0f)

// Vector Settings
#define WORLD_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define WORLD_RIGHT glm::vec3(1.0f, 0.0f, 0.0f)
#define WORLD_FORWARD glm::vec3(0.0f, 0.0f, 1.0f)
#define WORLD_ORIGIN glm::vec3(0.0f)

// Color Settings

#define COLOR_BLACK glm::vec3(0.0f, 0.0f, 0.0f)
#define COLOR_GRAY glm::vec3(0.1f, 0.1f, 0.1f)
#define COLOR_RED glm::vec3(1.0f, 0.1f, 0.1f)
#define COLOR_GREEN glm::vec3(0.1f, 1.0f, 0.1f)
#define COLOR_BLUE glm::vec3(0.1f, 0.1f, 1.0f)
#define COLOR_YELLOW glm::vec3(1.0f, 1.0f, 0.1f)
#define COLOR_WHITE glm::vec3(1.0f, 1.0f, 1.0f)
#define COLOR_PURPLE glm::vec3(1.0f, 0.1f, 1.0f)
#define DEFAULT_BACKGROUND_COLOR COLOR_BLACK
#define DEFAULT_SCENE_COLOR COLOR_GRAY
#define DEFAULT_SHADER_COLOR COLOR_PURPLE
#define DEFAULT_LIGHT_COLOR COLOR_WHITE

// Camera Settings
#define CAMERA_ORIGIN glm::vec3(0.0f, 0.0f, 4.0f)
#define YAW -90.0f
#define PITCH 0.0f
#define CAMERA_MAX_PITCH 89.0f
#define CAM_SPEED 8.0f
#define CAM_SENSITIVITY 0.1f
#define CAM_FOV 45.0f
#define MAX_FOV 90.0f
#define MIN_FOV 1.0f
#define FPS_CAM 0
#define CAMERA_FAR_PLANE 100.0f
#define CAMERA_NEAR_PLANE 0.01f

#endif // !CONFIG_H

#ifndef CONFIG_H
#define CONFIG_H

#define WINDOW_NAME "Graphics And Shaders"
#define OPENGL_MAJOR_VERSION 3
#define OPENGL_MINOR_VERSION 3
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 800
#define ENABLE_FULLSCREEN 0
#define ENABLE_FIXED_ASPECT_RATIO 1
#define ASPECT_RATIO_X 16
#define ASPECT_RATIO_Y 10

#define YAW -90.0f
#define PITCH 0.0f
#define CAM_SPEED 8.0f
#define CAM_SENSITIVITY 0.1f
#define CAM_FOV 45.0f
#define MAX_FOV 90.0f
#define MIN_FOV 1.0f
#define WORLD_UP glm::vec3(0.0f, 1.0f, 0.0f)
#define FPS_CAM 0

#endif
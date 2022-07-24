#ifndef TRANSFORM_H
#define TRANSFORM_H

// Third party headers
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Transform Class for actors
class Transform
{
public:
    glm::vec3 position; // Actor Position
    glm::vec3 rotation; // Actor Rotation
    glm::vec3 scale;    // Actor Scale

    // Transform Constructor
    Transform(glm::vec3 position_ = glm::vec3(0.0f), glm::vec3 rotation_ = glm::vec3(0.0f), glm::vec3 scale_ = glm::vec3(1.0f));
    // Resets objects to origin
    void reset_transform();
    // Gets the Model matrix for transform
    glm::mat4 get_model_matrix();

private:
};

#endif // !TRANSFORM_H

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"
#include "thirdparty/glm/gtc/type_ptr.hpp"

class Transform
{
public:
    glm::vec3 position, rotation, scale;
    Transform(glm::vec3 position_ = glm::vec3(0.0f), glm::vec3 rotation_ = glm::vec3(0.0f), glm::vec3 scale_ = glm::vec3(1.0f));

    void reset_transform();
    glm::mat4 get_model_matrix();

private:
};

#endif
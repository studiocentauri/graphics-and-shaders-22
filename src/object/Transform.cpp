#include "object/Transform.h"

Transform::Transform(glm::vec3 position_, glm::vec3 rotation_, glm::vec3 scale_)
{
    position = position_;
    rotation = rotation_;
    scale = scale_;
}

void Transform::reset_transform()
{
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
}

glm::mat4 Transform::get_model_matrix()
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, scale);
    return model;
}

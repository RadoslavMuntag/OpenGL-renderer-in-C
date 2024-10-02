//
// Created by muntr on 28. 9. 2024.
//

#ifndef MYGLFWPROJECT_C_TRANSFORM_H
#define MYGLFWPROJECT_C_TRANSFORM_H

#include "../utils/utils.h"

typedef struct{
    vec3 position;
    vec3 eulers;
    vec3 scale;
}TransformComponent;

void transform_get_model_matrix(TransformComponent* transform, mat4 modelMatrix);
void transform_set_position(TransformComponent* transform, float x, float y, float z);
void transform_set_rotation(TransformComponent* transform, float pitch, float yaw, float roll);
void transform_set_scale(TransformComponent* transform, float sx, float sy, float sz);
void transform_get_position(TransformComponent* transform, vec3 v);
void init_transform(TransformComponent* transform);

#endif //MYGLFWPROJECT_C_TRANSFORM_H

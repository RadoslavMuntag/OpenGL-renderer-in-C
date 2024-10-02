//
// Created by muntr on 28. 9. 2024.
//

#include "c_transform.h"

void transform_get_model_matrix(TransformComponent* transform, mat4 modelMatrix) {
    // Create identity matrix
    glm_mat4_identity(modelMatrix);

    // Translation: Create a translation matrix from the position vector
    mat4 translationMatrix;
    glm_translate_make(translationMatrix, transform->position);

    // Rotation: Create a rotation matrix from Euler angles (assumed to be in degrees)
    mat4 rotationMatrix;
    glm_euler_xyz(transform->eulers, rotationMatrix);  // Assuming ZXY order for Euler angles

    // Scale: Create a scale matrix from the scale vector
    mat4 scaleMatrix;
    glm_scale_make(scaleMatrix, transform->scale);

    // Combine transformations: modelMatrix = translation * rotation * scale
    glm_mat4_mul(translationMatrix, rotationMatrix, modelMatrix);
    glm_mat4_mul(modelMatrix, scaleMatrix, modelMatrix);
}

void transform_set_position(TransformComponent* transform, float x, float y, float z) {
    glm_vec3_copy((vec3){x, y, z}, transform->position);
}

// Function to set rotation (Euler angles in degrees)
void transform_set_rotation(TransformComponent* transform, float pitch, float yaw, float roll) {
    glm_vec3_copy((vec3){pitch, yaw, roll}, transform->eulers);
}

// Function to set scale
void transform_set_scale(TransformComponent* transform, float sx, float sy, float sz) {
    glm_vec3_copy((vec3){sx, sy, sz}, transform->scale);
}

void transform_get_position(TransformComponent* transform, vec3 v){
    glm_vec3_copy(transform->position, v);
}

void init_transform(TransformComponent* transform){
    transform_set_position(transform, 0.0f, 0.0f, 0.0f);
    transform_set_rotation(transform, 0.0f, 0.0f, 0.0f);
    transform_set_scale(transform, 1.0f, 1.0f, 1.0f);
}

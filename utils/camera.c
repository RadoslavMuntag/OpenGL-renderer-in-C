//
// Created by muntr on 20. 9. 2024.
//

#include "camera.h"


void print_mat4(mat4 matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void cam_resize(struct Camera *self, int width, int height){
    self->width = width;
    self->height = height;
    float ratio = (float)self->width / (float)self->height;
    glm_perspective(45.0f * (3.1415926f / 180.0f), (float)self->width / (float)self->height, 0.1f, 100.0f, self->projection);
    /*float left = -3.0f * ratio, right = 3.0f * ratio;
    float bottom = -3.0f, top = 3.0f;
    float near = 0.1f, far = 100.0f;
    glm_ortho(left, right, bottom, top, near, far, self->projection);*/
    print_mat4(self->projection);
}

void handle_rotation(struct Camera *self){
    vec3 temp;

    glm_vec3_cross(self->up, self->direction, temp);
    glm_normalize(temp);


    glm_vec3_rotate(self->direction, self->eulers[0], temp);
    glm_vec3_rotate(self->direction, self->eulers[1], self->up);
    glm_vec3_rotate(self->up, self->eulers[2], self->direction);

}

void camera_create(struct Camera *self, int width, int height){
    self->speed = 5.0f;
    self->sensitivity = 1.0f;

    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, self->eulers);

    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glm_vec3_copy((vec3){0.0f, 0.0f, -3.0f}, self->cameraPos);
    glm_vec3_copy((vec3){0.0f, 0.0f, 1.0f}, self->direction);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, self->up);


    glm_mat4_identity(self->view);
    glm_mat4_identity(self->projection);

    vec3 temp;
    glm_vec3_add(self->cameraPos, self->direction, temp);


    glm_lookat(self->cameraPos, temp, self->up, self->view);
    cam_resize(self, width, height);

}

void update_camera(struct Camera *self){
//    glDepthFunc(GL_LESS);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);

    /*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);          // Enable face culling
    glCullFace(GL_BACK);             // Cull back faces*/


    vec3 temp;

    handle_rotation(self);

    glm_vec3_add(self->cameraPos, self->direction, temp);

    glm_lookat(self->cameraPos, temp, self->up, self->view);

    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, self->eulers);

}





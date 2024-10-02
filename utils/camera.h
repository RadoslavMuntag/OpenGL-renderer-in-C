//
// Created by muntr on 20. 9. 2024.
//

#ifndef MYGLFWPROJECT_CAMERA_H
#define MYGLFWPROJECT_CAMERA_H

#include "../rendering/gfx_h.h"
#include "utils.h"

#define Z_DOWN ((vec3){0.0f, 0.0f, -1.0f})

struct Camera{
    vec3 cameraPos;
    vec3 up;

    vec3 direction;

    int width;
    int height;

    float speed;
    float sensitivity;
    vec3 eulers;

    mat4 view;
    mat4 projection;
};

void cam_resize(struct Camera *self, int width, int height);
void camera_create(struct Camera *self, int width, int height);
void update_camera(struct Camera *self);


#endif //MYGLFWPROJECT_CAMERA_H

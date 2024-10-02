//
// Created by muntr on 20. 9. 2024.
//

#ifndef MYGLFWPROJECT_WINDOW_H
#define MYGLFWPROJECT_WINDOW_H
# define M_PI 3.14159265358979323846

#include "gfx_h.h"
#include "../utils/utils.h"
#include "renderer.h"
#include "../utils/camera.h"
#include "../entity/control.h"

struct Window {
    GLFWwindow *handle;
    struct Renderer renderer;
    struct Camera camera;
    int width;
    int height;
    struct Keyboard keyboard;
    const GLFWvidmode* videoMode;

    uint64_t ticks,tps, tick_remainder, last_second;
    uint64_t frames, fps, frame_delta, last_frame;
    double time_from_start;
};

void window_create();
void window_loop();

#endif //MYGLFWPROJECT_WINDOW_H

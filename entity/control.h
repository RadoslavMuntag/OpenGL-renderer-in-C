//
// Created by muntr on 21. 9. 2024.
//

#ifndef MYGLFWPROJECT_CONTROL_H
#define MYGLFWPROJECT_CONTROL_H

#include "../utils/utils.h"
#include "../rendering/gfx_h.h"
#include "../rendering/renderer.h"
#include "../utils/camera.h"
#include "../utils/time.h"

struct Button{
    bool down, last, last_tick, pressed, pressed_tick;
};

struct Keyboard{
    struct Button keys[GLFW_KEY_LAST];
};

void tick(struct Keyboard *keyboard, struct Camera *camera, EntityList *entity_list, int refreshRate, double time);

#endif //MYGLFWPROJECT_CONTROL_H

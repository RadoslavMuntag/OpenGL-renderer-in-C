//
// Created by muntr on 21. 9. 2024.
//

#include "control.h"

float normalize_angle(float angle) {
    float two_pi = 2.0f * GLM_PIf;
    return fmodf(fmodf(angle, two_pi) + two_pi, two_pi);
}

void normalize_euler_angles(vec3 eulers) {
    eulers[0] = normalize_angle(eulers[0]); // Pitch (rotation around X-axis)
    eulers[1] = normalize_angle(eulers[1]); // Yaw (rotation around Y-axis)
    eulers[2] = normalize_angle(eulers[2]); // Roll (rotation around Z-axis)
}

void _update_camera(struct Keyboard *keyboard, struct Camera *self, float secPerTick){

    vec3 temp;
    float trueSpeed = self->speed * secPerTick;

    if((keyboard->keys[GLFW_KEY_W].down) == GLFW_PRESS) {
        glm_vec3_scale(self->direction, trueSpeed, temp);
        glm_vec3_add(self->cameraPos,temp, self->cameraPos );
    }
    if((keyboard->keys[GLFW_KEY_A].down) == GLFW_PRESS) {
        glm_vec3_cross(self->direction, self->up, temp);
        glm_normalize(temp);
        glm_vec3_scale(temp, -trueSpeed, temp);
        glm_vec3_add(self->cameraPos,temp, self->cameraPos );
    }

    if((keyboard->keys[GLFW_KEY_S].down) == GLFW_PRESS) {
        glm_vec3_scale(self->direction, -trueSpeed, temp);
        glm_vec3_add(self->cameraPos,temp, self->cameraPos );
    }

    if((keyboard->keys[GLFW_KEY_D].down) == GLFW_PRESS) {
        glm_vec3_cross(self->direction, self->up, temp);
        glm_normalize(temp);
        glm_vec3_scale(temp, trueSpeed, temp);
        glm_vec3_add(self->cameraPos,temp, self->cameraPos );
    }

    if((keyboard->keys[GLFW_KEY_SPACE].down) == GLFW_PRESS) {
        glm_vec3_scale(self->up, trueSpeed, temp);
        glm_vec3_add(self->cameraPos,temp, self->cameraPos );
    }

    if((keyboard->keys[GLFW_KEY_LEFT_SHIFT].down) == GLFW_PRESS) {
        glm_vec3_scale(self->up, -trueSpeed, temp);
        glm_vec3_add(self->cameraPos,temp, self->cameraPos );
    }

    if((keyboard->keys[GLFW_KEY_Q].down) == GLFW_PRESS) {
        self->eulers[1] += self->sensitivity * secPerTick;
        normalize_euler_angles(self->eulers);
    }

    if((keyboard->keys[GLFW_KEY_E].down) == GLFW_PRESS) {
        self->eulers[1] -= self->sensitivity * secPerTick;
        normalize_euler_angles(self->eulers);
    }

    if((keyboard->keys[GLFW_KEY_O].down) == GLFW_PRESS) {
        self->eulers[0] += self->sensitivity * secPerTick;
        normalize_euler_angles(self->eulers);
    }

    if((keyboard->keys[GLFW_KEY_P].down) == GLFW_PRESS) {
        self->eulers[0] -= self->sensitivity * secPerTick;
        normalize_euler_angles(self->eulers);
    }

    if((keyboard->keys[GLFW_KEY_K].down) == GLFW_PRESS) {
        self->eulers[2] += self->sensitivity * secPerTick;
        normalize_euler_angles(self->eulers);
    }

    if((keyboard->keys[GLFW_KEY_L].down) == GLFW_PRESS) {
        self->eulers[2] -= self->sensitivity * secPerTick;
        normalize_euler_angles(self->eulers);
    }



}

void animate(float u, float v, double t, Entity* entity){
    //float temp_y = sinf( GLM_PIf * (u / 10.0f + v / 10.0f+ (float)t)) * 2.0f;
    float old_u = u;
    float old_v = v;

    u -= 50;
    v -= 50;
    u /= 10.0f;
    v /= 10.0f;

    float d = sqrtf(u * u + v * v);
    float temp_y = sinf(GLM_PIf * (4.0f * d - t)) * 10.0f;
    temp_y /= (1.0f + 10.0f * d);

    transform_set_position(entity->transform, old_u , temp_y, old_v);



}


void tick(struct Keyboard *keyboard, struct Camera *camera, EntityList *entity_list, int refreshRate, double time) {
    float secPerTick = 1.0f/ (float) refreshRate;
    _update_camera(keyboard, camera, secPerTick);
    Entity* sky_entity = get_entity(entity_list, 0);
    transform_set_position(sky_entity->transform, camera->cameraPos[0], camera->cameraPos[1], camera->cameraPos[2]);
    //int row_size = (int)sqrt((double)entity_list->size);
    /*for (int i = 0; i < entity_list->size; ++i) {
        Entity* entity = get_entity(entity_list,i);
        vec3 pos;
        transform_get_position(entity->transform, pos);

        animate(pos[0], pos[2], time, entity);
    }*/

    /*float offset = 100.0f/2.0f;


    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            Entity* entity = get_entity(entity_list,i*100 + j);
            //vec3 pos;
            //transform_get_position(entity->transform, pos);
            animate(camera->cameraPos[0] - offset + (float) i, camera->cameraPos[2] - offset + (float) j, time, entity);
        }
    }*/


}


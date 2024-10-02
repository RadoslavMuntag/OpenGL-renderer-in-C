//
// Created by muntr on 20. 9. 2024.
//

#ifndef MYGLFWPROJECT_RENDERER_H
#define MYGLFWPROJECT_RENDERER_H


#include "gfx_h.h"
#include "../shaders/shader.h"
#include "VAO.h"
#include "Mesh.h"
#include "../entity/entity.h"
#include "../utils/utils.h"
#include "../utils/rand_obj_data.h"
#include "../utils/camera.h"



struct Renderer{
    struct Shader default_shader;
    struct Shader sky_shader;
    Entity* sky_entity;

    vec3 sun_pos;

    vec3 sky_color;

    EntityList entityList;
    MeshList meshList;
};

void renderer_create(struct Renderer *self);
void renderer_update(struct Renderer *self, struct Camera* camera);

void renderer_destroy(struct Renderer *self);

#endif //MYGLFWPROJECT_RENDERER_H

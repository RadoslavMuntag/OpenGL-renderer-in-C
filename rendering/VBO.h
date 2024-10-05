//
// Created by muntr on 18. 9. 2024.
//

#ifndef MYGLFWPROJECT_VBO_H
#define MYGLFWPROJECT_VBO_H

#include "../utils/utils.h"
#include "gfx_h.h"

typedef struct VBO {
    GLuint handle;
    GLint type;
    bool dynamic;
}VBO;

struct VBO vbo_create(GLint type, bool dynamic);

void vbo_destroy(struct VBO self);

void vbo_bind(struct VBO self);

void vbo_buffer(struct VBO self, void *data, size_t offset, size_t count);

#endif
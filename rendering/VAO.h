//
// Created by muntr on 18. 9. 2024.
//

#ifndef MYGLFWPROJECT_VAO_H
#define MYGLFWPROJECT_VAO_H

#include "../utils/utils.h"
#include "gfx_h.h"
#include "VBO.h"

typedef struct VAO {
    GLuint handle;
}VAO;

struct VAO vao_create();
void vao_destroy(struct VAO self);
void vao_bind(struct VAO self);
void vao_attr(
        struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type,
        GLsizei stride, size_t offset);


#endif //MYGLFWPROJECT_VAO_H

//
// Created by muntr on 20. 9. 2024.
//

#ifndef MYGLFWPROJECT_RAND_OBJ_DATA_H
#define MYGLFWPROJECT_RAND_OBJ_DATA_H

#include "../rendering/gfx_h.h"
#include "utils.h"
void get_simple_triangle(GLfloat* triangle);

void get_cube(GLfloat* cube, int array_size);
void get_cube_improved(GLfloat* cube_vertices, GLuint* cube_indices, int vertices_size, int indices_size);

#endif //MYGLFWPROJECT_RAND_OBJ_DATA_H

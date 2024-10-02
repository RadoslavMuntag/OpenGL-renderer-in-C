//
// Created by muntr on 20. 9. 2024.
//

#include "rand_obj_data.h"

void get_simple_triangle(GLfloat* triangle){
   GLfloat data[] = {
            // Positions        // Colors
            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Vertex 1: Red
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Vertex 2: Green
            0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Vertex 3: Blue
    };

    for (int i = 0; i < 18; ++i) {
        triangle[i] = data[i];
    }
}

void get_cube(GLfloat* cube, int array_size){
    assert(array_size >= 216*sizeof(float));
    GLfloat vertices[] = {
            // Positions          // Colors
            // Front face
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left (Red)
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-right (Red)
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Top-right (Red)
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Top-right (Red)
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Top-left (Red)
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Bottom-left (Red)

            // Back face
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-left (Green)
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-right (Green)
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Top-right (Green)
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Top-right (Green)
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Top-left (Green)
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // Bottom-left (Green)

            // Left face
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  // Top-right (Blue)
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Top-left (Blue)
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Bottom-left (Blue)
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // Bottom-left (Blue)
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  // Bottom-right (Blue)
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  // Top-right (Blue)

            // Right face
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Top-left (Yellow)
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Top-right (Yellow)
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Bottom-right (Yellow)
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // Bottom-right (Yellow)
            0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Bottom-left (Yellow)
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Top-left (Yellow)

            // Top face
            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  // Top-left (Purple)
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  // Top-right (Purple)
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-right (Purple)
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-right (Purple)
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Bottom-left (Purple)
            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  // Top-left (Purple)

            // Bottom face
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-left (Cyan)
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-right (Cyan)
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Top-right (Cyan)
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Top-right (Cyan)
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Top-left (Cyan)
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f   // Bottom-left (Cyan)
    };

    for (int i = 0; i < 216; ++i) {
        cube[i] = vertices[i];
    }
}

void get_cube_improved(GLfloat* cube_vertices, GLuint* cube_indices, int vertices_size, int indices_size){
    assert(vertices_size >= 48*sizeof(float));
    assert(indices_size >= 36*sizeof(float));

    GLfloat vertices[] = {
            // Positions          // Colors
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 0: Front Bottom Left (Red)
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // 1: Front Bottom Right (Red)
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // 2: Front Top Right (Red)
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // 3: Front Top Left (Red)

            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // 4: Back Bottom Left (Green)
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // 5: Back Bottom Right (Green)
            0.5f,  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  // 6: Back Top Right (Green)
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f   // 7: Back Top Left (Green)
    };

    GLuint indices[] = {
            // Front face
            0, 1, 2,
            0, 2, 3,

            // Top face
            3, 2, 6,
            3, 6, 7,

            // Left face
            7, 3, 0,
            7,0, 4,

            // Back face
            4,7, 6,
            4, 6, 5,

            // Bottom face
            5, 4, 0,
            5,0, 1,

            // Right face
            1, 5, 6,
            1,6, 2,

    };


    for (int i = 0; i < 48; ++i) {
        cube_vertices[i] = vertices[i];
    }

    for (int i = 0; i < 36; ++i) {
        cube_indices[i] = indices[i];
    }
}
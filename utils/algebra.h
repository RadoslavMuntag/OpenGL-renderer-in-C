//
// Created by muntr on 20. 9. 2024.
//

#ifndef MYGLFWPROJECT_ALGEBRA_H
#define MYGLFWPROJECT_ALGEBRA_H

typedef struct {
    float m[4][4];
} Mat4;

typedef struct {
    float x, y, z;
} Vec3;

void mat4_multiply(Mat4 *result, const Mat4 *a, const Mat4 *b);

#endif //MYGLFWPROJECT_ALGEBRA_H

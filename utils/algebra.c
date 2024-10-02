//
// Created by muntr on 20. 9. 2024.
//

#include "algebra.h"

void mat4_multiply(Mat4 *result, const Mat4 *a, const Mat4 *b) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result->m[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result->m[i][j] += a->m[i][k] * b->m[k][j];
            }
        }
    }
}

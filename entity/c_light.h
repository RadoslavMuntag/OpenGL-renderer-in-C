//
// Created by muntr on 9. 10. 2024.
//

#ifndef MYGLFWPROJECT_C_LIGHT_H
#define MYGLFWPROJECT_C_LIGHT_H
#include "../utils/utils.h"

typedef struct LightComponent{
    vec3 light_intensity;

    vec3 linear_attenuation;
    vec3 quadratic_attenuation;
}LightComponent;

#endif //MYGLFWPROJECT_C_LIGHT_H

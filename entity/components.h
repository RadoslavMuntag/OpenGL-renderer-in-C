//
// Created by muntr on 28. 9. 2024.
//

#ifndef MYGLFWPROJECT_COMPONENTS_H
#define MYGLFWPROJECT_COMPONENTS_H
#include "c_mesh.h"
#include "c_physics.h"
#include "c_transform.h"

#define COMPONENT_LAST C_LIGHT
enum EComponent {
    C_MESH = 0,
    C_TRANSFORM,
    C_CAMERA,
    C_PHYSICS,
    C_LIGHT
};

#endif //MYGLFWPROJECT_COMPONENTS_H

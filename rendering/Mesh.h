//
// Created by muntr on 23. 9. 2024.
//

#ifndef MYGLFWPROJECT_MESH_H
#define MYGLFWPROJECT_MESH_H
#define _CRT_SECURE_NO_WARNINGS

#include "../utils/utils.h"
#include "VAO.h"

#define MAX_DATA 3000
#define MAX_VERTICES 4000000
#define MAX_INDICES 1000000

typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    Vertex *data;
    int size;
} VertexArr;

typedef struct {
    float u, v;
} TexCoord;

typedef struct {
    TexCoord *data;
    int size;
} TexCoordArr;

typedef struct{
    Vertex v[1024];
    TexCoord vt[1024];
    Vertex vn[1024];
    int count;
}Face;

typedef struct {
    GLfloat* data;
    int size;
} Vertices;

typedef struct {
    GLuint* data;
    int size;
} Indices;

typedef struct{
    char name[128];
    int mtlID;
    float Ns; // specular exponent
    vec3 Ka; // ambient lighting
    vec3 Kd; // diffuse lighting
    vec3 Ks; // specular highlights color and intensity
}Material;

typedef struct{
    Material *data;
    int size;
}MtlArr;


void parse_obj_file(const char *filename, Vertices *vertices, Indices *indices, MtlArr *mtl_arr);

#endif //MYGLFWPROJECT_MESH_H

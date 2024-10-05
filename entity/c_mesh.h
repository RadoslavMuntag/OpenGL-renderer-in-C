//
// Created by muntr on 28. 9. 2024.
//


#ifndef MYGLFWPROJECT_C_MESH_H
#define MYGLFWPROJECT_C_MESH_H

#include "../rendering/VAO.h"
#include "../rendering/Mesh.h"


typedef struct MeshComponent{
    uint32_t meshID;
    int model_size;
    VBO vbo;
    VAO vao;
    VBO ebo;
    MtlArr materials;

}MeshComponent;

typedef struct MeshList{
    MeshComponent** data;
    uint32_t size;
}MeshList;

void create_mesh_component(MeshList* mesh_list, const char *filename);
MeshComponent* get_mesh_by_id(MeshList* mesh_list, uint32_t meshID);
void destroy_mesh_list(MeshList* list);

#endif //MYGLFWPROJECT_C_MESH_H

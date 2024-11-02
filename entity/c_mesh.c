//
// Created by muntr on 28. 9. 2024.
//
#include "c_mesh.h"
void init_mesh_list(MeshList* list){
    list->data = NULL;
    list->size = 0;
}

MeshComponent* get_mesh_by_id(MeshList* mesh_list, uint32_t meshID){
    if (meshID >= mesh_list->size){
        printf("Invalid mesh ID");
        exit(-1);
    }

    return mesh_list->data[meshID];
}

void alloc_mesh(MeshList* mesh_list){
    mesh_list->size++;

    if (mesh_list->data == NULL){
        mesh_list->data = (MeshComponent**)calloc(mesh_list->size, sizeof(MeshComponent*));
    }
    else{
        mesh_list->data = (MeshComponent**)realloc(mesh_list->data,mesh_list->size * sizeof(MeshComponent*));
    }

    mesh_list->data[mesh_list->size - 1] = (MeshComponent*)calloc(1, sizeof(MeshComponent));
    mesh_list->data[mesh_list->size - 1]->meshID = mesh_list->size -1;
}

void create_mesh_bufferss(MeshComponent* self, Vertices* vertices, Indices* indices){
    self->vao = vao_create();
    self->vbo = vbo_create(GL_ARRAY_BUFFER, false);
    self->ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    vbo_buffer(self->vbo, vertices->data, 0, vertices->size*sizeof(float));
    vbo_buffer(self->ebo, indices->data, 0, indices->size*sizeof(unsigned int));

    free(vertices->data);
    free(indices->data);

    vao_attr(self->vao, self->vbo, 0, 3, GL_FLOAT, 9 * sizeof(float), 0);
    vao_attr(self->vao, self->vbo, 1, 2, GL_FLOAT, 9 * sizeof(float), 3 * sizeof(float));
    vao_attr(self->vao, self->vbo, 2, 3, GL_FLOAT, 9 * sizeof(float), 5 * sizeof(float));
    vao_attr(self->vao, self->vbo, 3, 1, GL_FLOAT, 9 * sizeof(float), 8 * sizeof(float));

    self->model_size = indices->size;

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void create_mesh_component(MeshList* mesh_list, const char *filename){
    if (mesh_list == NULL){
        init_mesh_list(mesh_list);
    }

    alloc_mesh(mesh_list);
    MeshComponent* current = get_mesh_by_id(mesh_list, mesh_list->size - 1);

    Vertices vertices;
    vertices.data = (GLfloat *)malloc(MAX_VERTICES * sizeof(GLfloat));

    Indices indices;
    indices.data = (GLuint *)malloc(MAX_INDICES * sizeof(GLuint));
    current->materials.data = NULL;

    parse_obj_file(filename, &vertices, &indices, &current->materials);

    create_mesh_bufferss(current, &vertices, &indices);

}

void destroy_materials(MtlArr* mtl_arr){
    if(mtl_arr->data == NULL){
        return;
    }
    for (int i = 0; i < mtl_arr->size; ++i) {
        Material *current = &mtl_arr->data[i];
        if(current->map_Kd != NULL){
            glDeleteTextures(1, &current->map_Kd->ref);
            free(current->map_Kd);
            current->map_Kd = NULL;
        }
    }
    free(mtl_arr->data);
    mtl_arr->data = NULL;
}

void destroy_mesh_list(MeshList* list){
    for (int i = 0; i < list->size; ++i) {
        MeshComponent* current = list->data[i];
        vao_destroy(current->vao);
        vbo_destroy(current->vbo);
        vbo_destroy(current->ebo);
        destroy_materials(&current->materials);

        free(current);
        current = NULL;
    }
    free(list->data);
    list->data = NULL;
};

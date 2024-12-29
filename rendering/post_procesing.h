//
// Created by muntr on 3. 11. 2024.
//

#ifndef MYGLFWPROJECT_POST_PROCESING_H
#define MYGLFWPROJECT_POST_PROCESING_H
#include "../entity/c_texture.h"
#include "../entity/c_mesh.h"
#include "../shaders/shader.h"

typedef struct{
    GLuint handle;
    GLuint rbo;
    MeshComponent frame_mesh;
    TexComponent *framebufferTex;

    struct Shader frame_shader;
}FBO;

FBO *create_fbo(MeshList* mesh_list, int width, int height);
void resize_fbo(FBO *fbo, int width, int height);
void fbo_destroy(FBO *fbo);

#endif //MYGLFWPROJECT_POST_PROCESING_H

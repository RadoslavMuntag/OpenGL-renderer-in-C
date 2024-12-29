//
// Created by muntr on 3. 11. 2024.
//

#include "post_procesing.h"

FBO *create_fbo(MeshList* mesh_list, int width, int height){
    FBO *fbo = (FBO*)malloc(sizeof(FBO));

    glGenFramebuffers(1, &fbo->handle);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->handle);

    fbo->framebufferTex = (TexComponent*)malloc(sizeof(TexComponent));
    //create_empty_Texture(fbo->framebufferTex, GL_NEAREST, width, height);
    glGenTextures(1, &fbo->framebufferTex->ref);
    glBindTexture(GL_TEXTURE_2D, fbo->framebufferTex->ref);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->framebufferTex->ref, 0);

    glGenRenderbuffers(1, &fbo->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,fbo->rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fbo->rbo);

    int auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        printf("Framebuffer error: %x %d %d\n", fboStatus, width, height);

    float rectangleVertices[] =
            {
                    // Coords    // texCoords
                    1.0f, -1.0f,  1.0f, 0.0f,
                    -1.0f, -1.0f,  0.0f, 0.0f,
                    -1.0f,  1.0f,  0.0f, 1.0f,

                    1.0f,  1.0f,  1.0f, 1.0f,
                    1.0f, -1.0f,  1.0f, 0.0f,
                    -1.0f,  1.0f,  0.0f, 1.0f
            };

    glGenVertexArrays(1, &fbo->frame_mesh.vao.handle);
    glGenBuffers(1, &fbo->frame_mesh.vbo.handle);
    glBindVertexArray(fbo->frame_mesh.vao.handle);
    glBindBuffer(GL_ARRAY_BUFFER, fbo->frame_mesh.vbo.handle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    //create_mesh_component(mesh_list, "../assets/jus_plane.obj");
    //fbo->frame_mesh = get_mesh_by_id(mesh_list,0);


    fbo->frame_shader = shader_create(
            "../shaders/frame_buffer.vert", "../shaders/frame_buffer.frag",
            2, (struct VertexAttr[]){
                    {.index = 0, .name = "aPos"},
                    {.index = 1, .name = "aTexCoords"}
            });
    glUseProgram(fbo->frame_shader.handle);
    glUniform1i(glGetUniformLocation(fbo->frame_shader.handle,"screenTexture"), 0);

    return fbo;
}

void resize_fbo(FBO *fbo, int width, int height){
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->handle);

    glDeleteTextures(1, &fbo->framebufferTex->ref);
    //create_empty_Texture(fbo->framebufferTex, GL_NEAREST, width, height);
    glGenTextures(1, &fbo->framebufferTex->ref);
    glBindTexture(GL_TEXTURE_2D, fbo->framebufferTex->ref);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->framebufferTex->ref, 0);

    glDeleteRenderbuffers(1, &fbo->rbo);
    glGenRenderbuffers(1, &fbo->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,fbo->rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fbo->rbo);

    int auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        printf("Framebuffer error: %x %d %d\n", fboStatus, width, height);
}

void fbo_destroy(FBO *fbo){
    glDeleteTextures(1, &fbo->framebufferTex->ref);
    free(fbo->framebufferTex);

    glDeleteRenderbuffers(1, &fbo->rbo);
    glDeleteFramebuffers(1, &fbo->handle);

    shader_destroy(fbo->frame_shader);

    free(fbo);
}
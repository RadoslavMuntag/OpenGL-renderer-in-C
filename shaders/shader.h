//
// Created by muntr on 18. 9. 2024.
//

#ifndef MYGLFWPROJECT_SHADER_H
#define MYGLFWPROJECT_SHADER_H
#define _CRT_SECURE_NO_WARNINGS


#include "../rendering/gfx_h.h"
#include "../utils/utils.h"

struct VertexAttr {
    GLuint index;
    const GLchar *name;
};


struct Shader {
    GLuint handle, vs_handle, fs_handle;
};

struct Shader shader_create(char *vs_path, char *fs_path, size_t n, struct VertexAttr attributes[]);
void shader_destroy(struct Shader self);
void shader_bind(struct Shader self);
struct Shader shader_fragment_create(char *fs_path);
//void shader_uniform_mat4(struct Shader self, char *name, mat4s m);
//void shader_uniform_view_proj(struct Shader self, struct ViewProj view_proj);
//void shader_uniform_texture2D(struct Shader self, char *name, struct Texture texture, GLuint n);
//void shader_uniform_float(struct Shader self, char *name, f32 f);
//void shader_uniform_vec2(struct Shader self, char *name, vec2s v);
//void shader_uniform_vec3(struct Shader self, char *name, vec3s v);
//void shader_uniform_vec4(struct Shader self, char *name, vec4s v);
void shader_uniform_int(struct Shader self, char *name, int v);
void shader_uniform_uint(struct Shader self, char *name, unsigned int v);

#endif //MYGLFWPROJECT_SHADER_H

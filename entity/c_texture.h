//
// Created by muntr on 2. 11. 2024.
//

#ifndef MYGLFWPROJECT_C_TEXTURE_H
#define MYGLFWPROJECT_C_TEXTURE_H
#include "../rendering/gfx_h.h"
#include <stb/stb_image.h>
#include "../utils/utils.h"

typedef struct {
    GLuint ref;
}TexComponent;

int loadTexture(TexComponent *texture, const char *filename, GLint texScaling);
void create_empty_Texture(TexComponent *texture, GLint texScaling, int width, int height);
#endif //MYGLFWPROJECT_C_TEXTURE_H

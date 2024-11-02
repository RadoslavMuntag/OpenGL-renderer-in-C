//
// Created by muntr on 2. 11. 2024.
//

#include "c_texture.h"
int loadTexture(TexComponent *texture, const char *filename, GLint texScaling){
    int imgWidth, imgHeight, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(filename, &imgWidth, &imgHeight, &numColCh,0);

    if (bytes == NULL) {
        // Handle error
        printf("Failed to load texture file: %s\n", stbi_failure_reason());
        return 1;
    }

    glGenTextures(1, &texture->ref);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->ref);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texScaling);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texScaling);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    return 0;
}
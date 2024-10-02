
#include <stdio.h>

#include "rendering/window.h"

 /*
  The code is just passion project and I still don't know what its direction is.
  It's a very simple object renderer with glfw library.
  The foundation of the code is heavily inspired (and sometimes straight up copied) from
  project minecraft-weekend by jdah https://github.com/jdah/minecraft-weekend/tree/master.
  I am just learning basics of glfw library and thought that this is a perfect way to start.
  */


 void init_gl(){
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        exit(-1);
    }

    window_create();
    window_loop();
}

int main() {

    init_gl();
    glfwTerminate();
    return 0;
}

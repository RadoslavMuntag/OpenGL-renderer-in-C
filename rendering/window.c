//
// Created by muntr on 20. 9. 2024.
//

#include "window.h"

struct Window window;

static uint64_t maxim(uint64_t time, int i);

static void _size_callback(GLFWwindow *handle, int width, int height){
    //glViewport(0, 0, width, height);
    window.width = width;
    window.height = height;
    cam_resize(&window.camera,width, height);

    glViewport(0,0,window.width,window.height);


}

static void _key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods){
    if (key < 0) {
        return;
    }

    switch (action) {
        case GLFW_PRESS:
            window.keyboard.keys[key].down = true;
            break;
        case GLFW_RELEASE:
            window.keyboard.keys[key].down = false;
            break;
        default:
            break;
    }
}

void GLAPIENTRY
    MessageCallback(GLenum source,
                    GLenum type,
                    GLuint id,
                    GLenum severity,
                    GLsizei length,
                    const GLchar* message,
                    const void* userParam){
    printf("Opengl Error: %s\n", message);
}

void rotate_a_bit(vec3* cameraPos){

    vec3 y_axis = {0.0f,1.0f,0.0f};
    glm_vec3_rotate(cameraPos[0],-0.003f, y_axis);
//    vec3 z_axis = {0.0f,0.0f,1.0f};
//    glm_vec3_rotate(cameraPos[0],-0.003f, z_axis);

}

void window_create(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,1);

    window.width = 1080;
    window.height = 720;
    window.handle = glfwCreateWindow(window.width, window.height, "OpenGL Window", NULL, NULL);

    window.last_frame = NOW();
    window.last_second = NOW();

    // Get the primary monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // Get the video mode of the monitor
    window.videoMode = glfwGetVideoMode(monitor);

    if (!window.handle) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        exit(-1);
    }

    // Query and print the OpenGL version

    glfwMakeContextCurrent(window.handle);
    gladLoadGL();

    const GLubyte* version = glGetString(GL_VERSION);
    printf("OpenGL version: %s\n", version);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    glViewport(0,0,window.width,window.height);

    glfwSetFramebufferSizeCallback(window.handle, _size_callback);
    glfwSetKeyCallback(window.handle, _key_callback);

    renderer_create(&window.renderer);
    camera_create(&window.camera, window.width, window.height);
    window.time_from_start = glfwGetTime();


}

static void _destroy(){
    renderer_destroy(&window.renderer);
    glfwDestroyWindow(window.handle);
}

static void _tick(){
    window.ticks++;
    tick(&window.keyboard, &window.camera, &window.renderer.entityList, window.videoMode->refreshRate, window.time_from_start - glfwGetTime());
    //rotate_a_bit(&window.renderer.sun_pos);
}

static void _render(){
    window.frames++;
    renderer_update(&window.renderer, &window.camera);
}

static void _handle_time(){
    const uint64_t now = NOW();

    window.frame_delta = now - window.last_frame;
    window.last_frame = now;

    if (now - window.last_second > NS_PER_SECOND) {
        window.fps = window.frames;
        window.tps = window.ticks;
        window.frames = 0;
        window.ticks = 0;
        window.last_second = now;

        printf("FPS: %llu | TPS: %llu | RefreshRate: %d\n", window.fps, window.tps, window.videoMode->refreshRate);
    }

    // tick processing
    const uint64_t NS_PER_TICK = (NS_PER_SECOND / window.videoMode->refreshRate);
    uint64_t tick_time = window.frame_delta + window.tick_remainder;
    while (tick_time > NS_PER_TICK) {
        _tick();
        tick_time -= NS_PER_TICK;
    }
    window.tick_remainder = maxim(tick_time, 0);
}

static uint64_t maxim(uint64_t time, int i) {
    return time > i ? time : i;
}


void window_loop(){

    while (!glfwWindowShouldClose(window.handle)) {
        _handle_time();

        update_camera(&window.camera);
        _render();
        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    _destroy();
}

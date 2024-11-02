cmake_minimum_required(VERSION 3.10)
project(MyGLFWProject)

# Set the C standard or C++ standard (if you're using C++)
set(CMAKE_C_STANDARD 99)

# Set GLFW include directory
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include)

# Add the source files
set(SOURCES
        main.c
        rendering/EBO.c
        rendering/VAO.c
        rendering/VBO.c
        rendering/VBO.h
        rendering/VAO.h
        rendering/EBO.h
        shaders/shader.c
        shaders/shader.h
        rendering/gfx_h.h
        utils/utils.h
        rendering/window.c
        rendering/window.h
        rendering/renderer.c
        rendering/renderer.h
        utils/rand_obj_data.c
        utils/rand_obj_data.h
        utils/camera.c
        utils/camera.h
        utils/algebra.c
        utils/algebra.h
        utils/time.h
        entity/control.c
        entity/control.h
        entity/entity.c
        entity/entity.h
        rendering/Mesh.c
        rendering/Mesh.h
        glad.c
        entity/c_transform.c
        entity/c_transform.h
        entity/c_physics.c
        entity/c_physics.h
        entity/c_mesh.c
        entity/c_mesh.h
        entity/components.h
        stb.c
        entity/c_light.c
        entity/c_light.h
        entity/c_texture.c
        entity/c_texture.h
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify the GLFW library files to link
# For static linking:
set(GLFW_LIB_PATH ${CMAKE_SOURCE_DIR}/dependencies/lib)
target_link_directories(${PROJECT_NAME} PRIVATE ${GLFW_LIB_PATH})

# Specify the path to GLM
set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependencies/include/cglm/include/cglm")

# Include GLM headers
include_directories(${GLM_INCLUDE_DIR})

# If you're using static linking:
# Link with glfw3.lib (static version) and opengl32 (OpenGL library)
# Detect the platform and apply different libraries accordingly
if(WIN32)
    message(STATUS "Building for Windows")
    # Link Windows-specific libraries
    target_link_libraries(${PROJECT_NAME} glfw3 opengl32)
elseif(UNIX)
    message(STATUS "Building for Linux")
    # Link Linux-specific libraries
    target_link_libraries(${PROJECT_NAME} m glfw GL)
endif()

# If you want to link against the multi-threaded version, use glfw3_mt.lib:
# target_link_libraries(${PROJECT_NAME} glfw3_mt opengl32)

# For dynamic linking (with glfw3dll.lib):
# target_link_libraries(${PROJECT_NAME} glfw3dll opengl32)

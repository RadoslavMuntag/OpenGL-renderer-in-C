#version 330 core

layout(location = 0) in vec3 aPos; // Full-screen quad or dome vertex positions

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos; // Pass the fragment's position to the fragment shader

void main() {
    fragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);  // Project to clip space
}

#version 330 core

// Input attributes from the application
layout(location = 0) in vec3 aPos;   // Vertex position
layout(location = 2) in vec3 aNormal;
layout(location = 3) in float amtlID; // Vertex color

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Output to the fragment shader
out vec3 FragPos;
out vec3 Normal;
out float mtlID;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    // Pass the color to the fragment shader
    mtlID = amtlID;

    // Set the position of the vertex
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

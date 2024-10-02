#version 330 core
#define MAX_MATERIALS 32

struct Material {
    float Ns; // specular exponent
    vec3 Ka; // ambient lighting
    vec3 Kd; // diffuse lighting
    vec3 Ks; // specular highlights color and intensity
};


in vec3 FragPos;
in vec3 Normal;
in float mtlID;

out vec4 color;


uniform Material materials[MAX_MATERIALS];
uniform mat4 view;
uniform mat4 projection;
uniform vec2 winSize;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 skyColor;     // Sky color for tinting
uniform vec3 skyDir = vec3(0.0, 1.0, 0.0);  // World-space up vector representing the sky direction (upwards)

uniform float constantAttenuation = 1.0;  // Attenuation parameters
uniform float linearAttenuation = 0.12;
uniform float quadraticAttenuation = 0.10;
//uniform float linearAttenuation = 0.0;
//uniform float quadraticAttenuation = 0.0;

float near = 0.1f;
float far = 1000.0f;

float linear_depth(float depth){
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float distance_to_light(){
    // Transform light position from world space to clip space
    vec4 lightPosClip = projection * view * vec4(lightPos, 1.0);

    // Perspective divide to get light position in NDC
    vec3 lightPosNDC = lightPosClip.xyz / lightPosClip.w;

    // Convert NDC (-1 to 1) to window coordinates (0 to screen width/height)
    vec2 lightPosScreen = (lightPosNDC.xy * 0.5 + 0.5) * winSize;

    // Get fragment position in window space (gl_FragCoord is in window space)
    vec2 fragPosScreen = gl_FragCoord.xy;

    // Compute the 2D distance between the fragment and the projected light position
    float distance2D = distance(fragPosScreen, lightPosScreen);
    return distance2D;
}

void main()
{
    int new_mtlID = int(mtlID);

    // Compute the distance between the fragment and the light source
    float distance = length(lightPos - FragPos);

    // Calculate attenuation
    float attenuation = 1.0 / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance);

    // Ambient lighting
    float ambientStrength = 0.2f;
    vec3 ambient = materials[new_mtlID].Kd * ambientStrength;

    // Normal and light direction
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = materials[new_mtlID].Kd * diff;

    // Specular lighting
    float specularStrength = 1.0f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materials[new_mtlID].Ns);
    vec3 specular = materials[new_mtlID].Ks * spec;

    // Combine lighting results
    vec3 lightingResult = (ambient + diffuse + specular)* lightColor * attenuation;

    // Additional tint based on facing the sky
    float facingSky = dot(norm, skyDir);  // Dot product to determine if facing the sky
    if (facingSky >= -0.0f) {
        // If the surface is facing the sky, blend with sky color
        float skyTintFactor = min(facingSky,0.3f);  // Directly use the dot product value for blending
        lightingResult = lightingResult + skyColor * skyTintFactor;
    }

    float light_frag_distance = distance_to_light();
    float win_attenuation = 1.0 / (constantAttenuation + 0.05 * light_frag_distance + 0.001 * light_frag_distance * light_frag_distance);
    lightingResult = lightingResult + (lightColor * win_attenuation);


    //gamma correction
    /*if(gl_FragCoord.x < winSize[0]/2){
        lightingResult = pow(lightingResult, vec3(1.0/2.2));
    }*/
    lightingResult = pow(lightingResult, vec3(1.0/2.2));


    //lightingResult = lightingResult + (lightColor * attenuation / 10);

    // Output the final color
    //color = vec4(lightingResult, 1.0);

    float depth = linear_depth(gl_FragCoord.z)/10;
    color = vec4(lightingResult, 1.0) * (1.0f - depth) + vec4(depth * skyColor, 1.0f);

    //color = vec4(mix(lightingResult , skyColor , linear_depth(gl_FragCoord.z)/far ), 1.0);
}

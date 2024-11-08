#version 330 core
#define MAX_MATERIALS 32

struct Material {
    float Ns; // specular exponent
    vec3 Ka; // ambient lighting
    vec3 Kd; // diffuse lighting
    vec3 Ks; // specular highlights color and intensity
};


in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;
flat in int mtlID;

out vec4 color;


uniform Material materials[MAX_MATERIALS];
uniform sampler2D textureSampler;
uniform int texturedIndex;

uniform mat4 view;
uniform mat4 projection;
uniform vec2 winSize;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 skyColor;     // Sky color for tinting
uniform vec3 skyDir = vec3(0.0, 1.0, 0.0);  // World-space up vector representing the sky direction (upwards)

uniform float constantAttenuation = 1.0;  // Attenuation parameters
uniform float linearAttenuation = 0.7;
uniform float quadraticAttenuation = 1.8;
//uniform float linearAttenuation = 0.0;
//uniform float quadraticAttenuation = 0.0;

float near = 0.1f;
float far = 1000.0f;

float linear_depth(float depth){
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

bool is_fragment_behind_light(){
    float fragment_to_view = length(FragPos - viewPos);
    float light_to_view = length(lightPos - viewPos);

    vec3 view_to_fragment = normalize(FragPos - viewPos);
    vec3 view_to_light = normalize(lightPos - viewPos);
    float dot = dot(view_to_fragment, view_to_light);

    return (dot < 0.95) || (light_to_view <= fragment_to_view + 0.3);
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
    vec3 Kd_color;
    if (mtlID == texturedIndex){
        Kd_color = vec3(texture(textureSampler, TexCoords));
    }
    else{
        Kd_color = materials[mtlID].Kd;
    }
    // Compute the distance between the fragment and the light source
    float distance = length(lightPos - FragPos);

    // Calculate attenuation
    float attenuation = 1.0 / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance);

    // Ambient lighting
    float ambientStrength = 0.2f;
    vec3 ambient = Kd_color * ambientStrength;

    // Normal and light direction
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = Kd_color * diff;

    // Specular lighting
    float specularStrength = 1.0f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materials[mtlID].Ns);
    vec3 specular = materials[mtlID].Ks * spec;

    // Combine lighting results
    vec3 lightingResult = (ambient + diffuse + specular)* lightColor * attenuation;

    // Additional tint based on facing the sky
    float facingSky = dot(norm, skyDir);  // Dot product to determine if facing the sky
    if (facingSky >= -0.0f) {
        // If the surface is facing the sky, blend with sky color
        float skyTintFactor = min(facingSky,0.3f) * 0.5;  // Directly use the dot product value for blending
        lightingResult = lightingResult + skyColor * skyTintFactor;
    }

    if (is_fragment_behind_light()){
        float light_frag_distance = distance_to_light();
        float win_attenuation = 1.0 / (constantAttenuation + 0.005 * light_frag_distance + 0.005 * light_frag_distance * light_frag_distance);
        lightingResult = lightingResult + (lightColor * win_attenuation);
    }

    float depth = linear_depth(gl_FragCoord.z)/25;
    vec4 end_result = vec4(lightingResult, 1.0) * (1.0f - depth) + vec4(depth * skyColor, 1.0f);

    //gamma correction
    //if(gl_FragCoord.x < winSize[0]/2){
        //end_result = pow(end_result, vec4(1.0/2.2));
    //}
    end_result = pow(end_result, vec4(1.0/2.2));


    //lightingResult = lightingResult + (lightColor * attenuation / 10);

    // Output the final color
    color = end_result;

    //color = vec4(lightingResult, 1.0);

    //color = vec4(lightingResult, 1.0) * (1.0f - depth) + vec4(depth * skyColor, 1.0f);

    //color = vec4(mix(lightingResult , skyColor , linear_depth(gl_FragCoord.z)/far ), 1.0);
}

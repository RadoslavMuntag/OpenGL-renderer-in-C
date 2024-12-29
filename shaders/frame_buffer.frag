#version 330

in vec2 texCoords;
out vec4 FragColor;

const float kernel[9] = float[](
-1, -1, -1,
-1,  12, -1,
-1, -1, -1
);

uniform sampler2D screenTexture;
uniform float pixelSize = 8;
uniform vec2 winSize;

void main() {
    vec2 tex_offset = 1.0 / textureSize(screenTexture, 0);
    vec3 result = vec3(0.0);

    vec2 pixelatedCoords = (floor((texCoords * winSize) / pixelSize) * pixelSize) / winSize;

    result += texture(screenTexture, texCoords + tex_offset * vec2(-1, -1)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2( 0, -1)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2( 1, -1)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2(-1,  0)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2( 0,  0)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2( 1,  0)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2(-1,  1)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2( 0,  1)).rgb;
    result += texture(screenTexture, texCoords + tex_offset * vec2( 1,  1)).rgb;
    result /= 9;

    //vec2 pixelatedCoords = floor(texCoords / pixelSize) * pixelSize;

    /*if (texCoords[0] < (0.5) ){
        result = texture(screenTexture, pixelatedCoords).rgb;
    }*/
    result = pow(result, vec3(1.0/2.2));


    FragColor = vec4(result,1);

}
#version 330 core

in vec3 fragPos; // The position of the fragment in world space
out vec4 FragColor;

// Uniforms to control time of day and other parameters
uniform float timeOfDay;  // Value between 0.0 (midnight) to 1.0 (next midnight)
uniform vec3 sunDirection; // Direction of the sun in world space
uniform float starVisibility; // Controls how many stars are visible at night (0.0 to 1.0)

vec3 dayColor = vec3(0.4, 0.7, 1.0);  // Light blue for daytime sky
vec3 duskColor = vec3(1.0, 0.5, 0.2); // Orange-pink for sunset
vec3 nightColor = vec3(0.0, 0.0, 0.1); // Dark blue for nighttime

// Function to compute the sky color based on the sun's position
vec3 computeSkyColor(float sunElevation) {
    // Mix between night, dusk, and day colors
    if (sunElevation < 0.2) {
        return mix(nightColor, duskColor, smoothstep(0.0, 0.2, sunElevation));
    } else {
        return mix(duskColor, dayColor, smoothstep(0.2, 1.0, sunElevation));
    }
}

// Function to compute the sun's glow
vec3 computeSun(float sunElevation, vec3 fragDirection) {
    float sunSize = 0.02;  // Size of the sun disc
    float sunFactor = smoothstep(sunSize, sunSize * 0.9, length(fragDirection - sunDirection));
    vec3 sunColor = vec3(1.0, 1.0, 0.8);  // Bright yellow for the sun

    return sunFactor * sunColor;
}

// Function to add stars at night
vec3 computeStars(vec3 fragDirection, float starVisibility) {
    float starIntensity = max(0.0, dot(normalize(fragDirection), vec3(0.0, 1.0, 0.0)));
    float starFactor = pow(starIntensity, 20.0);  // Exaggerates star size and sharpness
    vec3 starColor = vec3(1.0, 1.0, 1.0) * starFactor * starVisibility;

    return starColor;
}

void main() {
    // Compute the direction the fragment is facing (view direction)
    vec3 fragDirection = normalize(fragPos);

    // Calculate the sun's elevation in the sky (dot product between sun direction and up vector)
    float sunElevation = clamp(dot(normalize(sunDirection), vec3(0.0, 1.0, 0.0)), 0.0, 1.0);

    // Compute sky color based on sun elevation
    vec3 skyColor = computeSkyColor(sunElevation);

    // Add the sun to the sky
    vec3 sun = computeSun(sunElevation, fragDirection);

    // Add stars (only visible at night)
    vec3 stars = computeStars(fragDirection, (1.0 - sunElevation) * starVisibility);

    // Combine all elements: sky, sun, and stars
    vec3 finalColor = skyColor + sun + stars;

    // Output the final color
    FragColor = vec4(finalColor, 1.0);
}


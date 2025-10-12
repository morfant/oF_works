// bg.frag
#version 150
uniform float uTime;
uniform vec2 uResolution;
in vec2 vUv;
out vec4 fragColor;

const float TAU = 6.28318530718;

vec2 hash2(vec2 p) {
    vec3 p3 = fract(vec3(p.xyx) * 0.1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((vec2(p3.x, p3.y) + vec2(p3.z, p3.x)) * 0.5);
}

float starField(vec2 uv, vec2 aspect, float density) {
    vec2 uvAspect = (uv - 0.5) * aspect + 0.5;
    vec2 gridUv = uvAspect * density;

    vec2 baseCell = floor(gridUv);
    vec2 cellFrac = fract(gridUv);

    float brightness = 0.0;

    for (int j = -1; j <= 1; ++j) {
        for (int i = -1; i <= 1; ++i) {
            vec2 cell = baseCell + vec2(i, j);
            vec2 rnd = hash2(cell);

            float speed = mix(0.15, 0.6, hash2(cell + 3.1).x);
            float orbitRadius = mix(0.05, 0.35, rnd.y);
            float angle = uTime * speed + rnd.x * TAU;
            vec2 orbital = vec2(cos(angle), sin(angle)) * orbitRadius;

            vec2 starCenter = rnd + orbital;
            vec2 diff = vec2(i, j) + starCenter - cellFrac;
            diff.x /= aspect.x;

            float dist = length(diff);
            float shape = smoothstep(0.22, 0.0, dist);
            shape *= smoothstep(0.05, 0.18, dist); // hollow out the center slightly

            float twinkle = 0.4 + 0.6 * sin(uTime * mix(2.0, 5.0, rnd.x) + rnd.y * TAU);

            brightness += shape * twinkle;
        }
    }

    return brightness;
}

void main() {
    vec2 aspect = vec2(uResolution.x / max(uResolution.y, 1.0), 1.0);

    float denseStars = starField(vUv, aspect, 46.0);
    float sparseStars = starField(vUv * 0.7 + 0.11, aspect, 18.0);

    float glow = denseStars * 0.7 + sparseStars * 1.3;
    glow = pow(clamp(glow, 0.0, 1.0), 1.4);

    vec3 background = vec3(0.01, 0.012, 0.02);
    vec3 starColor = vec3(0.75, 0.82, 1.0);
    vec3 color = background + starColor * glow;

    fragColor = vec4(min(color, 1.0), 1.0);
}

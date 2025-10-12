// bg.vert
#version 150
in vec4 position;
in vec2 texcoord;
out vec2 vUv;

void main() {
    vUv = texcoord;
    gl_Position = position;
}

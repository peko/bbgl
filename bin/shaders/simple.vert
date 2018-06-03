#version 330

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 col;
layout (location = 2) in vec2 uv;

smooth out vec4 theCol;
smooth out vec2 theUv;

void main() {
    gl_Position = pos;
    gl_Position.xyz/=2.0;
    theUv  = uv;
    theCol = col;
}

#version 330

uniform mat4 mvp;

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 col;
layout (location = 2) in vec2 uv;

smooth out vec4 theCol;
smooth out vec2 theUv;

void main() {
    gl_Position = mvp*pos;
    theUv  = uv;
    theCol = col;
}

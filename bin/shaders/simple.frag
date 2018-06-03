#version 330

smooth in vec2 theUv;
smooth in vec4 theCol;

out vec4 col;

void main() {
    col = theCol;
}

#pragma once

#include <GL/gl3w.h>

typedef struct {
	GLuint prog;
	GLuint mvp;
	GLuint col;
	GLuint pos;
} shader_t;
typedef shader_t* shader_p;

shader_p shader_ctor(char* shader_name);
void shader_dtor(shader_p shader);

void shader_start(shader_p shader);
void shader_stop (shader_p shader);

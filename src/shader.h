#pragma once

typedef struct {
	GLuint prog;
	GLuint mvp;
	GLuint col;
	GLuint pos;
} shader_t;

shader_t shader_load(char* shader_name);
void shader_delete(shader_t shader);


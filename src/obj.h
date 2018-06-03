#pragma once

#include <GL/gl3w.h>

typedef struct obj_t {
    GLuint vao;
    GLuint vbo;
    size_t size;
} obj_t;
typedef obj_t* obj_p;

obj_p obj_ctor();
void obj_dtor(obj_p obj);

obj_p obj_plane();
void obj_render(obj_p obj);


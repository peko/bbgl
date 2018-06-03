#pragma once

typedef struct obj_t {
    shader_t shader;
    vbo_t    vbo;   
} obj_t;
typedef obj_t* obj_p;

obj_p obj_ctor();
void obj_dtor(obj_p obj);

void obj_draw(obj_p obj);


#include "obj.h"

obj_p
obj_ctor() {
    obj_p obj = calloc(1,sizeof(obj_t));
	obj->shader = shader_load("simple");
	obj->vbo    = vbo_new();
	return obj;
}

obj_p obj_dtor(obj_p obj){
	vbo_delete(obj->bo);
	shader_delete(obj->shader);
	free(obj_p)
}

void obj_draw(obj_p obj) {
	shader_set(obj->shader)
	vbo_set(obj->vbo);
}

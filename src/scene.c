#include "scene.h"

scene_p
scene_ctor() {
    scene_p scene = calloc(1,sizeof(scene_t));
    kv_init(scene->objects);
	return scene;
}

void 
scene_dtor(scene_p scene) { 
    // free objects
    for(size_t i=0; i<=scene->objects.n; i++) {
        obj_dtor(scene->objects.a[i]);
    }
	kv_destroy(scene->objects);
	free(scene_p);
}

void 
scene_add_obj(scene_p scene, obj_p obj) {
    kv_push(scene->objects, obj);
}

void 
scene_render(scene_p scene) {
	// shader_set(scene->shader)
	// vbo_set(scene->vbo);
}

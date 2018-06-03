#include "scene.h"
#include "obj.h"
#include "shader.h"

shader_p shader;

scene_p
scene_ctor() {
    scene_p scene = calloc(1, sizeof(scene_t));
    kv_init(scene->objects);
    
    shader = shader_ctor("simple");
    obj_p o = obj_plane();
    scene_add_obj(scene, o);
    
	return scene;
}

void 
scene_dtor(scene_p scene) { 
    // free objects
    for(size_t i=0; i<scene->objects.n; i++) {
        obj_dtor(scene->objects.a[i]);
    }
	kv_destroy(scene->objects);
	free(scene);
}

void 
scene_add_obj(scene_p scene, obj_p obj) {
    kv_push(obj_p, scene->objects, obj);
}

void 
scene_render(scene_p scene) {
    shader_start(shader);
    for(size_t i=0; i<scene->objects.n; i++) {
        obj_render(scene->objects.a[i]);
    }
    shader_stop(shader);
}

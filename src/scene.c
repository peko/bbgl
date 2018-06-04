#include "scene.h"
#include "obj.h"
#include "shader.h"

shader_p shader;

scene_p
scene_ctor() {
    scene_p scene = calloc(1, sizeof(scene_t));
    kv_init(scene->objects);
    
    mat4x4_perspective(scene->p, 60, 1.0, 0.0001, 1000.0);
    mat4x4_look_at(scene->v, 
    	(vec3){1.0,1.0,1.0}, 
    	(vec3){0.0,0.0,0.0},
    	(vec3){0.0,1.0,0.0});

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
        mat4x4 mvp;
        mat4x4_mul(mvp, scene->p, scene->v);
        mat4x4_mul(mvp, mvp, scene->objects.a[i]->m);
        glUniformMatrix4fv(shader->mvp, 1, GL_FALSE, (const GLfloat*) mvp);
        obj_render(scene->objects.a[i]);
    }
    shader_stop(shader);
}

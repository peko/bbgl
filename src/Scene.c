#include "Scene.h"
#include "Drawable.h"
#include "shader.h"

Shader* shader;

static void AddObject(Scene*, Drawable*);

static void
Init(Scene* outScene){
    kv_init(outScene->objects);
    mat4x4_perspective(outScene->p, 30, 1.0, 0.0001, 1000.0);
    mat4x4_look_at(outScene->v, 
    	(vec3){1.0,1.0,1.0}, 
    	(vec3){0.0,0.0,0.0},
    	(vec3){0.0,1.0,0.0});

    shader = AShader->Create("simple");
    Drawable* d = ADrawable->Create();
    AddObject(outScene, d);
}

static Scene*
Create() {
    Scene* scene = calloc(1, sizeof(Scene));
    Init(scene); 
	return scene;
}

static void 
Release(Scene* scene) { 
    // free objects
    for(size_t i=0; i<scene->objects.n; i++) {
        ADrawable->Release(scene->objects.a[i]);
    }
	kv_destroy(scene->objects);
	AShader->Release(shader);
	free(scene);
}

static void
AddObject(Scene* scene, Drawable* d) {
    kv_push(Drawable*, scene->objects, d);
}

static void 
Render(Scene* scene) {

    static int n = 0;
    n++;
    float x = 5.0*sin(n/100.0);
    float z = 5.0*cos(n/100.0);
    mat4x4_look_at(scene->v, 
    	(vec3){  x,1.0,  z}, 
    	(vec3){0.0,0.0,0.0},
    	(vec3){0.0,1.0,0.0});
    AShader->Start(shader);
    for(size_t i=0; i<scene->objects.n; i++) {
        Drawable* d = scene->objects.a[i];
        mat4x4 mvp;
        mat4x4_mul(mvp, scene->p, scene->v);
        mat4x4_mul(mvp, mvp, d->m);
        glUniformMatrix4fv(shader->mvp, 1, GL_FALSE, (const GLfloat*) mvp);

        ADrawable->Render(d);
    }
    AShader->Stop(shader);
}

// ----------------------------------------------------------------------------

struct AScene AScene[1] = {{
	Create,
	Init,
	Release,
	Render,
	AddObject,
}};

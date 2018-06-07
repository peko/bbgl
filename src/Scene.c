#include "Scene.h"
#include "Shape.h"
#include "Drawable.h"
#include "Shader.h"

Shader* shader;

static void AddObject(Scene*, Drawable*);
static void Resize(Scene*, int, int);

static void
Init(Scene* outScene){
    kv_init(outScene->objects);
    Resize(outScene, 320, 240);
    shader   = AShader->Create("simple");
    Shape* s = AShape->Create();
    AddObject(outScene, s->drawable);
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
Resize(Scene* outScene, int width, int height) {
    outScene->ratio = (float)width/height;
    mat4x4_perspective(outScene->p, 30, outScene->ratio, 0.0001, 1000.0);
    mat4x4_look_at(outScene->v, 
        (vec3){1.0,1.0,1.0}, 
        (vec3){0.0,0.0,0.0},
        (vec3){0.0,1.0,0.0});
}

/*
static void print_vec(vec4 v) {
    for(int i=0;i<4;i++) printf("%f ",v[i]);
    printf("\n");
}
static void print_mat(char* n, mat4x4 m){
    printf("-%s-\n",n);
    for(int i=0;i<4;i++) print_vec(m[i]);
}
*/

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
        //print_mat("p", d->m);
        glUniformMatrix4fv(shader->mvp, 1, GL_FALSE, (const GLfloat*) mvp);

        ADrawable->Render(d);
    }
    AShader->Stop(shader);
}


/*
void 
scene_render(scene_p scene) {

    static int n = 0;
    n++;
    float x = 5.0*sin(n/100.0);
    float z = 5.0*cos(n/100.0);
    mat4x4_look_at(scene->v, 
    	(vec3){  x,1.0,  z}, 
    	(vec3){0.0,0.0,0.0},
    	(vec3){0.0,1.0,0.0});
    shader_start(shader);
    for(size_t i=0; i<scene->objects.n; i++) {
        obj_p o = scene->objects.a[i];
        mat4x4 mvp;
        mat4x4_mul(mvp, scene->p, scene->v);
        // print_mat("p", scene->p);
        // print_mat("v", scene->v);
        // print_mat("m", o->m);
        mat4x4_mul(mvp, mvp, o->m);
        // print_mat("mvp", mvp);
        // printf("%d\n", shader->mvp); 
        glUniformMatrix4fv(shader->mvp, 1, GL_FALSE, (const GLfloat*) mvp);

        obj_render(o);
    }
    shader_stop(shader);
}*/

// ----------------------------------------------------------------------------

struct AScene AScene[1] = {{
    Create,
    Init,
    Release,
    Render,
    Resize,
    AddObject,
}};

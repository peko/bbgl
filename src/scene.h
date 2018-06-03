#pragma once
#include <kvec.h>

typedef kvec_t(obj_p) objects_v;

typedef struct scene_t {
    objects_v objects;
} scene_t;
typedef scene_t* scene_p;

scene_p scene_ctor();
void scene_dtor(scene_p scene);

void scene_draw(scene_p scene);


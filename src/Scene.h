#pragma once

#include <kvec.h>
#include <linmath.h>

#include "Drawable.h"

typedef kvec_t(Drawable*) objects_v;

typedef struct Scene {
    objects_v objects;
    mat4x4 p,v;
} Scene;

struct AScene {
	Scene* (*Create   )();
	void   (*Init     )(Scene*);
	void   (*Release  )(Scene*);
	void   (*Render   )(Scene*);
	void   (*AddObject)(Scene*, Drawable*);
};

extern struct AScene AScene[1];


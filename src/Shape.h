#pragma once

#include "Drawable.h"

typedef struct Shape Shape;
struct Shape {
    Drawable drawable[1];
};

struct AShape {
    Shape* (*Create )();
    void   (*Init   )(Shape*);
    void   (*Release)(Shape*);
};
extern struct AShape AShape[1];

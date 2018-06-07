#pragma once

#include <GL/gl3w.h>
#include <linmath.h>

typedef struct Drawable Drawable;
struct Drawable {
    GLuint  vao;
    GLuint  vbo;
    mat4x4  m;
    GLenum  mode;
    GLsizei size;
};

struct ADrawable {
	Drawable* (*Create)();
	void (*Init   )(Drawable* outDrawable);
	void (*Release)(Drawable* drawable);
	void (*Render )(Drawable* drawable);
};

extern struct ADrawable ADrawable[1]; 

#include <stdlib.h>
#include <GL/gl3w.h>

#include "Drawable.h"

void InitPlane(Drawable* outDrawable);

static void
Init(Drawable *outDrawable) {
    mat4x4_identity(outDrawable->m);
	outDrawable->mode = GL_TRIANGLE_STRIP;
}

static Drawable* 
Create() {
    Drawable* drawable = malloc(sizeof(Drawable));
    Init(drawable);
    return drawable;
}

static void
Release(Drawable* drawable) {
    glDeleteBuffers(1, &drawable->vbo);
    glDeleteVertexArrays(1, &drawable->vao);
    free(drawable);
}

static void 
Render(Drawable* drawable) {
    glBindVertexArray(drawable->vao);
    // printf("%d", drawable->vao);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glDrawArrays(drawable->mode, 0, drawable->size);
    //glDisableVertexAttribArray(1); 
    //glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

// ----------------------------------------------------------------------------

struct ADrawable ADrawable[1] = {{
    .Create  = Create,
    .Init    = Init,
    .Release = Release,
    .Render  = Render
}};

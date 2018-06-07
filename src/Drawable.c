#include <stdlib.h>
#include <GL/gl3w.h>

#include "Drawable.h"

void InitPlane(Drawable* outDrawable);

static void
Init(Drawable *outDrawable) {
    mat4x4_identity(outDrawable->m);
    InitPlane(outDrawable);
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

void
InitPlane(Drawable* outDrawable) {
    #define POINT_SIZE 10
    const float pos_col_uv[4][POINT_SIZE] = {
        // pos                  col                   uv
        {-1.0,-1.0, 0.0, 1.0,   1.0, 0.0, 0.0, 1.0,   0.0, 0.0},
        {-1.0, 1.0, 0.0, 1.0,   0.0, 1.0, 0.0, 1.0,   0.0, 1.0},
        { 1.0,-1.0, 0.0, 1.0,   0.0, 0.0, 1.0, 1.0,   1.0, 1.0},
        { 1.0, 1.0, 0.0, 1.0,   0.0, 1.0, 1.0, 1.0,   1.0, 0.0},
    };
    outDrawable->size = 4;
    
    // allocate vertex array and bind it
    // https://stackoverflow.com/questions/16380005/opengl-3-4-glvertexattribpointer-stride-and-offset-miscalculation 
    glGenVertexArrays(1, &outDrawable->vao);
    glBindVertexArray(outDrawable->vao);
    {
        // allocate buffer objects for coordinates, colors and uvs
        glGenBuffers(1, &outDrawable->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, outDrawable->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pos_col_uv), pos_col_uv, GL_STATIC_DRAW);       
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(0*sizeof(GLfloat))); glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(4*sizeof(GLfloat))); glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(8*sizeof(GLfloat))); glEnableVertexAttribArray(2);
    }
    // unbind vbo & vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static void 
Render(Drawable* drawable) {
    glBindVertexArray(drawable->vao);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, drawable->size);
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

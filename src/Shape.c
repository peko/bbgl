#include <stdlib.h>

#include "Shape.h"

static void InitPlane(Shape*);

static void
Init(Shape* outShape) {
    ADrawable->Init(outShape->drawable);
    InitPlane(outShape);
}
static Shape*
Create() {
    Shape* shape = malloc(sizeof(Shape));
    Init(shape);
    return shape;
}

static void
Release(Shape* shape) {
    ADrawable->Release(shape->drawable);
}

static void
InitPlane(Shape* outShape) {
    Drawable* drawable = outShape->drawable;
    
    #define POINT_SIZE 10
    const float pos_col_uv[4][POINT_SIZE] = {
        // pos                  col                   uv
        {-1.0,-1.0, 0.0, 1.0,   1.0, 0.0, 0.0, 1.0,   0.0, 0.0},
        {-1.0, 1.0, 0.0, 1.0,   0.0, 1.0, 0.0, 1.0,   0.0, 1.0},
        { 1.0,-1.0, 0.0, 1.0,   0.0, 0.0, 1.0, 1.0,   1.0, 1.0},
        { 1.0, 1.0, 0.0, 1.0,   0.0, 1.0, 1.0, 1.0,   1.0, 0.0},
    };
    drawable->size = 4;
    
    // allocate vertex array and bind it
    // https://stackoverflow.com/questions/16380005/opengl-3-4-glvertexattribpointer-stride-and-offset-miscalculation 
    glGenVertexArrays(1, &drawable->vao);
    glBindVertexArray(drawable->vao);
    {
        // allocate buffer objects for coordinates, colors and uvs
        glGenBuffers(1, &drawable->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, drawable->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pos_col_uv), pos_col_uv, GL_STATIC_DRAW);       
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(0*sizeof(GLfloat))); glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(4*sizeof(GLfloat))); glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(8*sizeof(GLfloat))); glEnableVertexAttribArray(2);
    }
    // unbind vbo & vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

struct AShape AShape[1] = {{
    Create,
    Init,
    Release,
}};

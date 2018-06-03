#include <stdlib.h>
#include <GL/gl3w.h>

#include "obj.h"

obj_p
obj_ctor() {
    obj_p obj = calloc(1, sizeof(obj_t));
	return obj;
}

void
obj_dtor(obj_p obj) {
    glDeleteBuffers(1, &obj->vbo);
    glDeleteVertexArrays(1, &obj->vao);
	free(obj);
}

obj_p 
obj_plane() {
	obj_p obj = obj_ctor();
	#define POINT_SIZE 10
    const float pos_col_uv[4][POINT_SIZE] = {
        // pos                  col                   uv
        {-1.0,-1.0, 0.0, 1.0,   1.0, 0.0, 0.0, 1.0,   0.0, 0.0},
        {-1.0, 1.0, 0.0, 1.0,   0.0, 1.0, 0.0, 1.0,   0.0, 1.0},
        { 1.0,-1.0, 0.0, 1.0,   0.0, 0.0, 1.0, 1.0,   1.0, 1.0},
        { 1.0, 1.0, 0.0, 1.0,   0.0, 1.0, 1.0, 1.0,   1.0, 0.0},
    };
    obj->size = 4;
    
    // allocate vertex array and bind it
    // https://stackoverflow.com/questions/16380005/opengl-3-4-glvertexattribpointer-stride-and-offset-miscalculation 
    glGenVertexArrays(1, &obj->vao);
    glBindVertexArray(obj->vao);
    {
        // allocate buffer objects for coordinates, colors and uvs
        glGenBuffers(1, &obj->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pos_col_uv), pos_col_uv, GL_STATIC_DRAW);       
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(0*sizeof(GLfloat))); glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(4*sizeof(GLfloat))); glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, POINT_SIZE*sizeof(float), (GLvoid*)(8*sizeof(GLfloat))); glEnableVertexAttribArray(2);
    }
    // unbind vbo & vao
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return obj;
}

void 
obj_render(obj_p obj) {
    glBindVertexArray(obj->vao);
    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, obj->size);
    //glDisableVertexAttribArray(1); 
    //glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

#pragma once

#include <GL/gl3w.h>

typedef struct {
    GLuint prog;
    GLuint mvp;
    GLuint col;
    GLuint pos;
} Shader;

struct AShader {
   Shader* (*Create )(char*);
   void    (*Init   )(Shader*, char*);
   void    (*Release)(Shader*);
   void    (*Start  )(Shader*);
   void    (*Stop   )(Shader*);
};

extern struct AShader AShader[1];

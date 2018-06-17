#pragma once

#include "Shader.h"

struct AResources {
    Shader* (*GetShader)(char* name);
    void (*Init   )(void);
    void (*Release)(void);
};

extern struct AResources AResources[1];

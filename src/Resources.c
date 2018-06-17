#include <stdlib.h>
#include <stdio.h>

#include <khash.h>

#include "Resources.h"

KHASH_MAP_INIT_STR(shader_h, Shader*)
static khash_t(shader_h)* shaders = NULL;
static inline char* strdup(const char* c) {char* d=malloc(strlen(c)+1); strcpy(d,c); return d;}
static void 
Init(void) {
	shaders = kh_init(shader_h);
}

static void 
Release(void) {
    printf("Release shaders\n");
	for(khiter_t k=kh_begin(shaders); k!=kh_end(shaders); ++k) {
		if(kh_exist(shaders, k)) {
            // release shader
    		Shader* shader = kh_val(shaders, k);
			AShader->Release(shader);
			// release key
			char* key = (char*)kh_key(shaders, k);
			printf("\t\"%s\"\n",key);
			free(key);
		}
   	};
   	kh_destroy(shader_h, shaders);
}

static Shader* 
GetShader(char* name) {
	khiter_t k = kh_get(shader_h, shaders, name);
	Shader* s;
	// shader exists
	if (k != kh_end(shaders)) {
    	s = kh_value(shaders, k);
	} else {
    	printf("Create shader \"%s\"\n", name);
    	int ret;
		s = AShader->Create(name);
        // add new key
		k = kh_put(shader_h, shaders, strdup(name), &ret);
		// set key-value
		kh_value(shaders, k) = s;
	}
	return s;
}

struct AResources AResources[1] = {{
    .GetShader = GetShader,
	.Init    = Init,
	.Release = Release,
}};

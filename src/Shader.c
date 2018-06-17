#include <stdlib.h>
#include <stdio.h>

#include "Shader.h"

static void check_shader(GLuint sid);
static void load_file( char*  filename,  char** buf);

static void
Init(Shader* outShader, char* name) {
    
    char vert_name[256];
    char frag_name[256];
    char* vert_text;
    char* frag_text;
    
    sprintf(vert_name, "shaders/%s.vert", name);
    sprintf(frag_name, "shaders/%s.frag", name);
    
    load_file(vert_name, &vert_text);
    load_file(frag_name, &frag_text);

    GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_id, 1, (const char**)&vert_text, NULL);
    glCompileShader(vert_id);
    check_shader(vert_id);
    
    GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_id, 1, (const char**)&frag_text, NULL);
    glCompileShader(frag_id);
    check_shader(frag_id);

    outShader->prog = glCreateProgram();
    glAttachShader(outShader->prog, vert_id);
    glAttachShader(outShader->prog, frag_id);
    glLinkProgram (outShader->prog);

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
    
    outShader->mvp = glGetUniformLocation(outShader->prog, "mvp");
    // printf("mvp %d\n", outShader->mvp);
    // shader->col = glGetUniformLocation(shader->prog, "col");
    // shader->pos = glGetAttribLocation (shader->prog, "pos");

    // cleanup
    free(frag_text);
    free(vert_text);
}

static Shader* 
Create(char* name) {
    Shader* shader = malloc(sizeof(Shader));
	Init(shader, name);
    return shader;
}

static void
Release(Shader* shader) {
    glDeleteProgram(shader->prog);
    free(shader);
}

static void
Start(Shader* shader) {
    // SET SHADER
    glUseProgram(shader->prog);
}

static void
Stop(Shader* shader) {
	glUseProgram(0);
}

struct AShader AShader[1] = {{
	Create,
	Init,
	Release,
	Start,
	Stop,
}};

// -----------------------------------------------------------------

static void 
load_file(
    char*  filename, 
    char** buf) {

    long length = 0;
    FILE* fp = fopen (filename, "rb");
    
    if(fp) {
        fseek (fp, 0, SEEK_END);
        length = ftell(fp);
        fseek (fp, 0, SEEK_SET);
        *buf = malloc(length+1);
        if (*buf) {
            fread(*buf, 1, length, fp);
        }
        fclose (fp);
        (*buf)[length]=0;
    }
}

static void 
check_shader(GLuint sid) {
    GLint isCompiled = 0;
    glGetShaderiv(sid, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &maxLength);
        // The maxLength includes the NULL character
        GLchar error[maxLength];
        glGetShaderInfoLog(sid, maxLength, &maxLength, error);
        fprintf(stderr, "ERR: %s\n", error);

        // Provide the infolog in whatever manor you deem best.
        glDeleteShader(sid); // Don't leak the shader.
        return;
    }
}


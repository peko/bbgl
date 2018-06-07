
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "App.h"
#include "Gui.h"
#include "Scene.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

static void error_callback(int e, const char *d)
{printf("Error %d: %s\n", e, d);}

/* Platform */
static GLFWwindow *win;
int width = 0, height = 0;
Scene* scene;

static void onResize(GLFWwindow*, int, int);

static void 
Init() {

    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BBGL3", NULL, NULL);
    glfwMakeContextCurrent(win);
    gl3wInit();
    glfwSetWindowSizeCallback(win, onResize);
    glfwGetWindowSize(win, &width, &height);
     
    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    // glewExperimental = 1;
    // if (glewInit() != GLEW_OK) {
    //     fprintf(stderr, "Failed to setup GLEW\n");
    //     exit(1);
    // }
    
    scene = AScene->Create();
    AScene->Resize(scene, width,height);
    AGui->Init(win);
}


static void 
onResize(GLFWwindow* win, int width, int height) {
    AScene->Resize(scene, width, height);
}

static void 
Loop() {
    
    while (!glfwWindowShouldClose(win)) {
        /* Input */
        glfwPollEvents();
        AGui->Update();

        /* Draw */
        glfwGetWindowSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 0.0);

        AScene->Render(scene);
        AGui->Render();
        
        glfwSwapBuffers(win);
    }

    // cleanup
    AScene->Release(scene);
    AGui->Release();

    glfwTerminate();
}

struct AApp AApp[1] = {{
    Init,
    Loop
}};


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

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui/cimgui.h>
#include <imgui_impl_glfw_gl3.h>


#include "Gui.h"

struct ImGuiContext* ctx;
struct ImGuiIO* io; 

static void 
Init(GLFWwindow* win) {

    // IMGUI_CHECKVERSION();
    ctx = igCreateContext(NULL);
    io  = igGetIO();
    ImGui_ImplGlfwGL3_Init(win, true, NULL);

    // Setup style
    igStyleColorsDark(NULL);
}

static void
Update(){
    ImGui_ImplGlfwGL3_NewFrame();

    igBegin("Test", NULL, 0);
    igText("Test");
    igButton("Test",(struct ImVec2){0,0});
    igEnd();

	// Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. 
	// Here we just want to make the demo initial state a bit more friendly!
	igSetNextWindowPos((struct ImVec2){0,0}, ImGuiCond_FirstUseEver,(struct ImVec2){0,0} ); 
	igShowDemoWindow(NULL);
}

static void
Render(){
    igRender();
    ImGui_ImplGlfwGL3_RenderDrawData(igGetDrawData());
}

static void
Release(){
    ImGui_ImplGlfwGL3_Shutdown();
    igDestroyContext(ctx);
};

struct AGui AGui[1] = {{
	Init,
	Release,
	Update,
	Render,
}};



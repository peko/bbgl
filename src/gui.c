
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
#include <imgui/examples/opengl3_example/imgui_impl_glfw_gl3.h>

struct ImGuiContext* ctx;
struct ImGuiIO* io; 

void gui_init(GLFWwindow* win) {

    // IMGUI_CHECKVERSION();
    ctx = igCreateContext(NULL);
    io  = igGetIO();
    ImGui_ImplGlfwGL3_Init(win, true, NULL);

    // Setup style
    igStyleColorsDark(NULL);
}

void gui_update(){
     ImGui_ImplGlfwGL3_NewFrame();
     igBegin("Test", NULL, 0);
     // igBegin("Stream widget", NULL, 0);
     igText("Test");
     igButton("Test",(struct ImVec2){0,0});
     igEnd();
}

void gui_render(){
    igRender();
    ImGui_ImplGlfwGL3_RenderDrawData(igGetDrawData());
}

void gui_terminate(){
    ImGui_ImplGlfwGL3_Shutdown();
    igDestroyContext(ctx);
};



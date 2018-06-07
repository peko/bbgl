cmake_minimum_required(VERSION 3.6)

set(project_name bbgl)
project(${project_name})

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

#GLU
#pkg_search_module(GLU REQUIRED glu)

# NUKLEAR GUI
set(nuklear lib/nuklear)

set(cimgui lib/cimgui)
set(imgui_impl lib/imgui_gl3)
set(gl3w lib/gl3w)
set(klib lib/klib)
set(linmath lib/linmath/)

# library search path
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig")
set(ENV{LD_LIBRARY_PATH} "ENV{LD_LIBRARY_PATH}:/usr/local/lib")

# build dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -g")

# Include dirs
include_directories(
	src
    ${cimgui} ${cimgui}/imgui ${imgui_impl}
	${nuklear} ${nuklear}/demo/glfw_opengl3
    ${gl3w}
    ${klib}
    ${linmath})

file(GLOB cimgui_files "${cimgui}/cimgui/*.cpp" "${cimgui}/imgui/*.cpp")
add_library(cimgui ${cimgui_files})
add_library(imgui_impl ${imgui_impl}/imgui_impl_glfw_gl3.cpp)

file(GLOB source_files "src/*.c")
file(GLOB gl3w_files "${gl3w}/GL/*.c")

add_executable(
	${project_name} 
	${source_files}
	${gl3w_files})

target_link_libraries(
	${project_name}
    ${GLFW_LIBRARIES}
	m GL dl cimgui imgui_impl)



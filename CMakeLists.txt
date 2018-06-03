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

# GL3W
set(gl3w lib/gl3w)

# klib
set(klib lib/klib)

# library search path
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig")
set(ENV{LD_LIBRARY_PATH} "ENV{LD_LIBRARY_PATH}:/usr/local/lib")

# build dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -g")

# Include dirs
include_directories(
	src 
	${nuklear} ${nuklear}/demo/glfw_opengl3
    ${gl3w}
    ${klib})

file(GLOB source_files "src/*.c")
file(GLOB gl3w_files "${gl3w}/GL/*.c")

add_executable(
	${project_name} 
	${source_files}
	${gl3w_files})

target_link_libraries(
	${project_name}
    ${GLFW_LIBRARIES}
	m GL dl)



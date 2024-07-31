cmake_minimum_required(VERSION 3.22)

project(Engine)

# Locate all source files in the src directory
file(GLOB SRC_FILES src/*.cpp src/*.c)

add_executable(Engine main.cpp ${SRC_FILES})


find_package(OpenGL REQUIRED)

add_subdirectory(libs/glfw)

target_link_libraries(Engine PRIVATE glfw ${OPENGL_gl_LIBRARY})

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
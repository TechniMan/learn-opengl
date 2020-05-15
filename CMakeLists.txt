cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 17)
project(learn-opengl)

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "src/glad.c")

set(GCC_GL_COMPILE_FLAGS "-lglfw3 -lX11 -lpthread -lXrandr -lXi -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_GL_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_GL_COMPILE_FLAGS}")

add_executable(learn-opengl ${SOURCES})

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(learn-opengl glfw)

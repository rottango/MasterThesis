cmake_minimum_required(VERSION 3.16)

project(animationLoopProject VERSION 1.0)


find_package(OpenCV REQUIRED)

add_executable(
    animationLoop
    src/calculate.cpp
    src/draw_on_screen.cpp
    src/main.cpp
    src/node_class.cpp
    src/render_loop.cpp
)


###Add libs (relative to cmakelists.txt):

target_include_directories(animationLoop PRIVATE include)

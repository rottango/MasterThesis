cmake_minimum_required(VERSION 3.16)
 
 project(animationLoopProject VERSION 1.0)
 
 
 find_package(OpenCV REQUIRED)
 
 #create a source variable with a link to all cpp files to compile
 
 set(
 SOURCES
 src/calculate.cpp
 src/draw_class.cpp
 src/main.cpp
 src/node_class.cpp
 src/render_loop.cpp
 )
 
 
 add_executable(${PROJECT_NAME} ${SOURCES})
 
 
 ###Add libs (relative to cmakelists.txt):
 
 
 target_include_directories(
 animationLoopProject
 PRIVATE
 ${PROJECT_SOURCE_DIR}/include 
 ${OpenCV_INCLUDE_DIRS}
 )
 
 target_link_libraries(
 animationLoopProject
 PRIVATE 
 ${OpenCV_LIBS}
 )
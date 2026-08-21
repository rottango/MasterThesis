cmake_minimum_required(VERSION 3.16)
 
project(animationLoopProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

 
 find_package(OpenCV REQUIRED)
 find_package(spdlog CONFIG REQUIRED)
 
 #create a source variable with a link to all cpp files to compile
 
 set(
 SOURCES
 src/application_node.cpp
 src/color_palet_struct.cpp
 src/draw_class.cpp
 src/edge_class.cpp
 src/graph_class.cpp
 src/group_class.cpp
 src/main.cpp
 src/node_class.cpp
 src/grouping_manager_class.cpp
 src/reusable_calculations.cpp
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
 spdlog::spdlog
 )
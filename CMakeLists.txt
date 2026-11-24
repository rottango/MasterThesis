cmake_minimum_required(VERSION 3.16)
 
project(animationLoopProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

 
 find_package(OpenCV REQUIRED)
 find_package(spdlog CONFIG REQUIRED)
 find_package(PkgConfig REQUIRED)
 #create a source variable with a link to all cpp files to compile
 
 pkg_check_modules(LIBSERIALPORT REQUIRED IMPORTED_TARGET libserialport)

 set(
 SOURCES
 src/application/application_class.cpp
 src/colors/color_palet_struct.cpp
 src/visualization/draw_class.cpp
 src/visualization/edge_class.cpp
 src/visualization/graph_class.cpp
 src/visualization/group_class.cpp
 src/application/main.cpp
 src/visualization/node_class.cpp
 src/visualization/grouping_manager_class.cpp
 src/calculations/reusable_calculations.cpp
 src/uwb/libserialport_sequence.cpp
 )
 
 
 add_executable(${PROJECT_NAME} ${SOURCES})
 
 
 ###Add libs (relative to cmakelists.txt):
 
 
 target_include_directories(
 animationLoopProject
 PRIVATE
 ${PROJECT_SOURCE_DIR}/include 
 ${PROJECT_SOURCE_DIR}/include/uwb
 ${PROJECT_SOURCE_DIR}/include/visualization
 ${PROJECT_SOURCE_DIR}/include/application
 ${PROJECT_SOURCE_DIR}/include/calculations
 ${PROJECT_SOURCE_DIR}/include/colors
 ${OpenCV_INCLUDE_DIRS}
 )
 
 target_link_libraries(
 animationLoopProject
 PRIVATE 
 ${OpenCV_LIBS}
 spdlog::spdlog
 PkgConfig::LIBSERIALPORT
 )
#include <application_node.hpp>
#include <spdlog/spdlog.h>

/*

==
Im assuming that my calculations are with cartesian coordinates, so i have to add
a middleman funciton ,taht calculates all cordinates to and from cartesian and opencv
==
*/

int main()
{
    spdlog::info("Hello, {}!", "World");

    Application app;
    app.start();

    return 0;
}
#include <application_class.hpp>
#include <spdlog/spdlog.h>

/*

==
Im assuming that my calculations are with cartesian coordinates, so i have to add
a middleman funciton ,taht calculates all cordinates to and from cartesian and opencv
==
*/

int main()
{
    spdlog::info("Starting application");

    Application app;
    app.start();

    return 0;
}
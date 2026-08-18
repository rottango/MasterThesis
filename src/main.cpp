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
    // Taken from:
    // https://stackoverflow.com/questions/2031163/when-to-use-the-different-log-levels
    // info - Generally useful information to log (service start/stop, configuration assumptions, etc). Info I want to always have available but usually don't care about under normal circumstances. This is my out-of-the-box config level.
    // error - Any error which is fatal to the operation, but not the service or application (can't open a required file, missing data, etc.). These errors will force user (administrator, or direct user) intervention. These are usually reserved (in my apps) for incorrect connection strings, missing services, etc.
    // warn - Anything that can potentially cause application oddities, but for which I am automatically recovering. (Such as switching from a primary to backup server, retrying an operation, missing secondary data, etc.)
    // critical - Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss). I reserve these only for the most heinous errors and situations where there is guaranteed to have been data corruption or loss.
    // debug - Information that is diagnostically helpful to people more than just developers (IT, sysadmins, etc.).

    spdlog::info("Project ran");

    Application app;
    app.start();

    return 0;
}
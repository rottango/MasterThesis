#include <application_class.hpp>
#include <spdlog/spdlog.h>

int main()
{
    spdlog::info("Project ran");

    Application app;
    app.start();

    return 0;
}
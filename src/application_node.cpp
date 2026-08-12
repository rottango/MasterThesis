#include <application_node.hpp>

Application::Application()
{
}

void Application::run()
{
}

bool Application::initialize(int screen_width,
                             int screen_height)
{
    createNamedWindow("Visualization", cv::WindowFlags::WINDOW_NORMAL);
    cv::Size windowSize{screen_width, screen_height};
    int makeTypeFlag = CV_8UC3;
    cv::Scalar backgroundColor{87, 80, 73};
    cv::Mat img_temp_{screen_height, screen_width, makeTypeFlag, backgroundColor};
    img_ = img_temp_;

    running_ = true;

    return true;
}

void Application::clearFrame()
{
}

void Application::update()
{
}

void Application::render()
{
}

void Application::presentFrame()
{
}

void Application::processInput()
{
}

bool Application::shutdown()
{
}

void Application::createNamedWindow(std::string namedWindowName, int flag)
{
    cv::namedWindow(namedWindowName, flag);
    cv::resizeWindow(namedWindowName, cv::Size(screen_width_, screen_height_));
}
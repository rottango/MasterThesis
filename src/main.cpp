#include <chrono>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <thread>

#include <calculate.hpp>
#include <draw_on_screen.hpp>
#include <node_class.hpp>
#include <render_loop.hpp>

#define PI 3.14159265

int main()
{
    Node ugv1(0, 0, 0, 0, 0, 5, 40, 45);
    Node ugv2(0, 0, 0, 0, 0, 5, 40, 45);

    const std::string windowName = "Visualization";
    cv::namedWindow(windowName, cv::WindowFlags::WINDOW_NORMAL);
    cv::resizeWindow(windowName, cv::Size(1920, 1080));
    cv::Mat img(1080, 1920, CV_8UC3, cv::Scalar(255, 255, 255));

    while (true)
    {
        cv::Mat imgCop = img.clone();
        renderLoop(imgCop, windowName, ugv1, ugv2);
    }

    return 0;
}
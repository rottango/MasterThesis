#include <chrono>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <thread>

#include <calculate.hpp>
#include <color_palet_struct.hpp>
#include <draw_class.hpp>
#include <extern_variables.hpp>
#include <node_class.hpp>
#include <render_loop.hpp>

#define PI 3.14159265

int main()
{
    screen_height_pixels = 1080;
    screen_width_pixels = 1920;

    std::string windowName = "Visualization";
    cv::WindowFlags flag = cv::WindowFlags::WINDOW_NORMAL;

    std::cout << opencv_screen_center.x << "dasdasd " << opencv_screen_center.y << "\n";
    cv::Size windowSize{screen_width_pixels, screen_height_pixels};
    int makeTypeFlag = CV_8UC3;
    cv::Scalar backgroundColor{87, 80, 73};
    cv::Point2d ugv_location = openCVPointToCartesianPoint(cv::Point2d(0, 0), opencv_screen_center);

    Node ugv1(cartesianPointToOpenCVPoint(cv::Point2d(100, 100), opencv_screen_center), 0, 0, 5, 40, 45, ugv1ColorPalet);
    Node ugv2(cartesianPointToOpenCVPoint(cv::Point2d(-100, -100), opencv_screen_center), 0, 0, 5, 40, 45, ugv2ColorPalet);

    Draw draw1(windowName,
               flag,
               windowSize,
               screen_height_pixels,
               screen_width_pixels,
               makeTypeFlag,
               backgroundColor);

    while (true)
    {
        cv::Mat imgCop = draw1.img.clone();
        renderLoop(imgCop, windowName, ugv1, ugv2, draw1);
    }

    return 0;
}
#include <chrono>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <thread>

#include <calculate.hpp>
#include <color_palet_struct.hpp>
#include <draw_class.hpp>
#include <node_class.hpp>
#include <render_loop.hpp>

#define PI 3.14159265

int main()
{
    std::string windowName = "Visualization";
    cv::WindowFlags flag = cv::WindowFlags::WINDOW_NORMAL;
    int rows = 1080;
    int cols = 1920;
    int middle_x = cols / 2;
    int middle_y = rows / 2;
    cv::Size windowSize{cols, rows};
    int makeTypeFlag = CV_8UC3;
    cv::Scalar backgroundColor{87, 80, 73};
    cv::Point2d ugv_location = openCVPointToCartesianPoint(cv::Point2d(0, 0), cv::Point2d(middle_x, middle_y));

    Node ugv1(cartesianPointToOpenCVPoint(cv::Point2d(100, 100), cv::Point2d(middle_x, middle_y)), 0, 0, 5, 40, 45, ugv1ColorPalet);
    Node ugv2(cartesianPointToOpenCVPoint(cv::Point2d(-100, -100), cv::Point2d(middle_x, middle_y)), 0, 0, 5, 40, 45, ugv2ColorPalet);

    Draw draw1(windowName,
               flag,
               windowSize,
               rows,
               cols,
               makeTypeFlag,
               backgroundColor);

    while (true)
    {
        cv::Mat imgCop = draw1.img.clone();
        renderLoop(imgCop, windowName, ugv1, ugv2, draw1);
    }

    return 0;
}
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

void calculate()
{
}

double calculateDistanceBetweenPoints(double x1, double x2, double y1, double y2)
{
    double square_difference_x = (x2 - x1) * (x2 - x1);
    double square_difference_y = (y2 - y1) * (y2 - y1);
    double sum = square_difference_x + square_difference_y;
    double distance = sqrt(sum);
    return distance;
}

void testLocalization(cv::Mat &img, Node ugv1, Node ugv2)
{
}

int main()
{
    Node ugv1(0, 0, 0, 5, 40, 45);
    Node ugv2(0, 0, 0, 5, 40, 45);

    const std::string windowName = "w";
    cv::namedWindow(windowName, cv::WindowFlags::WINDOW_FULLSCREEN);
    cv::resizeWindow(windowName, cv::Size(1920, 1080));
    cv::Mat img(1080, 1920, CV_8UC3, cv::Scalar(255, 255, 255));

    while (true)
    {
        cv::Mat imgCop = img.clone();
        renderLoop(imgCop, windowName, ugv1, ugv2);
    }

    return 0;
}
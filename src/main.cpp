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
    Node ugv1(500, 500, 0, 0, 5, 40, 45, ugv1ColorPalet);
    Node ugv2(1000, 500, 0, 0, 5, 40, 45, ugv2ColorPalet);

    std::string windowName = "Visualization";
    cv::WindowFlags flag = cv::WindowFlags::WINDOW_NORMAL;
    int rows = 1080;
    int cols = 1920;
    cv::Size windowSize{cols, rows};
    int makeTypeFlag = CV_8UC3;
    cv::Scalar backgroundColor{255, 255, 255};

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
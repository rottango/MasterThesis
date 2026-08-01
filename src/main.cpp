#include <chrono>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <thread>
#include <vector>

#include <application_node.hpp>
#include <calculate.hpp>
#include <color_palet_struct.hpp>
#include <define.hpp>
#include <draw_class.hpp>
#include <node_class.hpp>
#include <render_loop.hpp>

#define PI 3.14159265

int main()
{
    Application application;

    std::vector<Node> node_vector;
    std::string windowName = "Visualization";
    cv::WindowFlags flag = cv::WindowFlags::WINDOW_NORMAL;

    cv::Size windowSize{1920, 1080};
    int makeTypeFlag = CV_8UC3;
    cv::Scalar backgroundColor{87, 80, 73};

    Node ugv1(0, cv::Point2d(0, 0), 0, 5, 40, 45, ugv1ColorPalet);
    Node ugv2(1, cv::Point2d(-100, -100), 0, 5, 40, 45, ugv2ColorPalet);

    node_vector.push_back(ugv1);
    node_vector.push_back(ugv2);

    Draw draw1(windowName,
               flag,
               windowSize,
               1080,
               1920,
               makeTypeFlag,
               backgroundColor);

    while (true)
    {
        cv::Mat imgCop = draw1.img.clone();
        renderLoop(imgCop, windowName, node_vector, draw1);
    }

    return 0;
}
#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

struct colorPalet
{
    cv::Scalar vehicle_color;
    cv::Scalar inner__color;
    cv::Scalar measurment_error_color;
    cv::Scalar observer_line_color;
    cv::Scalar text_color;

    int thickness;
    int lineType;
    int shift;
};

extern cv::Scalar colors[];

colorPalet generateColorPalet(int &color_positon);

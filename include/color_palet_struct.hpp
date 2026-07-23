#pragma once

#include <opencv2/opencv.hpp>

struct colorPalet
{
    cv::Scalar vehicle_color;
    cv::Scalar inner_color;
    cv::Scalar measurment_error_color;
    cv::Scalar observer_line_color;
    cv::Scalar text_color;
};

extern colorPalet ugv1ColorPalet;
extern colorPalet ugv2ColorPalet;
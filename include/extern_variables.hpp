#pragma once

#include <opencv2/opencv.hpp>

extern int screen_width_pixels;
extern int screen_height_pixels;
extern cv::Point2d opencv_screen_center;

void setExternValues(int screen_width_pixels,
                     int screen_height_pixels,
                     cv::Point2d opencv_screen_center);
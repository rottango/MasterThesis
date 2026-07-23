#pragma once

#include <opencv2/opencv.hpp>

#define screen_x_pixels 1920
#define screen_y_pixels 1080

cv::Point2d opencv_screen_center(screen_x_pixels / 2, screen_y_pixels / 2);
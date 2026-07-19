#pragma once

#define PI 3.14159265
#include <opencv2/opencv.hpp>

void drawTextOnScreen(cv::Mat &img, Node ugv1, Node ugv2);

void draw(cv::Mat &img, Node ugv1, Node ugv2);

void drawConnectingLine(cv::Mat &img, Node ugv1, Node ugv2);

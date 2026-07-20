#pragma once

#include <node_class.hpp>
#include <opencv2/opencv.hpp>

void drawTextOnScreen(cv::Mat &img, Node ugv1, Node ugv2);

void drawAxis(cv::Mat &img, Node ugv);

void draw(cv::Mat &img, Node ugv1, Node ugv2);

void drawConnectingLine(cv::Mat &img, Node ugv1, Node ugv2);

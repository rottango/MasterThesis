#pragma once

#include <node_class.hpp>
#include <opencv2/opencv.hpp>

class Draw
{
public:
    std::string distance_output;
    std::string observer_pos_output;
    std::string target_pos_output;
    std::string measurment_error_output;
    std::string angle_output_atan2;

    cv::Point2d middleOfAngleLine;
    cv::Point2d centerOfScreen;
    cv::Mat img;

    Draw(std::string windowNameme,
         cv::WindowFlags flag,
         cv::Size windowSize,
         int rows,
         int cols,
         int makeTypeFlag,
         cv::Scalar backgroundColor);

    void drawTextOnScreen(cv::Mat &img, Node ugv1, Node ugv2);

    void drawAxis(cv::Mat &img, Node ugv);

    void drawConnectingLine(cv::Mat &img, Node ugv1, Node ugv2);

    void drawFrame(cv::Mat &img, Node ugv1, Node ugv2);

    void generateText(Node observer, Node target);
};
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

    void DrawTextOnScreen(cv::Mat &img, std::vector<Node> node_list);

    void DrawAxis(cv::Mat &img, Node ugv);

    void drawConnectingLine(cv::Mat &img, Node observer, Node target);

    void drawFrame(cv::Mat &img, std::vector<Node> node_list);

    void generateText(std::vector<Node> node_list);

    void drawElipse(cv::Mat &img, Node observer);

    void drawNode(cv::Mat img, Node ugv);
};
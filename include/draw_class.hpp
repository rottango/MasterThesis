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

    cv::Point2d middle_of_angle_line;
    cv::Point2d center_of_screen;
    cv::Mat image;

    Draw(std::string windowNameme,
         cv::WindowFlags flag,
         cv::Size windowSize,
         int rows,
         int cols,
         int makeTypeFlag,
         cv::Scalar backgroundColor);

    void drawTextOnScreen(cv::Mat &image, std::vector<Node> node_list);

    void drawAxis(cv::Mat &image, Node ugv);

    void drawConnectingLine(cv::Mat &image, Node observer, Node target);

    void drawFrame(cv::Mat &image, std::vector<Node> node_list);

    void generateText(std::vector<Node> node_list);

    void drawElipse(cv::Mat &image, Node observer);

    void drawNode(cv::Mat image, Node ugv);
};
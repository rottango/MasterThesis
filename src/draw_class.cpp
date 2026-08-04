
#include <draw_class.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

Draw::Draw(std::string windowName,
           cv::WindowFlags flag,
           cv::Size windowSize,
           int rows,
           int cols,
           int makeTypeFlag,
           cv::Scalar backgroundColor) : image{rows,
                                               cols,
                                               makeTypeFlag,
                                               backgroundColor}
{
}

void Draw::drawElipse(cv::Mat &image, Node observer)
{
}

void Draw::generateText(std::vector<Node> node_list)
{
}

void Draw::drawTextOnScreen(cv::Mat &image, std::vector<Node> node_list)
{
}

void Draw::drawAxis(cv::Mat &image, Node node)
{
}

void Draw::drawNode(cv::Mat image, Node node)
{
}

void Draw::drawFrame(cv::Mat &image, std::vector<Node> node_list)
{
}

void Draw::drawConnectingLine(cv::Mat &image, Node observer, Node target)
{
}

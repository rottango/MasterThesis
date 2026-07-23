#pragma once

#include <calculate.hpp>
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
           cv::Scalar backgroundColor) : img{rows,
                                             cols,
                                             makeTypeFlag,
                                             backgroundColor}
{
    cv::namedWindow(windowName, flag);
    cv::resizeWindow(windowName, windowSize);

    this->centerOfScreen = cv::Point2d(cols / 2, rows / 2);
}

void Draw::generateText(Node observer, Node target)
{
    this->distance_output = "Distance: " + std::to_string(calculateDistanceBetweenPoints(observer.opencv_x_y_point.x, target.opencv_x_y_point.x, observer.opencv_x_y_point.y, target.opencv_x_y_point.y));
    this->observer_pos_output = "observer (x,y) = (" + std::to_string(observer.opencv_x_y_point.x) + "," + std::to_string(observer.opencv_x_y_point.y) + ")";
    this->target_pos_output = "target (x,y) = (" + std::to_string(target.opencv_x_y_point.x) + "," + std::to_string(target.opencv_x_y_point.y) + ")";
    this->measurment_error_output = "+-" + std::to_string(observer.getMeasurmentError() + target.getMeasurmentError()) + "[pixels]";

    double remainder = std::fmod(calculateAngle(observer, target) + observer.theta_rotation, 360.00f);
    if (remainder < 0)
    {
        remainder += 360;
    }
    this->angle_output_atan2 = "angle atan2: = " + std::to_string(remainder);
}

void Draw::drawTextOnScreen(cv::Mat &img, Node observer, Node target)
{
    cv::putText(img,
                this->distance_output + this->measurment_error_output,
                this->centerOfScreen,
                cv::HersheyFonts::FONT_HERSHEY_PLAIN, 2,
                observer.ugvColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                this->observer_pos_output,
                cv::Point2d(this->centerOfScreen.x, this->centerOfScreen.y + 25),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                observer.ugvColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                this->target_pos_output,
                cv::Point2d(this->centerOfScreen.x, this->centerOfScreen.y + 50),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                target.ugvColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                this->angle_output_atan2,
                this->middleOfAngleLine,
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                0.75,
                observer.ugvColorPalet.text_color,
                1,
                7);
}

void Draw::drawAxis(cv::Mat &img, Node ugv)
{
    cv::arrowedLine(img, cv::Point2d(ugv.opencv_x_y_point.x, ugv.opencv_x_y_point.y), cv::Point2d(ugv.x_x_axis_point, ugv.y_x_axis_point), cv::Scalar(0, 0, 255), 5); // x axis red
    cv::arrowedLine(img, cv::Point2d(ugv.opencv_x_y_point.x, ugv.opencv_x_y_point.y), cv::Point2d(ugv.x_y_axis_point, ugv.y_y_axis_point), cv::Scalar(255, 0, 0), 5); // y axis blue
}

void Draw::drawFrame(cv::Mat &img, Node ugv1, Node ugv2)
{
    ugv1.drawNode(img);
    ugv2.drawNode(img);
    drawConnectingLine(img, ugv1, ugv2);
    generateText(ugv1, ugv2);
    drawTextOnScreen(img, ugv1, ugv2);
    drawAxis(img, ugv1);
    drawAxis(img, ugv2);
}

void Draw::drawConnectingLine(cv::Mat &img, Node observer, Node target)
{
    cv::line(img,
             cv::Point2d(observer.opencv_x_y_point.x, observer.opencv_x_y_point.y),
             cv::Point2d(target.opencv_x_y_point.x, target.opencv_x_y_point.y),
             observer.ugvColorPalet.observer_line_color,
             2,
             cv::LineTypes::LINE_4,
             0);
    this->middleOfAngleLine = cv::Point2d((observer.opencv_x_y_point.x + target.opencv_x_y_point.x) / 2, (observer.opencv_x_y_point.y + target.opencv_x_y_point.y) / 2);
}


#include <calculate.hpp>
#include <define.hpp>
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
}

void Draw::drawElipse(cv::Mat &img, Node observer)
{
    double angle = 0;
    double start_angle = 0;
    double end_angle = observer.angle_output_atan2_to_target;
    cv::Scalar color = observer.ugvColorPalet.text_color;
    bool invert = 0;

    end_angle *= -1;

    start_angle = observer.theta_rotation;

    cv::ellipse(img,                               // cv::InputOutputArray img,
                observer.opencv_x_y_point,         // cv::Point center
                cv::Size2d(100, 100),              // cv::Size axes
                angle,                             // double angle STAYS 0, then its like i want it to be
                start_angle,                       // double startAngle
                end_angle,                         // double endAngle
                observer.ugvColorPalet.text_color, // const cv::Scalar &color
                1,                                 // int thickness
                8,                                 // int lineType = 8
                0);                                // int shift = 0
    std::cout << "end_angle: " << end_angle << "\n";
}

void Draw::generateText(Node &observer, Node target)
{
    this->distance_output = "Distance: " + std::to_string(calculateDistanceBetweenPoints(observer.opencv_x_y_point.x, target.opencv_x_y_point.x, observer.opencv_x_y_point.y, target.opencv_x_y_point.y));
    this->observer_pos_output = "observer (x,y) = (" + std::to_string(observer.opencv_x_y_point.x) + "," + std::to_string(observer.opencv_x_y_point.y) + ")";
    this->target_pos_output = "target (x,y) = (" + std::to_string(target.opencv_x_y_point.x) + "," + std::to_string(target.opencv_x_y_point.y) + ")";
    this->measurment_error_output = "+-" + std::to_string(observer.getMeasurmentError() + target.getMeasurmentError()) + "[pixels]";

    observer.angle_output_atan2_to_target = cartesianCalculateAngle(observer, target);
    this->angle_output_atan2 = "angle atan2: = " + std::to_string(observer.angle_output_atan2_to_target);
}

void Draw::openCVDrawTextOnScreen(cv::Mat &img, Node observer, Node target)
{
    cv::putText(img,
                this->distance_output + this->measurment_error_output,
                cv::Point2d(0, 1080 - 75),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN, 2,
                observer.ugvColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                this->observer_pos_output,
                cv::Point2d(0, 1080 - 50),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                observer.ugvColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                this->target_pos_output,
                cv::Point2d(0, 1080 - 25),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                target.ugvColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                angle_output_atan2,
                this->middleOfAngleLine,
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                0.75,
                observer.ugvColorPalet.text_color,
                1,
                7);
}

void Draw::openCVDrawAxis(cv::Mat &img, Node ugv)
{
    cv::arrowedLine(img, ugv.opencv_x_y_point, ugv.opencv_x_axis_point, cv::Scalar(0, 0, 255), 5); // x axis red
    cv::arrowedLine(img, ugv.opencv_x_y_point, ugv.opencv_y_axis_point, cv::Scalar(255, 0, 0), 5); // y axis blue
}

void Draw::drawFrame(cv::Mat &img, Node ugv1, Node ugv2)
{
    ugv1.drawNode(img);
    ugv2.drawNode(img);
    drawConnectingLine(img, ugv1, ugv2);
    generateText(ugv1, ugv2);
    openCVDrawTextOnScreen(img, ugv1, ugv2);
    openCVDrawAxis(img, ugv1);
    openCVDrawAxis(img, ugv2);
    drawElipse(img, ugv1);
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

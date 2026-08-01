
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
    double start_angle = -observer.theta_rotation_degrees;
    double end_angle = start_angle - observer.angle_output_atan2_to_target;
    cv::Scalar color = observer.nodeColorPalet.text_color;
    bool invert = 0;

    cv::ellipse(img,                                                       // cv::InputOutputArray img,
                cartesianPointToOpenCVPoint(observer.cartesian_x_y_point), // cv::Point center
                cv::Size2d(100, 100),                                      // cv::Size axes
                angle,                                                     // double angle STAYS 0, then its like i want it to be
                start_angle,                                               // double startAngle
                end_angle,                                                 // double endAngle
                observer.nodeColorPalet.text_color,                        // const cv::Scalar &color
                1,                                                         // int thickness
                8,                                                         // int lineType = 8
                0);                                                        // int shift = 0
    std::cout << "end_angle: " << end_angle << "\n";
}

void Draw::generateText(std::vector<Node> node_list)
{
    this->distance_output = "Distance: " + std::to_string(calculateDistanceBetweenPoints(node_list.at(0).cartesian_x_y_point.x, node_list.at(1).cartesian_x_y_point.x, node_list.at(0).cartesian_x_y_point.y, node_list.at(1).cartesian_x_y_point.y));
    this->observer_pos_output = "observer (x,y) = (" + std::to_string(node_list.at(0).cartesian_x_y_point.x) + "," + std::to_string(node_list.at(0).cartesian_x_y_point.y) + ")";
    this->target_pos_output = "target (x,y) = (" + std::to_string(node_list.at(1).cartesian_x_y_point.x) + "," + std::to_string(node_list.at(1).cartesian_x_y_point.y) + ")";
    this->measurment_error_output = "+-" + std::to_string(node_list.at(0).getMeasurmentError() + node_list.at(1).getMeasurmentError()) + "[pixels]";

    node_list.at(0).angle_output_atan2_to_target = changePosition(node_list.at(0), node_list.at(1));
    this->angle_output_atan2 = "angle atan2: = " + std::to_string(node_list.at(0).angle_output_atan2_to_target);
}

void Draw::DrawTextOnScreen(cv::Mat &img, std::vector<Node> node_list)
{
    cv::putText(img,
                this->distance_output + this->measurment_error_output,
                cv::Point2d(0, 1080 - 75),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN, 2,
                node_list.at(0).nodeColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                this->observer_pos_output,
                cv::Point2d(0, 1080 - 50),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                node_list.at(0).nodeColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                this->target_pos_output,
                cv::Point2d(0, 1080 - 25),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                node_list.at(1).nodeColorPalet.text_color,
                1,
                7);
    cv::putText(img,
                angle_output_atan2,
                this->middleOfAngleLine,
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                0.75,
                node_list.at(0).nodeColorPalet.text_color,
                1,
                7);
}

void Draw::DrawAxis(cv::Mat &img, Node node)
{
    cv::Point2d temp_opencv_point_x_y = cartesianPointToOpenCVPoint(node.cartesian_x_y_point);
    cv::Point2d temp_opencv_x_axis_point = cartesianPointToOpenCVPoint(node.cartesian_x_axis_point);
    cv::Point2d temp_opencv_y_axis_point = cartesianPointToOpenCVPoint(node.cartesian_y_axis_point);

    cv::arrowedLine(img,
                    temp_opencv_point_x_y,
                    temp_opencv_x_axis_point,
                    cv::Scalar(0, 0, 255),
                    5); // x axis red
    cv::arrowedLine(img,
                    temp_opencv_point_x_y,
                    temp_opencv_y_axis_point,
                    cv::Scalar(255, 0, 0),
                    5); // y axis blue
}

void Draw::drawNode(cv::Mat img, Node node)
{
    cv::Point2d temp_opencv_point_x_y = cartesianPointToOpenCVPoint(node.cartesian_x_y_point);
    cv::circle(img, temp_opencv_point_x_y, node.getVehicleSize(), node.nodeColorPalet.vehicle_color, cv::FILLED, 8, 0);
    cv::circle(img, temp_opencv_point_x_y, node.getinner_(), node.nodeColorPalet.inner__color, 2, 8, 0);
    cv::circle(img, temp_opencv_point_x_y, node.getMeasurmentError(), node.nodeColorPalet.measurment_error_color, 2, 8, 0);
}

void Draw::drawFrame(cv::Mat &img, std::vector<Node> node_list)
{
    drawNode(img, node_list.at(0));
    drawNode(img, node_list.at(1));
    drawConnectingLine(img, node_list.at(0), node_list.at(1));
    generateText(node_list);
    openCVDrawTextOnScreen(img, node_list);
    openCVDrawAxis(img, node_list.at(0));
    openCVDrawAxis(img, node_list.at(1));
    drawElipse(img, node_list.at(0));
}

void Draw::drawConnectingLine(cv::Mat &img, Node observer, Node target)
{
    cv::Point2d temp_observer_cartesian_x_y_point = cartesianPointToOpenCVPoint(observer.cartesian_x_y_point);
    cv::Point2d temp_target_cartesian_x_y_point = cartesianPointToOpenCVPoint(target.cartesian_x_y_point);

    cv::line(img,
             temp_observer_cartesian_x_y_point,
             temp_target_cartesian_x_y_point,
             observer.nodeColorPalet.observer_line_color,
             2,
             cv::LineTypes::LINE_4,
             0);
    this->middleOfAngleLine = cv::Point2d((temp_observer_cartesian_x_y_point.x + temp_target_cartesian_x_y_point.x) / 2,
                                          (temp_observer_cartesian_x_y_point.y + temp_target_cartesian_x_y_point.y) / 2);
}

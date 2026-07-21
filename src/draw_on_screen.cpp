#include <calculate.hpp>
#include <draw_on_screen.hpp>
#include <node_class.hpp>

void drawTextOnScreen(cv::Mat &img, Node observer, Node target)
{
    std::string distance_output = "Distance: " + std::to_string(calculateDistanceBetweenPoints(observer.x_position, target.x_position, observer.y_position, target.y_position));
    std::string observer_pos_output = "observer (x,y) = (" + std::to_string(observer.x_position) + "," + std::to_string(observer.y_position) + ")";
    std::string target_pos_output = "target (x,y) = (" + std::to_string(target.x_position) + "," + std::to_string(target.y_position) + ")";
    std::string measurment_error_output = "+-" + std::to_string(observer.getMeasurmentError() + target.getMeasurmentError()) + "[pixels]";
    // double result = atan((target.y_position - observer.y_position) / (target.x_position - observer.x_position)) * 180 / PI;
    double resultarctan2 = calculateAngle(observer, target);
    // std::string angle_output = "angle: = " + std::to_string(result);
    std::string angle_output_atan2 = "angle atan2: = " + std::to_string(resultarctan2);

    cv::putText(img,
                distance_output + measurment_error_output,
                cv::Point2d(img.rows / 2, img.cols / 2),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN, 2,
                cv::Scalar(127, 127, 127),
                1,
                7);
    cv::putText(img,
                observer_pos_output,
                cv::Point2d(img.rows / 2, (img.cols / 2) + 25),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                cv::Scalar(127, 127, 127),
                1,
                7);
    cv::putText(img,
                target_pos_output,
                cv::Point2d(img.rows / 2, (img.cols / 2) + 50),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                cv::Scalar(127, 127, 127),
                1,
                7);
    // cv::putText(img,
    //             angle_output,
    //             cv::Point2d(img.rows / 2, (img.cols / 2) - 75),
    //             cv::HersheyFonts::FONT_HERSHEY_PLAIN,
    //             2,
    //             cv::Scalar(127, 127, 127),
    //             1,
    //             7);
    cv::putText(img,
                angle_output_atan2,
                cv::Point2d(img.rows / 2, (img.cols / 2) - 100),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                0.75,
                cv::Scalar(127, 127, 127),
                1,
                7);
}

void drawAxis(cv::Mat &img, Node ugv)
{
    cv::arrowedLine(img, cv::Point2d(ugv.x_position, ugv.y_position), cv::Point2d(ugv.x_x_axis_point, ugv.y_x_axis_point), cv::Scalar(0, 0, 255), 5); // x axis red
    cv::arrowedLine(img, cv::Point2d(ugv.x_position, ugv.y_position), cv::Point2d(ugv.x_y_axis_point, ugv.y_y_axis_point), cv::Scalar(255, 0, 0), 5); // y axis blue
}

void draw(cv::Mat &img, Node ugv1, Node ugv2)
{
    ugv1.drawNode(img);
    ugv2.drawNode(img);
    drawConnectingLine(img, ugv1, ugv2);
    drawTextOnScreen(img, ugv1, ugv2);
    drawAxis(img, ugv1);
    drawAxis(img, ugv2);
}

void drawConnectingLine(cv::Mat &img, Node ugv1, Node ugv2)
{
    cv::line(img,
             cv::Point2d(ugv1.x_position, ugv1.y_position),
             cv::Point2d(ugv2.x_position, ugv2.y_position),
             cv::Scalar(0, 0, 0),
             2,
             cv::LineTypes::LINE_4,
             0);
}
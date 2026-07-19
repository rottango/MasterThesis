#include <calculate.hpp>
#include <draw_on_screen.hpp>
#include <node_class.hpp>

void drawTextOnScreen(cv::Mat &img, Node ugv1, Node ugv2)
{
    std::string distance_output = "Distance: " + std::to_string(calculateDistanceBetweenPoints(ugv1.x_position, ugv2.x_position, ugv1.y_position, ugv2.y_position));
    std::string ugv1_pos_output = "ugv1 (x,y) = (" + std::to_string(ugv1.x_position) + "," + std::to_string(ugv1.y_position) + ")";
    std::string ugv2_pos_output = "ugv2 (x,y) = (" + std::to_string(ugv2.x_position) + "," + std::to_string(ugv2.y_position) + ")";
    std::string measurment_error_output = "+-" + std::to_string(ugv1.getMeasurmentError() + ugv2.getMeasurmentError()) + "[pixels]";
    double result = atan((ugv2.y_position - ugv1.y_position) / (ugv2.x_position - ugv1.x_position)) * 180 / PI;
    double resultarctan2 = ((atan2(ugv2.x_position - ugv1.x_position, ugv2.y_position - ugv1.y_position) * 180 / PI) - 180) * (-1);
    std::string angle_output = "angle: = " + std::to_string(result);
    std::string angle_output_atan2 = "angle atan2: = " + std::to_string(resultarctan2);

    cv::putText(img,
                distance_output + measurment_error_output,
                cv::Point2d(img.rows / 2, img.cols / 2),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN, 2,
                cv::Scalar(127, 127, 127),
                1,
                7);
    cv::putText(img,
                ugv1_pos_output,
                cv::Point2d(img.rows / 2, (img.cols / 2) + 25),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                cv::Scalar(127, 127, 127),
                1,
                7);
    cv::putText(img,
                ugv2_pos_output,
                cv::Point2d(img.rows / 2, (img.cols / 2) + 50),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                cv::Scalar(127, 127, 127),
                1,
                7);
    cv::putText(img,
                angle_output,
                cv::Point2d(img.rows / 2, (img.cols / 2) - 75),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                2,
                cv::Scalar(127, 127, 127),
                1,
                7);
    cv::putText(img,
                angle_output_atan2,
                cv::Point2d(img.rows / 2, (img.cols / 2) - 100),
                cv::HersheyFonts::FONT_HERSHEY_PLAIN,
                0.75,
                cv::Scalar(127, 127, 127),
                1,
                7);
}

void draw(cv::Mat &img, Node ugv1, Node ugv2)
{
    ugv1.drawNode(img);
    ugv2.drawNode(img);
    drawConnectingLine(img, ugv1, ugv2);
    drawTextOnScreen(img, ugv1, ugv2);
    cv::arrowedLine(img, cv::Point2d(ugv1.x_position, ugv1.y_position), cv::Point2d(ugv1.x_position + 100, ugv1.y_position), cv::Scalar(0, 0, 255), 5);
    cv::arrowedLine(img, cv::Point2d(ugv1.x_position, ugv1.y_position), cv::Point2d(ugv1.x_position, ugv1.y_position - 100), cv::Scalar(255, 0, 0), 5);
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
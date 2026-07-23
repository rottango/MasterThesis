#include <calculate.hpp>
#include <node_class.hpp>

#define DEGREES_TO_RADIANS PI / 180
#define RADIANS_TO_DEGREES 180 / PI

cv::Point2d openCVPointToCartesianPoint(cv::Point2d opencv_point, cv::Point2d opencv_origin_point)
{
    return cv::Point2d(opencv_point.x - opencv_origin_point.x, opencv_origin_point.y - opencv_point.y);
}

cv::Point2d cartesianPointToOpenCVPoint(cv::Point2d cartesian_point, cv::Point2d opencv_origin_point)
{
    return cv::Point2d(cartesian_point.x + opencv_origin_point.x, opencv_origin_point.y - cartesian_point.y);
}

void calculate(double x, double y)
{
}

void calculateRotationMatrix(double &x, double &y, double theta)
{

    double old_x = x;
    double old_y = y;

    x = old_x * cos(theta * DEGREES_TO_RADIANS) - old_y * sin(theta * DEGREES_TO_RADIANS);
    y = old_x * sin(theta * DEGREES_TO_RADIANS) + old_y * cos(theta * DEGREES_TO_RADIANS);
}

void calculateNewPoints(Node &ugv, double theta)
{
    double x_pos_diff = ugv.y_axis_point.x - ugv.opencv_x_y_point.x;
    double y_pos_diff = ugv.y_axis_point.y - ugv.opencv_x_y_point.y;
    calculateRotationMatrix(x_pos_diff, y_pos_diff, theta);
    ugv.y_axis_point.x = ugv.opencv_x_y_point.x + x_pos_diff;
    ugv.y_axis_point.y = ugv.opencv_x_y_point.y + y_pos_diff;
    ugv.x_axis_point.x = ugv.opencv_x_y_point.x - y_pos_diff;
    ugv.x_axis_point.y = ugv.opencv_x_y_point.y + x_pos_diff;
    ugv.changeThetaRotation(theta);
}

double calculateDistanceBetweenPoints(double x1, double x2, double y1, double y2)
{
    double square_difference_x = (x2 - x1) * (x2 - x1);
    double square_difference_y = (y2 - y1) * (y2 - y1);
    double sum = square_difference_x + square_difference_y;
    double distance = sqrt(sum);
    return distance;
}

double calculateAngle(Node observer, Node target)
{
    return ((atan2(target.opencv_x_y_point.x - observer.opencv_x_y_point.x, target.opencv_x_y_point.y - observer.opencv_x_y_point.y) * RADIANS_TO_DEGREES) - 180) * (-1);
}

#include <calculate.hpp>
#include <node_class.hpp>

#define DEGREES_TO_RADIANS PI / 180
#define RADIANS_TO_DEGREES 180 / PI

cv::Point2d openCVPointToCartesianPoint(cv::Point2d opencv_point)
{
    return cv::Point2d(opencv_point.x - 1920 / 2, 1080 / 2 - opencv_point.y);
}

cv::Point2d cartesianPointToOpenCVPoint(cv::Point2d cartesian_point)
{
    return cv::Point2d(cartesian_point.x + 1920 / 2, 1080 / 2 - cartesian_point.y);
}

void calculate(double x, double y)
{
}

void calculateRotationMatrix(double &x, double &y, double theta_rotation_degrees)
{

    double old_x = x;
    double old_y = y;

    x = old_x * cos(theta_rotation_degrees * DEGREES_TO_RADIANS) - old_y * sin(theta_rotation_degrees * DEGREES_TO_RADIANS);
    y = old_x * sin(theta_rotation_degrees * DEGREES_TO_RADIANS) + old_y * cos(theta_rotation_degrees * DEGREES_TO_RADIANS);
}

void calculateNewPoints(Node &ugv, double theta_rotation_degrees)
{
    double x_pos_diff = ugv.cartesian_y_axis_point.x - ugv.cartesian_x_y_point.x;
    double y_pos_diff = ugv.cartesian_y_axis_point.y - ugv.cartesian_x_y_point.y;
    calculateRotationMatrix(x_pos_diff, y_pos_diff, theta_rotation_degrees);
    ugv.cartesian_y_axis_point.x = ugv.cartesian_x_y_point.x + x_pos_diff;
    ugv.cartesian_y_axis_point.y = ugv.cartesian_x_y_point.y + y_pos_diff;
    ugv.cartesian_x_axis_point.x = ugv.cartesian_x_y_point.x - y_pos_diff;
    ugv.cartesian_x_axis_point.y = ugv.cartesian_x_y_point.y + x_pos_diff;
    ugv.change_theta_rotation_degrees(theta_rotation_degrees);
}

double calculateDistanceBetweenPoints(double x1, double x2, double y1, double y2)
{
    double square_difference_x = (x2 - x1) * (x2 - x1);
    double square_difference_y = (y2 - y1) * (y2 - y1);
    double sum = square_difference_x + square_difference_y;
    double distance = sqrt(sum);
    return distance;
}

double cartesianCalculateAngle(Node observer, Node target)
{
    double result = ((atan2(target.cartesian_x_y_point.y - observer.cartesian_x_y_point.y, target.cartesian_x_y_point.x - observer.cartesian_x_y_point.x)) * RADIANS_TO_DEGREES);
    result -= observer.theta_rotation_degrees;
    if (result < -180)
    {
        result += 360;
    }
    if (result > 180)
    {
        result -= 360;
    }
    return result;
}

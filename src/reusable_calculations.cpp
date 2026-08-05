#include <reusable_calculations.hpp>

// each cartesian unit equals to one pixel for now.

cv::Point2d openCVPointToCartesianPoint(cv::Point2d opencv_point)
{
    return cv::Point2d(opencv_point.x - SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - opencv_point.y);
}

cv::Point2d cartesianPointToOpenCVPoint(cv::Point2d cartesian_point)
{
    return cv::Point2d(cartesian_point.x + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - cartesian_point.y);
}

double degreesToRadians(double angle_degrees)
{
    return angle_degrees * std::numbers::pi / 180;
}

double radiansToDegrees(double angle_radians)
{
    return angle_radians * 180 / std::numbers::pi;
}

double normalizeAngleDegrees(double angle_degrees) // return value only <-180,180)
{
    while (angle_degrees < -180 || angle_degrees >= 180) // std::isfinite for future reading
    {
        if (angle_degrees < -180)
        {
            angle_degrees += 360;
        }
        if (angle_degrees >= 180)
        {
            angle_degrees -= 360;
        }
    }

    return angle_degrees;
}

double distanceBetweenTwoPoints(cv::Point2d point_1, cv::Point2d point_2)
{
    double square_difference_x = (point_2.x - point_1.x) * (point_2.x - point_1.x);
    double square_difference_y = (point_2.y - point_1.y) * (point_2.y - point_1.y);
    double sum = square_difference_x + square_difference_y;
    double distance = std::sqrt(sum);
    return distance;
}

double bearingBetweenTwoPointsDegrees(cv::Point2d point_observer, cv::Point2d point_target) // this is the standard bearing calculations, that should be dispalyed
{
    double result = radiansToDegrees((std::atan2(point_target.y - point_observer.y, point_target.x - point_observer.x)));
    return normalizeAngleDegrees(result);
}

cv::Point2d rotatePointAroundCenterPoint(cv::Point2d point_to_rotate, cv::Point2d rotation_center, double theta_rotation_degrees) // 0 degrees is at the x axis, positive angles go counterclockwise, negative go clockwise
{
    // make sure we are rotating arount the center point
    double x_pos_normalized_to_the_cartesian_axis_origin = point_to_rotate.x - rotation_center.x;
    double y_pos_normalized_to_the_cartesian_axis_origin = point_to_rotate.y - rotation_center.y;

    double temp_x = x_pos_normalized_to_the_cartesian_axis_origin;
    double temp_y = y_pos_normalized_to_the_cartesian_axis_origin;
    double theta_rotation_radians = degreesToRadians(theta_rotation_degrees);

    double normalized_new_x = temp_x * std::cos(theta_rotation_radians) - temp_y * std::sin(theta_rotation_radians);
    double normalized_new_y = temp_x * std::sin(theta_rotation_radians) + temp_y * std::cos(theta_rotation_radians);

    double new_x = normalized_new_x + rotation_center.x;
    double new_y = normalized_new_y + rotation_center.y;

    return cv::Point2d(new_x,
                       new_y);
}

cv::Point2d calculatePointFromCenter(cv::Point2d center_point, double theta_rotation_degrees, double distance)
{

    // using polar coordinates, it calculates from the cartesian axis origin point
    double r = distance;
    double x = r * std::cos(degreesToRadians(theta_rotation_degrees));
    double y = r * std::sin(degreesToRadians(theta_rotation_degrees));

    double new_point_x = x + center_point.x;
    double new_point_y = y + center_point.y;

    return cv::Point2d(new_point_x, new_point_y);
}

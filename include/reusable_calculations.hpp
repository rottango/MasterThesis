#pragma once

#include <cmath>
#include <numbers>
#include <opencv2/opencv.hpp>

/**
 * @brief Recieve a point in openCV coordinates and translate them into a point in cartesian coordiantes
 * 
 * @param opencv_point 
 * @param screen_width 
 * @param screen_height 
 * @return cv::Point2d 
 */
cv::Point2d openCVPointToCartesianPoint(cv::Point2d opencv_point, int screen_width, int screen_height);
/**
 * @brief Recieve a point in cartesian coordiantes and translate them into a point in openCV coordiantes
 * 
 * @param cartesian_point 
 * @param screen_width 
 * @param screen_height 
 * @return cv::Point2d 
 */
cv::Point2d cartesianPointToOpenCVPoint(cv::Point2d cartesian_point, int screen_width, int screen_height);

/**
 * @brief Change the unit from degrees to radians
 * 
 * @param angle_degrees 
 * @return double 
 */
double degreesToRadians(double angle_degrees);

/**
 * @brief Change the unit from radians to degrees
 * 
 * @param angle_radians 
 * @return double 
 */
double radiansToDegrees(double angle_radians);

/**
 * @brief normalize the degrees to <-180;180)
 * 
 * @param angle_degrees 
 * @return double 
 */
double normalizeAngleDegrees(double angle_degrees);

/**
 * @brief Calcualte the distance between two points given two points
 * 
 * @param point_1 
 * @param point_2 
 * @return double 
 */
double distanceBetweenTwoPoints(cv::Point2d point_1, cv::Point2d point_2);

/**
 * @brief Calculate the angle between two points and then normalize the results to the normalized rangesolution provided by the one and only - gf
 * 
 * @param point_observer 
 * @param point_target 
 * @return double 
 */
double bearingBetweenTwoPointsDegrees(cv::Point2d point_observer, cv::Point2d point_target); // this is the standard bearing calculations, that souhldbe dispalyed

/**
 * @brief Calculate, using polar coordinates, a new point rotated by
 * 
 * @param center_point 
 * @param theta_rotation_degrees 
 * @param distance 
 * @return cv::Point2d 
 */
cv::Point2d calculatePointFromCenter(cv::Point2d center_point, double theta_rotation_degrees, double distance);

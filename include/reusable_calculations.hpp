#pragma once

#include <cmath>
#include <numbers>
#include <opencv2/opencv.hpp>

/**
 * @brief 
 * 
 * @param opencv_point 
 * @param screen_width 
 * @param screen_height 
 * @return cv::Point2d 
 */
cv::Point2d openCVPointToCartesianPoint(cv::Point2d opencv_point, int screen_width, int screen_height);
/**
 * @brief 
 * 
 * @param cartesian_point 
 * @param screen_width 
 * @param screen_height 
 * @return cv::Point2d 
 */
cv::Point2d cartesianPointToOpenCVPoint(cv::Point2d cartesian_point, int screen_width, int screen_height);

/**
 * @brief 
 * 
 * @param angle_degrees 
 * @return double 
 */
double degreesToRadians(double angle_degrees);

/**
 * @brief 
 * 
 * @param angle_radians 
 * @return double 
 */
double radiansToDegrees(double angle_radians);

/**
 * @brief 
 * 
 * @param angle_degrees 
 * @return double 
 */
double normalizeAngleDegrees(double angle_degrees);

/**
 * @brief 
 * 
 * @param point_1 
 * @param point_2 
 * @return double 
 */
double distanceBetweenTwoPoints(cv::Point2d point_1, cv::Point2d point_2);

/**
 * @brief 
 * 
 * @param point_observer 
 * @param point_target 
 * @return double 
 */
double bearingBetweenTwoPointsDegrees(cv::Point2d point_observer, cv::Point2d point_target); // this is the standard bearing calculations, that souhldbe dispalyed

/**
 * @brief 
 * 
 * @param point_to_rotate 
 * @param rotation_center 
 * @param theta_rotation_degrees 
 * @return cv::Point2d 
 * when already have a point and rortate it around the center that is another point
 */
cv::Point2d rotatePointAroundCenterPoint(cv::Point2d point_to_rotate, cv::Point2d rotation_center, double theta_rotation_degrees); // uses rotationMatrix in it

/**
 * @brief 
 * 
 * @param center_point 
 * @param theta_rotation_degrees 
 * @param distance 
 * @return cv::Point2d 
 */
cv::Point2d calculatePointFromCenter(cv::Point2d center_point, double theta_rotation_degrees, double distance);

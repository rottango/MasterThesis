#pragma once

#include <cmath>
#include <numbers>
#include <opencv2/opencv.hpp>

#include <reusable_calculations.hpp>

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

cv::Point2d openCVPointToCartesianPoint(cv::Point2d opencv_point);

cv::Point2d cartesianPointToOpenCVPoint(cv::Point2d cartesian_point);

double degreesToRadians(double angle_degrees);

double radiansToDegrees(double angle_radians);

double normalizeAngleDegrees(double angle_degrees);

double distanceBetweenTwoPoints(cv::Point2d point_1, cv::Point2d point_2);

double bearingBetweenTwoPointsDegrees(cv::Point2d point_observer, cv::Point2d point_target); // this is the standard bearing calculations, that souhldbe dispalyed

// when already have a point and rortate it around the center that is another point
cv::Point2d rotatePointAroundCenterPoint(cv::Point2d point_to_rotate, cv::Point2d rotation_center, double theta_rotation_degrees); // uses rotationMatrix in it

cv::Point2d calculatePointFromCenter(cv::Point2d center_point, double theta_rotation_degrees, double distance);

#pragma once

#include <cmath>
#include <extern_variables.hpp>
#include <node_class.hpp>

#define PI 3.14159265

cv::Point2d openCVPointToCartesianPoint(cv::Point2d opencv_point, cv::Point2d opencv_origin_point);

cv::Point2d cartesianPointToOpenCVPoint(cv::Point2d cartesian_point, cv::Point2d opencv_origin_point);

void calculate();

double calculateAngle(Node observer, Node target);

double calculateDistanceBetweenPoints(double x1, double x2, double y1, double y2);

void calculateRotationMatrix(double &x, double &y, double theta); // https://en.wikipedia.org/wiki/Rotation_matrix,
// how to prevent long term drift of angle due to rotation angle estimation.?
// contact proffessor ?
// this shouldnt be the name for the funciton, because it calculates new poitns, not the rotation matrix

void calculateNewPoints(Node &ugv, double theta);
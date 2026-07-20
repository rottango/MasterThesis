#pragma once
#include <calculate.hpp>
#include <node_class.hpp>
void calculate()
{
}

void calculateRotationMatrix(double &x, double &y, double theta)
{
    double old_x = x;
    double old_y = y;

    x = old_x * cos(theta * PI / 180) - old_y * sin(theta * PI / 180);
    y = old_x * sin(theta * PI / 180) - old_y * cos(theta * PI / 180);
}

void calculateNewPoints(Node &ugv, double theta)
{
    calculateRotationMatrix(ugv.x_axis_point, ugv.y_axis_point, theta);
    ugv.theta_rotation += theta;
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
    return ((atan2(target.x_position - observer.x_position, target.y_position - observer.y_position) * 180 / PI) - 180) * (-1);
}
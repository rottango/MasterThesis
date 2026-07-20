#pragma once
#include <calculate.hpp>
#include <node_class.hpp>
void calculate()
{
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
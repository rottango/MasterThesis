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
    y = old_x * sin(theta * PI / 180) + old_y * cos(theta * PI / 180);
}

void calculateNewPoints(Node &ugv, double theta)
{
    double x_position = ugv.x_position, y_position = ugv.y_position;
    double x_y_axis_point = ugv.x_y_axis_point, y_y_axis_point = ugv.y_y_axis_point;
    double x_pos_diff = x_y_axis_point - x_position;
    double y_pos_diff = y_y_axis_point - y_position;
    calculateRotationMatrix(x_pos_diff, y_pos_diff, theta);
    ugv.x_y_axis_point = ugv.x_position + x_pos_diff;
    ugv.y_y_axis_point = ugv.y_position + y_pos_diff;
    ugv.x_x_axis_point = ugv.x_position - y_pos_diff;
    ugv.y_x_axis_point = ugv.y_position + x_pos_diff;
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
    return ((atan2(target.x_position - observer.x_position, target.y_position - observer.y_position) * 180 / PI) - 180) * (-1);
}

// ugv (100,100)
// axis point (200,100)
// theta(90)

// x_pos_diff= 200 - 100 = 100
// y_pos_diff= 100 - 100 = 0
// normalized vector = (100,0)
// wchich is correct i think

// new point:

// new_x=100 * cos(90) - 0 * sin(90)
// cos(90)=0
// new_y=100*sin(90) + 0*cos(90)
// sin(90)=1

// new_x= 100 *0=0
// new_y= 100

// i think its ok?

// ugv.x_y_axis_point = ugv.x_position + x_pos_diff;
// ugv.y_y_axis_point = ugv.y_position + y_pos_diff;
// ugv.theta_rotation += theta;

// new cordinates of axis point:
// x_y_axis_point = 100+0
// y_y_axis_point= 100+100
//(100,200)
//
#pragma once

#include <node_class.hpp>

Node::Node(double x_position,
           double y_position,
           double z_position,
           double theta_rotation,
           double vehicle_size,
           double inner,
           double measurment_error_CM,
           colorPalet newugvColorPalet)
{
    this->x_position = x_position;
    this->y_position = y_position;
    this->z_position = z_position;
    this->theta_rotation = theta_rotation;

    this->vehicle_size = vehicle_size;
    this->inner = inner;
    this->measurment_error_CM = measurment_error_CM;

    this->x_x_axis_point = x_position + 100;
    this->y_x_axis_point = y_position;
    this->x_y_axis_point = x_position;
    this->y_y_axis_point = y_position - 100;

    this->ugvColorPalet = newugvColorPalet;
}

void Node::changeThetaRotation(double new_theta_rotation)
{
    double remainder = std::fmod(this->theta_rotation + new_theta_rotation, 360.00f);
    if (remainder < 0)
    {
        this->theta_rotation = remainder + 360;
    }
    else
    {
        this->theta_rotation = remainder;
    }
}

void Node::assingColors()
{
    ugvColorPalet.vehicle_color[0] = 35;
    ugvColorPalet.vehicle_color[1] = 75;
    ugvColorPalet.vehicle_color[2] = 0;

    ugvColorPalet.inner_color[0] = 0;
    ugvColorPalet.inner_color[1] = 100;
    ugvColorPalet.inner_color[2] = 0;

    ugvColorPalet.measurment_error_color[0] = 0;
    ugvColorPalet.measurment_error_color[1] = 114;
    ugvColorPalet.measurment_error_color[2] = 0;

    ugvColorPalet.observer_line_color[0] = 0;
    ugvColorPalet.observer_line_color[1] = 128;
    ugvColorPalet.observer_line_color[2] = 0;

    ugvColorPalet.text_color[0] = 0;
    ugvColorPalet.text_color[1] = 176;
    ugvColorPalet.text_color[2] = 56;
}

void Node::changePositionXYZ(double new_x_position,
                             double new_y_position,
                             double new_z_position)
{
    double x_delta = new_x_position - this->x_position;
    double y_delta = new_y_position - this->y_position;
    double z_delta = new_z_position - this->z_position;
    this->x_position = new_x_position;
    this->y_position = new_y_position;
    this->z_position = new_z_position;

    changeAxisPoints(x_delta, y_delta, z_delta);
}

void Node::changeAxisPoints(double new_x_position,
                            double new_y_position,
                            double new_z_position)
{
    this->x_y_axis_point = x_y_axis_point + new_x_position;
    this->y_y_axis_point = y_y_axis_point + new_y_position;
    this->x_x_axis_point = x_x_axis_point + new_x_position;
    this->y_x_axis_point = y_x_axis_point + new_y_position;
}

void Node::drawNode(cv::Mat img)
{
    cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->vehicle_size, this->ugvColorPalet.vehicle_color, cv::FILLED, 8, 0);
    cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->inner, this->ugvColorPalet.inner_color, 2, 8, 0);
    cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->measurment_error_CM, this->ugvColorPalet.measurment_error_color, 2, 8, 0);
}

void Node::setVehicleSize(double new_vehicle_size)
{
    this->vehicle_size = new_vehicle_size;
}

void Node::setInner(double new_inner)
{
    this->inner = new_inner;
}

void Node::setMeasurmentError(double new_measurment_error_CM)
{
    this->measurment_error_CM = new_measurment_error_CM;
}

double Node::getVehicleSize()
{
    return this->vehicle_size;
}

double Node::getInner()
{
    return this->inner;
}

double Node::getMeasurmentError()
{
    return this->measurment_error_CM;
}

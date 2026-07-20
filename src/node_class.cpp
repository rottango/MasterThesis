#pragma once

#include <node_class.hpp>

Node::Node(double x_position,
           double y_position,
           double z_position,
           double vehicle_size,
           double local_rotation,
           double inner,
           double measurment_error_CM)
{
    this->x_position = x_position;
    this->y_position = y_position;
    this->z_position = z_position;
    this->local_rotation = local_rotation;
    this->vehicle_size = vehicle_size;
    this->inner = inner;
    this->measurment_error_CM = measurment_error_CM;

    changeAxisPoints(this->x_position, this->y_position, this->z_position);
}

void Node::change_local_rotation(double new_local_rotation)
{
    this->local_rotation = new_local_rotation;
}

void Node::changePositionXYZ(double new_x_position,
                             double new_y_position,
                             double new_z_position)
{
    this->x_position = new_x_position;
    this->y_position = new_y_position;
    this->z_position = new_z_position;

    changeAxisPoints(this->x_position, this->y_position, this->z_position);
}

void Node::changeAxisPoints(double new_x_position,
                            double new_y_position,
                            double new_z_position)
{
    this->x_axis_point = new_x_position + 100;
    this->y_axis_point = new_y_position - 100;
}

void Node::drawNode(cv::Mat img)
{
    cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->vehicle_size, cv::Scalar(52, 66, 227), cv::FILLED, 8, 0);
    cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->inner, cv::Scalar(52, 66, 227), 2, 8, 0);
    cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->measurment_error_CM, cv::Scalar(52, 66, 227), 2, 8, 0);
}

void Node::setVehicleSize(double newvehicle_size)
{
    this->vehicle_size = newvehicle_size;
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

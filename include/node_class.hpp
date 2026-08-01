#pragma once

#include "boost/lexical_cast.hpp"
#include <cstdint>

#include <color_palet_struct.hpp>
#include <opencv2/opencv.hpp>

// observer
// target
// Only the target’s position and the observer’s position and heading matter

class Node
{
public:
    uint8_t node_id;

    // cartesian
    cv::Point2d cartesian_x_y_point;
    cv::Point2d cartesian_x_axis_point;
    cv::Point2d cartesian_y_axis_point;

    // not specified
    double theta_rotation_degrees;

    // misc
    colorPalet nodeColorPalet;

    bool is_active;

    Node(uint8_t node_id, cv::Point2d cartesian_x_y_point,
         double theta_rotation_degrees,
         double vehicle_size_,
         double inner_,
         double measurment_error_CM_,
         colorPalet nodeColorPalet);

    void changePosition(cv::Point2d opencv_x_y_point);

    void changeAxisPoints(cv::Point2d opencv_x_y_point);

    void assingColors();

    void change_theta_rotation_degrees(double new_theta_rotation_degrees);

    void setVehicleSize(double new_vehicle_size_);

    void setInner(double new_inner_);

    void setMeasurmentError(double new_measurment_error_CM_);

    double getVehicleSize();

    double getInner();

    double getMeasurmentError();

private:
    int vehicle_size_;
    int inner_;
    int measurment_error_CM_;
};
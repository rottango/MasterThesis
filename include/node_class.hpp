#pragma once

#include "boost/lexical_cast.hpp"
#include <color_palet_struct.hpp>
#include <opencv2/opencv.hpp>

// observer
// target
// Only the target’s position and the observer’s position and heading matter

class Node
{
public:
    // cartesian
    cv::Point2d cartesian_x_y_point;
    cv::Point2d cartesian_x_axis_point;
    cv::Point2d cartesian_y_axis_point;

    // not specified
    double theta_rotation_degrees;
    double angle_output_atan2_to_target;

    // misc
    colorPalet ugvColorPalet;

    Node(cv::Point2d cartesian_x_y_point,
         double theta_rotation_degrees,
         double vehicle_size,
         double inner,
         double measurment_error_CM,
         colorPalet ugvColorPalet);

    void openCVCartesianCalculateAngle(cv::Point2d opencv_x_y_point);

    void changeAxisPoints(cv::Point2d opencv_x_y_point);

    void assingColors();

    void change_theta_rotation_degrees(double new_theta_rotation_degrees);

    void setVehicleSize(double new_vehicle_size);

    void setInner(double new_inner);

    void setMeasurmentError(double new_measurment_error_CM);

    double getVehicleSize();

    double getInner();

    double getMeasurmentError();

private:
    int vehicle_size;
    int inner;
    int measurment_error_CM;
};
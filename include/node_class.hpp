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
    // openCV
    cv::Point2d opencv_x_y_point;
    double opencv_z_position;
    cv::Point2d opencv_x_axis_point;
    cv::Point2d opencv_y_axis_point;

    /// cartesian
    cv::Point2d cartesian_x_y_point;
    double cartesian_z_position;
    cv::Point2d cartesian_x_axis_point;
    cv::Point2d cartesian_y_axis_point;

    // not specified
    double theta_rotation_degrees;
    double angle_output_atan2_to_target;

    // misc
    colorPalet ugvColorPalet;

    Node(cv::Point2d cartesian_x_y_point,
         double cartesian_z_position,
         double theta_rotation_degrees,
         double vehicle_size,
         double inner,
         double measurment_error_CM,
         colorPalet ugvColorPalet);

    void openCVCartesianCalculateAngle(cv::Point2d opencv_x_y_point,
                                       double new_opencv_z_position);

    void changeAxisPoints(cv::Point2d opencv_x_y_point,
                          double new_opencv_z_position);

    void assingColors();

    void change_theta_rotation_degrees(double new_theta_rotation_degrees);

    void drawNode(cv::Mat img);

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
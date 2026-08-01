#pragma once

#include "boost/lexical_cast.hpp"
#include <cstdint>

#include <color_palet_struct.hpp>
#include <opencv2/opencv.hpp>

class Node
{
public:
    Node(uint8_t node_id, cv::Point2d cartesian_x_y_point,
         double theta_rotation_degrees,
         double vehicle_size_,
         double inner_,
         double measurment_error_CM_,
         colorPalet nodeColorPalet);

private:
    uint8_t getNodeId();

    cv::Point2d getXYPoint();

    cv::Point2d getXAxisPoint();

    cv::Point2d getYAxisPoint();

    bool getActiveState();

    double getVehicleSize();

    double getInner();

    double getMeasurmentError();

    void setNodeId();

    void setXYPoint();

    void setXAxisPoint();

    void setYAxisPoint();

    void setActiveState();

    void setThetaRotationDegrees();

    void setVehicleSize(double new_vehicle_size_);

    void setInner(double new_inner_);

    void setMeasurmentError(double new_measurment_error_CM_);

    void changePosition(cv::Point2d opencv_x_y_point);

    void changeAxisPoints(cv::Point2d opencv_x_y_point);

    void assingColors();

    void change_theta_rotation_degrees(double new_theta_rotation_degrees);

    uint8_t node_id_;
    cv::Point2d cartesian_x_y_point_;
    cv::Point2d cartesian_x_axis_point_;
    cv::Point2d cartesian_y_axis_point_;
    int vehicle_size_;
    int inner_;
    int measurment_error_CM_;
    double theta_rotation_degrees_;
    colorPalet node_color_palet_;
    bool is_active_;
};
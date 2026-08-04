#pragma once

#include <cstdint>

#include <color_palet_struct.hpp>
#include <opencv2/opencv.hpp>

class Node
{
public:
    Node(uint8_t node_id_,
         cv::Point2d cartesian_x_y_point_,
         double theta_rotation_degrees_,
         uint8_t vehicle_size_,
         uint8_t inner_,
         uint8_t measurment_error_CM_,
         colorPalet node_color_palet_);

    uint8_t getNodeId() const;

    cv::Point2d getXYPoint() const;

    cv::Point2d getXAxisPoint() const;

    cv::Point2d getYAxisPoint() const;

    // bool getActiveState();

    uint8_t getVehicleSize() const;

    uint8_t getInner() const;

    uint8_t getMeasurmentError() const;

    double getThetaRotationDegrees() const;

    void changePosition(cv::Point2d cartesian_x_y_point);

    void rotateNodesAxis(double theta_rotation_degrees_); // inside call changeThetaRotationDegrees

    void assignColors(colorPalet color_palet); // should be accessible publicly

private:
    void setVehicleSize(uint8_t new_vehicle_size_);

    void setInner(uint8_t new_inner_);

    void setMeasurmentError(uint8_t new_measurment_error_CM_);

    void setXYPoint(cv::Point2d cartesian_x_y_point_); // to call after chanignPosition()

    void changeAxisPoints(); // to call after changix position()

    void changeThetaRotationDegrees(double new_theta_rotation_degrees);

    uint8_t node_id_; // no need to have a setter for the future
    cv::Point2d cartesian_x_y_point_;
    cv::Point2d cartesian_x_axis_point_;
    cv::Point2d cartesian_y_axis_point_;
    uint8_t vehicle_size_;
    uint8_t inner_;
    uint8_t measurment_error_CM_;
    double theta_rotation_degrees_;
    colorPalet node_color_palet_;
    // bool is_active_;
};
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
         uint8_t measurment_error_cm_,
         colorPalet node_color_palet_);

    uint8_t getNodeId() const;

    cv::Point2d getXYPoint() const;

    cv::Point2d getXAxisPoint() const;

    cv::Point2d getYAxisPoint() const;

    uint8_t getVehicleSize() const;

    uint8_t getInner() const;

    uint8_t getMeasurmentError() const;

    colorPalet getColorPalet() const;

    double getThetaRotationDegrees() const;

    void changePosition(cv::Point2d cartesian_x_y_point);

    void rotateNodesAxis(double theta_rotation_degrees_); // inside call changeThetaRotationDegrees

    void assignColors(colorPalet color_palet); // should be accessible publicly

private:
    void setNodeId(uint8_t node_id_);

    void setVehicleSize(uint8_t new_vehicle_size_);

    void setInner(uint8_t new_inner_);

    void setMeasurmentErrorCm(uint8_t new_measurment_error_cm_);

    void setXYPoint(cv::Point2d cartesian_x_y_point_); // to call after chanignPosition()

    void setXAxisPoint(); // helper function to the setAxisPoints

    void setYAxisPoint(); // helper function to the setAxisPoints

    void setAxisPoints(); // to call after changix position()

    void setThetaRotationDegrees(double new_theta_rotation_degrees);

    uint8_t node_id_; // no need to have a setter for the future
    cv::Point2d cartesian_x_y_point_{0, 0};
    cv::Point2d cartesian_x_axis_point_{100, 0};
    cv::Point2d cartesian_y_axis_point_{0, 100};
    uint8_t vehicle_size_ = 0;
    uint8_t inner_ = 0;
    uint8_t measurment_error_cm_ = 0;
    double theta_rotation_degrees_ = 0;
    colorPalet node_color_palet_;
};
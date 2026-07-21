#pragma once

#include "boost/lexical_cast.hpp"
#include <opencv2/opencv.hpp>

// observer
// target
// Only the target’s position and the observer’s position and heading matter

class Node
{
public:
    double x_position; // [+] right / [-]left
    double y_position; // [+] back/ [-]front
    double z_position; // [+] up / [-] down
    double theta_rotation;
    double x_y_axis_point;
    double y_y_axis_point;
    double x_x_axis_point;
    double y_x_axis_point;

    cv::Scalar vehicle_color;
    cv::Scalar inner_color;
    cv::Scalar measurment_error_color;
    cv::Scalar observer_line_color;
    cv::Scalar text_color;
    // bgr ugv1/ugv2
    //  234b00 //2f0f80
    //  006400 //3c13a4
    //  007200 //4a18c9
    //  008000 //6d4dff
    //  00b038 //8f75ff

    Node(double x_position,
         double y_position,
         double z_position,
         double theta_rotation,
         double vehicle_size,
         double inner,
         double measurment_error_CM);

    void changePositionXYZ(double new_x_position,
                           double new_y_position,
                           double new_z_position);

    void changeAxisPoints(double new_x_position,
                          double new_y_position,
                          double new_z_position);

    void assingColors();

    void changeThetaRotation(double new_theta_rotation);

    void drawNode(cv::Mat img);

    void setVehicleSize(double newvehicle_size);

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
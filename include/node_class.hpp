#pragma once

#include <opencv2/opencv.hpp>

// observer
// target
// Only the target’s position and the observer’s position and heading matter

class Node
{
public:
    double x_position; // [+] front / [-]back
    double y_position; // [+] right / [-]left
    double z_position; // [+] up / [-] down
    double local_rotation;

    // struct colorPreset();

    Node(double x_position,
         double y_position,
         double z_position,
         double local_rotation, // current absolute heading relative to the world axis
         double vehicle_size,
         double inner,
         double measurment_error_CM);

    void changePositionXYZ(double new_x_position,
                           double new_y_position,
                           double new_z_position);

    void change_local_rotation(double new_local_rotation);

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
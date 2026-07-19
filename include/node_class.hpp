#pragma once

#include <opencv2/opencv.hpp>

class Node
{
public:
    double x_position; // [+] front / [-]back
    double y_position; // [+] right / [-]left
    double z_position; // [+] up / [-] down

    Node(double x_position,
         double y_position,
         double z_position,
         double vehicle_size,
         double inner,
         double measurment_error_CM)
    {
        this->x_position = x_position;
        this->y_position = y_position;
        this->z_position = z_position;
        this->vehicle_size = vehicle_size;
        this->inner = inner;
        this->measurment_error_CM = measurment_error_CM;
    }

    void changePositionXYZ(double new_x_position,
                           double new_y_position,
                           double new_z_position)
    {
        this->x_position = new_x_position;
        this->y_position = new_y_position;
        this->z_position = new_z_position;
    }

    void drawNode(cv::Mat img)
    {
        cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->vehicle_size, cv::Scalar(52, 66, 227), cv::FILLED, 8, 0);
        cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->inner, cv::Scalar(52, 66, 227), 2, 8, 0);
        cv::circle(img, cv::Point2d(this->x_position, this->y_position), this->measurment_error_CM, cv::Scalar(52, 66, 227), 2, 8, 0);
    }

    void setVehicleSize(double newvehicle_size)
    {
        this->vehicle_size = newvehicle_size;
    }

    void setInner(double new_inner)
    {
        this->inner = new_inner;
    }

    void setMeasurmentError(double new_measurment_error_CM)
    {
        this->measurment_error_CM = new_measurment_error_CM;
    }

    double getVehicleSize()
    {
        return this->vehicle_size;
    }

    double getInner()
    {
        return this->inner;
    }

    double getMeasurmentError()
    {
        return this->measurment_error_CM;
    }

private:
    int vehicle_size;
    int inner;
    int measurment_error_CM;
};
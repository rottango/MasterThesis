#pragma once

#include <cstdint>

#include <color_palet_struct.hpp>
#include <opencv2/opencv.hpp>

/**
* @file node_class.hpp
* @author rottango
* @date 13.10.2026
* @see ‘‘ OpenCV2 ’’ 
*
* @brief Header file for the node, that the software representation of a UGV.
*/
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
    
    /**
     * @brief Get the Node Id object
     * 
     * @return uint8_t 
     */
    uint8_t getNodeId() const;

    /**
     * @brief 
     * 
     * @return cv::Point2d 
     */
    cv::Point2d getXYPoint() const;

    /**
     * @brief 
     * 
     * @return cv::Point2d 
     */
    cv::Point2d getXAxisPoint() const;

    /**
     * @brief 
     * 
     * @return cv::Point2d 
     */
    cv::Point2d getYAxisPoint() const;

    /**
     * @brief Get the Vehicle Size object
     * 
     * @return uint8_t 
     */
    uint8_t getVehicleSize() const;

    /**
     * @brief Get the Inner object
     * 
     * @return uint8_t 
     */
    uint8_t getInner() const;

    /**
     * @brief Get the Measurment Error object
     * 
     * @return uint8_t 
     */
    uint8_t getMeasurmentError() const;

    /**
     * @brief Get the Color Palet object
     * 
     * @return const colorPalet& 
     */
    const colorPalet &getColorPalet() const;

    /**
     * @brief Get the Theta Rotation Degrees object
     * 
     * @return double 
     */
    double getThetaRotationDegrees() const;

    /**
     * @brief 
     * 
     * @param cartesian_x_y_point 
     */
    void changePosition(cv::Point2d cartesian_x_y_point);

    /**
     * @brief 
     * 
     * @param theta_rotation_degrees_ 
     */
    void rotateNodesAxis(double theta_rotation_degrees_); // inside call changeThetaRotationDegrees

    /**
     * @brief 
     * 
     * @param color_palet 
     */
    void assignColors(colorPalet color_palet); // should be accessible publicly

    /**
     * @brief Set the Vehicle Size object
     * 
     * @param new_vehicle_size_ 
     */
    void setVehicleSize(uint8_t new_vehicle_size_);

    /**
     * @brief Set the Inner object
     * 
     * @param new_inner_ 
     */
    void setInner(uint8_t new_inner_);

    /**
     * @brief Set the Measurment Error Cm object
     * 
     * @param new_measurment_error_cm_ 
     */
    void setMeasurmentErrorCm(uint8_t new_measurment_error_cm_);

private:

    /**
     * @brief Set the Node Id object
     * 
     * @param node_id_ 
     */
    void setNodeId(uint8_t node_id_);

    /**
     * @brief 
     * 
     * @param cartesian_x_y_point_ 
     */
    void setXYPoint(cv::Point2d cartesian_x_y_point_); // to call after chanignPosition()

    /**
     * @brief 
     * 
     */
    void setXAxisPoint(); // helper function to the setAxisPoints

    /**
     * @brief 
     * 
     */
    void setYAxisPoint(); // helper function to the setAxisPoints

    /**
     * @brief Set the Axis Points object
     * 
     */
    void setAxisPoints(); // to call after changix position()

    /**
     * @brief Set the Theta Rotation Degrees object
     * 
     * @param new_theta_rotation_degrees 
     */
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
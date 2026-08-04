#include <node_class.hpp>

Node::Node(uint8_t node_id_,
           cv::Point2d cartesian_x_y_point_,
           double theta_rotation_degrees_,
           uint8_t vehicle_size_,
           uint8_t inner_,
           uint8_t measurment_error_CM_,
           colorPalet node_color_palet_)
{
    this->node_id_ = node_id_;

    this->cartesian_x_y_point_ = cartesian_x_y_point_;
    this->cartesian_x_axis_point_ = cv::Point2d(cartesian_x_y_point_.x + 100, cartesian_x_y_point_.y);
    this->cartesian_y_axis_point_ = cv::Point2d(cartesian_x_y_point_.x, cartesian_x_y_point_.y + 100);

    this->theta_rotation_degrees_ = theta_rotation_degrees_;

    this->vehicle_size_ = vehicle_size_;
    this->inner_ = inner_;
    this->measurment_error_CM_ = measurment_error_CM_;

    this->node_color_palet_ = node_color_palet_;
}

uint8_t Node::getNodeId() const
{
    return this->node_id_;
}

cv::Point2d Node::getXYPoint() const
{
    return this->cartesian_x_y_point_;
}

cv::Point2d Node::getXAxisPoint() const
{
    return this->cartesian_x_axis_point_;
}

cv::Point2d Node::getYAxisPoint() const
{
    return this->cartesian_y_axis_point_;
}

uint8_t Node::getVehicleSize() const
{
    return this->vehicle_size_;
}

uint8_t Node::getInner() const
{
    return this->inner_;
}

uint8_t Node::getMeasurmentError() const
{
    return this->measurment_error_CM_;
}

void setNodeId(uint8_t node_id_)
{
}

void setXYPoint(cv::Point2d cartesian_x_y_point_)
{
}

void setXAxisPoint(cv::Point2d cartesian_x_axis_point_)
{
}

void setYAxisPoint(cv::Point2d cartesian_y_axis_point_)
{
}

// void setActiveState()
// {
// }

void getThetaRotationDegrees()
{
}

void Node::setVehicleSize(uint8_t new_vehicle_size_)
{
    this->vehicle_size_ = new_vehicle_size_;
}

void Node::setInner(uint8_t new_inner_)
{
    this->inner_ = new_inner_;
}

void Node::setMeasurmentError(uint8_t new_measurment_error_CM_)
{
    this->measurment_error_CM_ = new_measurment_error_CM_;
}

void Node::changeThetaRotationDegrees(double new_theta_rotation_degrees_)
{
    double remainder = this->theta_rotation_degrees_ + new_theta_rotation_degrees_;
    remainder = std::fmod(remainder, 360.00f);
    if (remainder >= 180)
    {
        remainder -= 360;
    }
    if (remainder < -180)
    {
        remainder += 360;
    }
    this->theta_rotation_degrees_ = remainder;
}

void Node::assignColors(colorPalet color_palet)
{
    color_palet.vehicle_color[0] = 35;
    color_palet.vehicle_color[1] = 75;
    color_palet.vehicle_color[2] = 0;

    color_palet.inner__color[0] = 0;
    color_palet.inner__color[1] = 100;
    color_palet.inner__color[2] = 0;

    color_palet.measurment_error_color[0] = 0;
    color_palet.measurment_error_color[1] = 114;
    color_palet.measurment_error_color[2] = 0;

    color_palet.observer_line_color[0] = 0;
    color_palet.observer_line_color[1] = 128;
    color_palet.observer_line_color[2] = 0;

    color_palet.text_color[0] = 0;
    color_palet.text_color[1] = 176;
    color_palet.text_color[2] = 56;
}

void Node::changePosition(cv::Point2d new_cartesian_x_y_point_)
{
    cv::Point2d cartesian_x_y_delta_point(new_cartesian_x_y_point_.x - this->cartesian_x_y_point_.x,
                                          new_cartesian_x_y_point_.y - this->cartesian_x_y_point_.y);

    this->cartesian_x_y_point_ = new_cartesian_x_y_point_;

    changeAxisPoints();
}

void Node::changeAxisPoints()
{
}

#include <node_class.hpp>

Node::Node(uint8_t node_id, cv::Point2d cartesian_x_y_point,
           double theta_rotation_degrees,
           double vehicle_size_,
           double inner_,
           double measurment_error_CM_,
           colorPalet nodeColorPalet)
{
    this->node_id = node_id;

    this->cartesian_x_y_point = cartesian_x_y_point;
    this->cartesian_x_axis_point = cv::Point2d(cartesian_x_y_point.x + 100, cartesian_x_y_point.y);
    this->cartesian_y_axis_point = cv::Point2d(cartesian_x_y_point.x, cartesian_x_y_point.y + 100);

    this->theta_rotation_degrees = theta_rotation_degrees;

    this->vehicle_size_ = vehicle_size_;
    this->inner_ = inner_;
    this->measurment_error_CM_ = measurment_error_CM_;

    this->nodeColorPalet = nodeColorPalet;
}

uint8_t Node::getNodeId()
{
    return this->node_id_;
}

cv::Point2d Node::getXYPoint()
{
    return this->cartesian_x_y_point_;
}

cv::Point2d Node::getXAxisPoint()
{
    return this->cartesian_x_axis_point_;
}

cv::Point2d Node::getYAxisPoint()
{
    return this->cartesian_y_axis_point_;
}

double Node::getVehicleSize()
{
    return this->vehicle_size_;
}

double Node::getInner()
{
    return this->inner_;
}

double Node::getMeasurmentError()
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

void getThetaRotationDegrees(double theta_rotation_degrees_)
{
}

void Node::setVehicleSize(double new_vehicle_size_)
{
    this->vehicle_size_ = new_vehicle_size_;
}

void Node::setInner(double new_inner_)
{
    this->inner_ = new_inner_;
}

void Node::setMeasurmentError(double new_measurment_error_CM_)
{
    this->measurment_error_CM_ = new_measurment_error_CM_;
}

void Node::changeThetaRotationDegrees(double new_theta_rotation_degrees)
{
    double remainder = this->theta_rotation_degrees + new_theta_rotation_degrees;
    remainder = std::fmod(remainder, 360.00f);
    if (remainder >= 180)
    {
        remainder -= 360;
    }
    if (remainder < -180)
    {
        remainder += 360;
    }
    this->theta_rotation_degrees = remainder;
}

void Node::assingColors()
{
    nodeColorPalet.vehicle_color[0] = 35;
    nodeColorPalet.vehicle_color[1] = 75;
    nodeColorPalet.vehicle_color[2] = 0;

    nodeColorPalet.inner__color[0] = 0;
    nodeColorPalet.inner__color[1] = 100;
    nodeColorPalet.inner__color[2] = 0;

    nodeColorPalet.measurment_error_color[0] = 0;
    nodeColorPalet.measurment_error_color[1] = 114;
    nodeColorPalet.measurment_error_color[2] = 0;

    nodeColorPalet.observer_line_color[0] = 0;
    nodeColorPalet.observer_line_color[1] = 128;
    nodeColorPalet.observer_line_color[2] = 0;

    nodeColorPalet.text_color[0] = 0;
    nodeColorPalet.text_color[1] = 176;
    nodeColorPalet.text_color[2] = 56;
}

void Node::changePosition(cv::Point2d new_cartesian_x_y_point)
{
    cv::Point2d cartesian_x_y_delta_point(new_cartesian_x_y_point.x - this->cartesian_x_y_point.x,
                                          new_cartesian_x_y_point.y - this->cartesian_x_y_point.y);

    this->cartesian_x_y_point = new_cartesian_x_y_point;

    changeAxisPoints(cartesian_x_y_delta_point);
}

void Node::changeAxisPoints(cv::Point2d new_cartesian_x_y_point)
{
    this->cartesian_y_axis_point.x = cartesian_y_axis_point.x + new_cartesian_x_y_point.x;
    this->cartesian_y_axis_point.y = cartesian_y_axis_point.y + new_cartesian_x_y_point.y;
    this->cartesian_x_axis_point.x = cartesian_x_axis_point.x + new_cartesian_x_y_point.x;
    this->cartesian_x_axis_point.y = cartesian_x_axis_point.y + new_cartesian_x_y_point.y;
}

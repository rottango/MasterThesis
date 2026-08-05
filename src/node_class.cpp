#include <node_class.hpp>
#include <reusable_calculations.hpp>

Node::Node(uint8_t node_id_,
           cv::Point2d cartesian_x_y_point_,
           double theta_rotation_degrees_,
           uint8_t vehicle_size_,
           uint8_t inner_,
           uint8_t measurment_error_cm_,
           colorPalet node_color_palet_)
{
    this->node_id_ = node_id_; // will not change ever.
    setThetaRotationDegrees(theta_rotation_degrees_);
    setXYPoint(cartesian_x_y_point_);
    setVehicleSize(vehicle_size_);
    setInner(inner_);
    setMeasurmentErrorCm(measurment_error_cm_);
    assignColors(node_color_palet_);
}

uint8_t Node::getNodeId() const // done
{
    return this->node_id_;
}

cv::Point2d Node::getXYPoint() const // done
{
    return this->cartesian_x_y_point_;
}

cv::Point2d Node::getXAxisPoint() const // done
{
    return this->cartesian_x_axis_point_;
}

cv::Point2d Node::getYAxisPoint() const // done
{
    return this->cartesian_y_axis_point_;
}

uint8_t Node::getVehicleSize() const // done
{
    return this->vehicle_size_;
}

uint8_t Node::getInner() const // done
{
    return this->inner_;
}

uint8_t Node::getMeasurmentError() const // done
{
    return this->measurment_error_cm_;
}

double Node::getThetaRotationDegrees() const // done
{
    return this->theta_rotation_degrees_;
}

void Node::changePosition(cv::Point2d new_cartesian_x_y_point_) // done
{
    setXYPoint(new_cartesian_x_y_point_);
}

void Node::rotateNodesAxis(double theta_rotation_delta_degrees) // add a rotation delta
{
    // add logic to modify that dleta to and absolute angle
    double new_theta_rotation_degrees =
        this->theta_rotation_degrees_ +
        theta_rotation_delta_degrees;

    setThetaRotationDegrees(new_theta_rotation_degrees);
}

void Node::assignColors(colorPalet node_color_palet) // done
{
    this->node_color_palet_ = node_color_palet;
}

void Node::setVehicleSize(uint8_t new_vehicle_size_) // done
{
    this->vehicle_size_ = new_vehicle_size_;
}

void Node::setInner(uint8_t new_inner_) // done
{
    this->inner_ = new_inner_;
}

void Node::setMeasurmentErrorCm(uint8_t new_measurment_error_cm_) // done
{
    this->measurment_error_cm_ = new_measurment_error_cm_;
}

void Node::setXYPoint(cv::Point2d cartesian_x_y_point_) // done
{
    this->cartesian_x_y_point_ = cartesian_x_y_point_;
    setAxisPoints();
}

void Node::setXAxisPoint() // done
{
    cv::Point2d new_cartesian_x_axis_point = calculatePointFromCenter(this->cartesian_x_y_point_,
                                                                      this->theta_rotation_degrees_,
                                                                      100);
    this->cartesian_x_axis_point_ = new_cartesian_x_axis_point;
}

void Node::setYAxisPoint() // done
{
    cv::Point2d new_cartesian_y_axis_point = calculatePointFromCenter(this->cartesian_x_y_point_,
                                                                      this->theta_rotation_degrees_ + 90,
                                                                      100);
    this->cartesian_y_axis_point_ = new_cartesian_y_axis_point;
}

void Node::setAxisPoints() // done
{
    setXAxisPoint();
    setYAxisPoint();
}

void Node::setThetaRotationDegrees(double new_theta_rotation_degrees_) // not touching, was working before - // set an aboslute angle
{
    this->theta_rotation_degrees_ = normalizeAngleDegrees(new_theta_rotation_degrees_);

    setAxisPoints();
}

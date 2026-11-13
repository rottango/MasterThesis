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
    this->node_id_ = node_id_; 
    setThetaRotationDegrees(theta_rotation_degrees_);
    setXYPoint(cartesian_x_y_point_);
    setVehicleSize(vehicle_size_);
    setInner(inner_);
    setMeasurmentErrorCm(measurment_error_cm_);
    assignColors(node_color_palet_);
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
    return this->measurment_error_cm_;
}

const colorPalet &Node::getColorPalet() const
{
    return this->node_color_palet_;
}

double Node::getThetaRotationDegrees() const 
{
    return this->theta_rotation_degrees_;
}

void Node::changePosition(cv::Point2d new_cartesian_x_y_point_) 
{
    setXYPoint(new_cartesian_x_y_point_);
}

void Node::rotateNodesAxis(double theta_rotation_delta_degrees) 
{
    // add logic to modify that delta to and absolute angle
    double new_theta_rotation_degrees =
        this->theta_rotation_degrees_ +
        theta_rotation_delta_degrees;

    setThetaRotationDegrees(new_theta_rotation_degrees);
}

void Node::assignColors(colorPalet node_color_palet) 
{
    this->node_color_palet_ = node_color_palet;
}

void Node::setVehicleSize(uint8_t new_vehicle_size_) 
{
    this->vehicle_size_ = new_vehicle_size_;
}

void Node::setInner(uint8_t new_inner_) 
{
    this->inner_ = new_inner_;
}

void Node::setMeasurmentErrorCm(uint8_t new_measurment_error_cm_) 
{
    this->measurment_error_cm_ = new_measurment_error_cm_;
}

void Node::setXYPoint(cv::Point2d cartesian_x_y_point_) 
{
    this->cartesian_x_y_point_ = cartesian_x_y_point_;
    setAxisPoints();
}

void Node::setXAxisPoint() 
{
    cv::Point2d new_cartesian_x_axis_point = calculatePointFromCenter(this->cartesian_x_y_point_,
                                                                      this->theta_rotation_degrees_,
                                                                      100);
    this->cartesian_x_axis_point_ = new_cartesian_x_axis_point;
}

void Node::setYAxisPoint() 
{
    cv::Point2d new_cartesian_y_axis_point = calculatePointFromCenter(this->cartesian_x_y_point_,
                                                                      this->theta_rotation_degrees_ + 90,
                                                                      100);
    this->cartesian_y_axis_point_ = new_cartesian_y_axis_point;
}

void Node::setAxisPoints() 
{
    setXAxisPoint();
    setYAxisPoint();
}

void Node::setThetaRotationDegrees(double new_theta_rotation_degrees_) 
{
    this->theta_rotation_degrees_ = normalizeAngleDegrees(new_theta_rotation_degrees_);

    setAxisPoints();
}


#include <calculate.hpp>
#include <node_class.hpp>

Node::Node(cv::Point2d cartesian_x_y_point,
           double theta_rotation_degrees,
           double vehicle_size,
           double inner,
           double measurment_error_CM,
           colorPalet newUgvColorPalet)
{
    this->cartesian_x_y_point = cartesian_x_y_point;
    this->cartesian_x_axis_point = cv::Point2d(cartesian_x_y_point.x + 100, cartesian_x_y_point.y);
    this->cartesian_y_axis_point = cv::Point2d(cartesian_x_y_point.x, cartesian_x_y_point.y + 100);

    this->theta_rotation_degrees = theta_rotation_degrees;

    this->vehicle_size = vehicle_size;
    this->inner = inner;
    this->measurment_error_CM = measurment_error_CM;

    this->ugvColorPalet = newUgvColorPalet;
}

void Node::change_theta_rotation_degrees(double new_theta_rotation_degrees)
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
    ugvColorPalet.vehicle_color[0] = 35;
    ugvColorPalet.vehicle_color[1] = 75;
    ugvColorPalet.vehicle_color[2] = 0;

    ugvColorPalet.inner_color[0] = 0;
    ugvColorPalet.inner_color[1] = 100;
    ugvColorPalet.inner_color[2] = 0;

    ugvColorPalet.measurment_error_color[0] = 0;
    ugvColorPalet.measurment_error_color[1] = 114;
    ugvColorPalet.measurment_error_color[2] = 0;

    ugvColorPalet.observer_line_color[0] = 0;
    ugvColorPalet.observer_line_color[1] = 128;
    ugvColorPalet.observer_line_color[2] = 0;

    ugvColorPalet.text_color[0] = 0;
    ugvColorPalet.text_color[1] = 176;
    ugvColorPalet.text_color[2] = 56;
}

void Node::openCVCartesianCalculateAngle(cv::Point2d new_cartesian_x_y_point)
{
    cv::Point2d opencv_x_y_delta_point(new_cartesian_x_y_point.x - this->cartesian_x_y_point.x,
                                       new_cartesian_x_y_point.y - this->cartesian_x_y_point.y);
    this->cartesian_x_y_point = new_cartesian_x_y_point;

    changeAxisPoints(opencv_x_y_delta_point);
}

void Node::changeAxisPoints(cv::Point2d new_cartesian_x_y_point)
{
    this->cartesian_y_axis_point.x = cartesian_y_axis_point.x + new_cartesian_x_y_point.x;
    this->cartesian_y_axis_point.y = cartesian_y_axis_point.y + new_cartesian_x_y_point.y;
    this->cartesian_x_axis_point.x = cartesian_x_axis_point.x + new_cartesian_x_y_point.x;
    this->cartesian_x_axis_point.y = cartesian_x_axis_point.y + new_cartesian_x_y_point.y;
}

void Node::setVehicleSize(double new_vehicle_size)
{
    this->vehicle_size = new_vehicle_size;
}

void Node::setInner(double new_inner)
{
    this->inner = new_inner;
}

void Node::setMeasurmentError(double new_measurment_error_CM)
{
    this->measurment_error_CM = new_measurment_error_CM;
}

double Node::getVehicleSize()
{
    return this->vehicle_size;
}

double Node::getInner()
{
    return this->inner;
}

double Node::getMeasurmentError()
{
    return this->measurment_error_CM;
}

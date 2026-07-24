
#include <calculate.hpp>
#include <node_class.hpp>

Node::Node(cv::Point2d opencv_x_y_point,
           double opencv_z_position,
           double theta_rotation,
           double vehicle_size,
           double inner,
           double measurment_error_CM,
           colorPalet newUgvColorPalet)
{
    this->opencv_x_y_point = opencv_x_y_point;
    this->opencv_z_position = opencv_z_position;

    this->opencv_x_y_point = openCVPointToCartesianPoint(opencv_x_y_point, cv::Point2d(1920 / 2, 1080 / 2));

    this->theta_rotation = theta_rotation;

    this->vehicle_size = vehicle_size;
    this->inner = inner;
    this->measurment_error_CM = measurment_error_CM;

    this->x_axis_point = openCVPointToCartesianPoint(cv::Point2d(opencv_x_y_point.x + 100, opencv_x_y_point.y), cv::Point2d(1920 / 2, 1080 / 2));
    this->y_axis_point = openCVPointToCartesianPoint(cv::Point2d(opencv_x_y_point.x, opencv_x_y_point.y + 100), cv::Point2d(1920 / 2, 1080 / 2));

    this->ugvColorPalet = newUgvColorPalet;
}

void Node::changeThetaRotation(double new_theta_rotation)
{
    double remainder = std::fmod(this->theta_rotation + new_theta_rotation, 360.00f);
    if (remainder < 0)
    {
        this->theta_rotation = remainder + 360;
    }
    else
    {
        this->theta_rotation = remainder;
    }
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

void Node::changePositionXYZ(cv::Point2d new_opencv_x_y_point,
                             double new_opencv_z_position)
{
    cv::Point2d opencv_x_y_delta_point(new_opencv_x_y_point.x - this->opencv_x_y_point.x,
                                       new_opencv_x_y_point.y - this->opencv_x_y_point.y);
    double z_delta = new_opencv_z_position - this->opencv_z_position;
    this->opencv_x_y_point = new_opencv_x_y_point;
    this->cartesian_x_y_point = openCVPointToCartesianPoint(opencv_x_y_point, cv::Point2d(1920 / 2, 1080 / 2));

    this->opencv_z_position = new_opencv_z_position;

    changeAxisPoints(opencv_x_y_delta_point, z_delta);
}

void Node::changeAxisPoints(cv::Point2d new_opencv_x_y_point,
                            double new_opencv_z_position)
{
    this->y_axis_point.x = y_axis_point.x + new_opencv_x_y_point.x;
    this->y_axis_point.y = y_axis_point.y + new_opencv_x_y_point.y;
    this->x_axis_point.x = x_axis_point.x + new_opencv_x_y_point.x;
    this->x_axis_point.y = x_axis_point.y + new_opencv_x_y_point.y;
}

void Node::drawNode(cv::Mat img)
{
    cv::circle(img, cv::Point2d(this->opencv_x_y_point.x, this->opencv_x_y_point.y), this->vehicle_size, this->ugvColorPalet.vehicle_color, cv::FILLED, 8, 0);
    cv::circle(img, cv::Point2d(this->opencv_x_y_point.x, this->opencv_x_y_point.y), this->inner, this->ugvColorPalet.inner_color, 2, 8, 0);
    cv::circle(img, cv::Point2d(this->opencv_x_y_point.x, this->opencv_x_y_point.y), this->measurment_error_CM, this->ugvColorPalet.measurment_error_color, 2, 8, 0);
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

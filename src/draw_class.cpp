
#include <draw_class.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

Draw::Draw(const Graph &graph,
           cv::Mat &img) : graph_(graph), img_(img)
{
    this->screen_width_ = img_.cols;
    this->screen_height_ = img_.rows;
    this->size_ = img_.size();
    this->type_ = img_.type();
}

// frame

void Draw::drawFrame()
{
    drawGraph();
}

// graph

void Draw::drawGraph()
{
    drawNodes();

    drawEdges();

    drawTextOnScreen();
}
// node

void Draw::drawNodes()
{
    for (auto it = graph_.getNodes().begin(); it != graph_.getNodes().end(); it++)
    {
        drawNode(it->second);
    }
}

void Draw::drawNode(const Node &node)
{
    drawNodeVehicleSize(node);
    drawNodeInner(node);
    drawNodeMeasurmentError(node);
    drawNodeAxis(node);
}

void Draw::drawNodeVehicleSize(const Node &node)
{
    cv::circle(this->img_,
               cartesianPointToOpenCVPoint(node.getXYPoint(),
                                           screen_width_,
                                           screen_height_),
               node.getVehicleSize(),
               node.getColorPalet().vehicle_color,
               node.getColorPalet().thickness,
               node.getColorPalet().lineType,
               node.getColorPalet().shift);
}

void Draw::drawNodeAxis(const Node &node)
{
    cv::arrowedLine(img_,
                    cartesianPointToOpenCVPoint(node.getXYPoint(),
                                                screen_width_,
                                                screen_height_),
                    cartesianPointToOpenCVPoint(node.getXAxisPoint(),
                                                screen_width_,
                                                screen_height_),
                    x_axis_color_,
                    axis_arrow_thickness_);

    cv::arrowedLine(img_,
                    cartesianPointToOpenCVPoint(node.getXYPoint(),
                                                screen_width_,
                                                screen_height_),
                    cartesianPointToOpenCVPoint(node.getYAxisPoint(),
                                                screen_width_,
                                                screen_height_),
                    y_axis_color_,
                    axis_arrow_thickness_);
}

void Draw::drawNodeMeasurmentError(const Node &node)
{
    cv::circle(this->img_,
               cartesianPointToOpenCVPoint(node.getXYPoint(),
                                           screen_width_,
                                           screen_height_),
               node.getMeasurmentError(),
               node.getColorPalet().measurment_error_color,
               node.getColorPalet().thickness,
               node.getColorPalet().lineType,
               node.getColorPalet().shift);
}

void Draw::drawNodeInner(const Node &node)
{
    cv::circle(this->img_,
               cartesianPointToOpenCVPoint(node.getXYPoint(),
                                           screen_width_,
                                           screen_height_),
               node.getInner(),
               node.getColorPalet().inner__color,
               node.getColorPalet().thickness,
               node.getColorPalet().lineType,
               node.getColorPalet().shift);
}

// edge

void Draw::drawEdges()
{

    for (auto it = graph_.getEdges().begin(); it != graph_.getEdges().end(); it++)
    {
        drawEdge(it->second);
        drawAngleElipse(it->second);
    }
}

void Draw::drawEdge(const Edge &edge)
{
}

void Draw::drawAngleElipse(const Edge &edge)
{
    // example use case for different observer -> target realtions for one node
    do
    {
        drawAngleElipseToTarget(edge);
    } while (true);
}

void Draw::drawAngleElipseToTarget(const Edge &edge)
{
    Node observer = graph_.findNodeById().getXYPoint();
    double angle = 0;
    double start_angle = -observer.theta_rotation_degrees;
    double end_angle = start_angle - observer.angle_output_atan2_to_target;
    cv::Scalar color = observer.ugvColorPalet.text_color;
    bool invert = 0;

    cv::ellipse(img,                                                       // cv::InputOutputArray img,
                cartesianPointToOpenCVPoint(observer.cartesian_x_y_point), // cv::Point center
                cv::Size2d(100, 100),                                      // cv::Size axes
                angle,                                                     // double angle STAYS 0, then its like i want it to be
                start_angle,                                               // double startAngle
                end_angle,                                                 // double endAngle
                observer.ugvColorPalet.text_color,                         // const cv::Scalar &color
                1,                                                         // int thickness
                8,                                                         // int lineType = 8
                0);                                                        // int shift = 0
    std::cout << "end_angle: " << end_angle << "\n";
}

// text

void Draw::drawTextOnScreen() {}

void Draw::generateText()
{
}

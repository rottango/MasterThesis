
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

void Draw::drawEdges() // correct
{

    for (auto it = graph_.getEdges().begin(); it != graph_.getEdges().end(); it++)
    {
        drawEdge(it->second);
    }
}

void Draw::drawEdge(const Edge &edge)
{
    drawEdgeConnectingLine(edge);
    drawEdgeAngleElipseToTarget(edge);
}

void Draw::drawEdgeConnectingLine(const Edge &edge)
{
    const Node &observer = graph_.findNodeById(edge.getObserverId());
    const Node &target = graph_.findNodeById(edge.getTargetId());
    cv::arrowedLine(img_,
                    cartesianPointToOpenCVPoint(observer.getXYPoint(),
                                                screen_width_,
                                                screen_height_),
                    cartesianPointToOpenCVPoint(target.getXYPoint(),
                                                screen_width_,
                                                screen_height_),
                    observer.getColorPalet().text_color,
                    axis_arrow_thickness_);
}

void Draw::drawEdgeAngleElipseToTarget(const Edge &edge)
{
    const Node &observer = graph_.findNodeById(edge.getObserverId());
    double angle = 0;
    double start_angle = -observer.getThetaRotationDegrees();
    double end_angle = start_angle - edge.getAngleBetweenNodesDegrees();

    cv::ellipse(img_, // cv::InputOutputArray img,
                cartesianPointToOpenCVPoint(observer.getXYPoint(),
                                            screen_width_,
                                            screen_height_), // cv::Point center
                cv::Size2d(angle_elipse_size_,
                           angle_elipse_size_),      // cv::Size axes
                angle,                               // double angle STAYS 0, then its like i want it to be
                start_angle,                         // double startAngle
                end_angle,                           // double endAngle
                observer.getColorPalet().text_color, // const cv::Scalar &color
                1,                                   // int thickness
                8,                                   // int lineType = 8
                0);                                  // int shift = 0
    std::cout << "end_angle: " << end_angle << "\n";
}

// text

void Draw::drawTextOnScreen()
{
}

void Draw::generateText() // use getTextSize()
{
    std::string node_id_text = "Node ID: ";
}

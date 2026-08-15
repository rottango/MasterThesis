
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

    /// drawText();
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
    std::unordered_map<uint8_t, uint8_t> number_of_elipses_per_observer_id;
    for (auto it = graph_.getEdges().begin(); it != graph_.getEdges().end(); it++)
    {
        uint8_t observer_id = it->second.getObserverId();
        uint8_t &counter = number_of_elipses_per_observer_id[observer_id];
        int radius = base_angle_elipse_size_ + counter * base_angle_elipse_spacing_;
        drawEdge(it->second, radius);
        counter++;
    }
}

void Draw::drawEdge(const Edge &edge, int radius)
{
    drawEdgeConnectingLine(edge);
    drawEdgeAngleElipseToTarget(edge, radius);
}

void Draw::drawEdgeConnectingLine(const Edge &edge)
{
    const Node &observer = graph_.findNodeByIdReadOnly(edge.getObserverId());
    const Node &target = graph_.findNodeByIdReadOnly(edge.getTargetId());
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

void Draw::drawEdgeAngleElipseToTarget(const Edge &edge, int radius)
{
    const Node &observer = graph_.findNodeByIdReadOnly(edge.getObserverId());
    double angle = 0;
    double start_angle = -observer.getThetaRotationDegrees();
    double end_angle = start_angle - edge.getAngleBetweenNodesDegrees();

    cv::ellipse(img_, // cv::InputOutputArray img,
                cartesianPointToOpenCVPoint(observer.getXYPoint(),
                                            screen_width_,
                                            screen_height_), // cv::Point center
                cv::Size2d(radius,
                           radius),                  // cv::Size axes
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

void Draw::drawText()
{
    generateText();

    // layoutGeneratedText();
}

void Draw::generateText()
{
    generateNodesText();
    generateEdgesText();
}

void Draw::generateNodesText()
{
    for (auto it = graph_.getNodes().begin(); it != graph_.getNodes().end(); it++)
    {
        generateNodeText(it->second);
    }
}

void Draw::generateNodeText(const Node &node)
{

    generated_text_node.clear();

    generated_text_node.push_back(node_id_text_ + std::to_string(node.getNodeId()));
    generated_text_node.push_back(cartesian_x_y_point_text_ + "(" + std::to_string(node.getXYPoint().x) +
                                  "," + std::to_string(node.getXYPoint().y) + ")");
    generated_text_node.push_back(vehicle_size_text_ + std::to_string(node.getVehicleSize()));
    generated_text_node.push_back(inner_text_ + std::to_string(node.getInner()));
    generated_text_node.push_back(measurment_error_cm_text_ + std::to_string(node.getMeasurmentError()));
    generated_text_node.push_back(theta_rotation_degrees_text_ + std::to_string(node.getThetaRotationDegrees()));
}

void Draw::generateEdgesText()
{
    for (auto it = graph_.getEdges().begin(); it != graph_.getEdges().end(); it++)
    {
        generateEdgeText(it->second);
    }
}

void Draw::generateEdgeText(const Edge &edge)
{

    generated_text_edge.clear();

    generated_text_edge.push_back(edge_id_ + std::to_string(edge.getEdgeId()));
    generated_text_edge.push_back(observer_id + std::to_string(edge.getObserverId()));
    generated_text_edge.push_back(target_id_ + std::to_string(edge.getTargetId()));
    generated_text_edge.push_back(distance_between_nodes_meters_ + std::to_string(edge.getDistanceBetweenNodesMeters()));
    generated_text_edge.push_back(angle_between_nodes_degrees_ + std::to_string(edge.getAngleBetweenNodesDegrees()));
    generated_text_edge.push_back(temp_timestamp_ + std::to_string(edge.getTempTimestamp()));
    generated_text_edge.push_back(distance_between_nodes_meters_error_ + std::to_string(edge.getDistanceBetweenNodesMetersError()));
    generated_text_edge.push_back(angle_between_nodes_degrees_error_ + std::to_string(edge.getAngleBetweenNodesDegreesError()));
}

void Draw::layoutGeneratedText(const Node &node, const Edge &edge)
{
    // i did it kinda wrong, because this is the rectangle that would contain all the info of all the nodes,
    // so i actually need to just get a node or an edge passed that i want to render, and measure its stuff.
    // so i kinda need to rewrite this shi ;/
    // 69

    int node_info_rectangle_width_ = 0;
    int node_info_rectangle_height_ = 0;
    int edge_info_rectangle_width_ = 0;
    int edge_info_rectangle_height_ = 0;

    int gap_size_pixels = 5;
    int edge_text_gap;
    int node_text_gap;
    if (generated_text_edge.size() < 1)
    {
        edge_text_gap = 0;
    }
    else
    {
        edge_text_gap = (generated_text_edge.size() - 1) * gap_size_pixels;
    }

    if (generated_text_node.size() < 1)
    {
        node_text_gap = 0;
    }
    else
    {
        node_text_gap = (generated_text_node.size() - 1) * gap_size_pixels;
    }

    // calculate the rectangle of the node
    for (auto it = generated_text_node.begin(); it != generated_text_node.end(); it++)
    {
        cv::Size text_size = cv::getTextSize(*it,
                                             font_face_,
                                             font_scale_,
                                             font_thickness_,
                                             baseline_);
        if (text_size.width > node_info_rectangle_width_)
        {
            node_info_rectangle_width_ = text_size.width;
        }
        node_info_rectangle_height_ += text_size.height;
    }
    // calculate the rectangle of the edge
    for (auto it = generated_text_edge.begin(); it != generated_text_edge.end(); it++)
    {
        cv::Size text_size = cv::getTextSize(*it,
                                             font_face_,
                                             font_scale_,
                                             font_thickness_,
                                             baseline_);
        if (text_size.width > edge_info_rectangle_width_)
        {
            edge_info_rectangle_width_ = text_size.width;
        }
        edge_info_rectangle_height_ += text_size.height;
    }
}

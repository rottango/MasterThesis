#pragma once

#include <graph_class.hpp>
#include <opencv2/opencv.hpp>
#include <reusable_calculations.hpp>

class Draw
{
public:
    Draw(const Graph &Graph,
         cv::Mat &img);

    // frame

    void drawFrame();

private:
    // graph

    void
    drawGraph();

    // node

    void drawNodes();

    void drawNode(const Node &node);

    void drawNodeVehicleSize(const Node &node) {}

    void drawNodeAxis(const Node &node);

    void drawNodeMeasurmentError(const Node &node);

    void drawNodeInner(const Node &node);

    // edge

    void drawEdges();

    void drawEdge(const Edge &edge); // this is the same as drawConnectingLine i believe

    void drawEdgeConnectingLine(const Edge &edge);

    void drawEdgeAngleElipse(const Edge &edge); // every edge from observer to targets are drawn

    void drawEdgeAngleElipseToTarget(const Edge &edge); // single edge from observer to target is drawn

    // text

    void drawText();

    void generateText();

    void generateNodesText();

    void generateNodeText(const Node &node);

    void generateEdgesText();

    void generateEdgeText(const Edge &edge);

    void layoutGeneratedText(const Node &node, const Edge &edge);

    const Graph &graph_;
    cv::Mat &img_;

    int screen_width_;
    int screen_height_;
    cv::Size size_;
    int type_;

    cv::Scalar x_axis_color_{(0, 0, 255)};
    cv::Scalar y_axis_color_{(255, 0, 0)};
    int axis_arrow_thickness_ = 5;
    int angle_elipse_size_ = 100;

    int font_face_;
    double font_scale_;
    int font_thickness_;
    int *baseline_;

    std::vector<std::string> generated_text_node;
    std::vector<std::string> generated_text_edge;

    // node
    std::string node_id_text_ = "Node ID: ";
    std::string cartesian_x_y_point_text_ = "Location (x,y): ";
    std::string vehicle_size_text_ = "Vehicle size: ";
    std::string inner_text_ = "Inner size: ";
    std::string measurment_error_cm_text_ = "Measurment error [cm]: ";
    std::string theta_rotation_degrees_text_ = "Theta rotation [degrees]: ";

    // edge

    std::string edge_id_ = "Edge ID: ";
    std::string observer_id = "Observer ID: ";
    std::string target_id_ = "Target ID: ";
    std::string distance_between_nodes_meters_ = "Distance [m]: ";
    std::string angle_between_nodes_degrees_ = "Angle [degrees]: ";
    std::string temp_timestamp_ = "Timestamp: ";
    std::string distance_between_nodes_meters_error_ = "Distance error [m]: ";
    std::string angle_between_nodes_degrees_error_ = "Angle error [degrees]: ";
};
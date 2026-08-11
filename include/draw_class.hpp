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

    struct GeneratedTextNode
    {
        std::string node_id_text_;
        std::string cartesian_x_y_point_text_;
        std::string vehicle_size_text_;
        std::string inner_text_;
        std::string measurment_error_cm_text_;
        std::string theta_rotation_degrees_text_;
    };

    struct GeneratedTextEdge
    {
        std::string edge_id_;
        std::string observer_id;
        std::string target_id_;
        std::string distance_between_nodes_meters_;
        std::string angle_between_nodes_degrees_;
        std::string temp_timestamp_;
        std::string distance_between_nodes_meters_error_;
        std::string angle_between_nodes_degrees_error_;
    };

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

    void layoutGeneratedText();

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

    std::map<uint8_t, GeneratedTextNode> nodes_generated_text;
    std::map<std::pair<uint8_t, uint8_t>, GeneratedTextEdge> edges_generated_text;
};
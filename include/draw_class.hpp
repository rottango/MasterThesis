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

    // graph

    void drawGraph();

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

    void drawConnectingLine(const Edge &edge);

    void drawAngleElipse(const Edge &edge); // every edge from observer to targets are drawn

    void drawAngleElipseToTarget(const Edge &edge); // single edge from observer to target is drawn

    // text

    void drawTextOnScreen();

    void generateText();

private:
    const Graph &graph_;
    cv::Mat &img_;

    std::unordered_map<uint8_t, Node> read_only_nodes_;
    std::map<std::pair<uint8_t, uint8_t>, Edge> read_only_edges_;

    int screen_width_;
    int screen_height_;
    cv::Size size_;
    int type_;

    cv::Scalar x_axis_color_{(0, 0, 255)};
    cv::Scalar y_axis_color_{(255, 0, 0)};
    int axis_arrow_thickness_ = 5;
};
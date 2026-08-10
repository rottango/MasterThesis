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

    void drawNode();

    void drawNodeAxis();

    void drawNodeMeasurmentError();

    void drawNodeInner();

    // edge

    void drawEdges();

    void drawConnectingLine();

    void drawAngleElipse();

    void drawAngleToTargetElipse();

    // text

    void drawTextOnScreen();

    void generateText();

private:
    const Graph &graph_;
    cv::Mat &img_;
};
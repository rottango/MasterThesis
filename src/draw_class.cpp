
#include <draw_class.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

Draw::Draw(const Graph &graph,
           cv::Mat &img)
{
    this->graph_ = graph;
    this->img_ = img;
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
    drawNodeMeasurmentError();
    drawNodeInner();
    drawNodeAxis();

    drawEdges();

    drawTextOnScreen();
}

// node

void Draw::drawNodes()
{
    // example use case for all nodes
    do
    {
        drawNode();
    } while (true);
}

void Draw::drawNode() {}

void Draw::drawNodeAxis() {}

void Draw::drawNodeMeasurmentError() {}

void Draw::drawNodeInner() {}

// edge

void Draw::drawEdges() {}

void Draw::drawConnectingLine()
{
}

void Draw::drawAngleElipse()
{
    // example use case for different observer -> target realtions for one node
    do
    {
        drawAngleToTargetElipse();
    } while (true);
}

void Draw::drawAngleToTargetElipse()
{
}

// text

void Draw::drawTextOnScreen() {}

void Draw::generateText()
{
}

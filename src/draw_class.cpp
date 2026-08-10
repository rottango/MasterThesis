
#include <draw_class.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

Draw::Draw(const Graph &graph,
           cv::Mat &img) : graph_(graph), img_(img)
{
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
        drawNodeMeasurmentError(it->second);
        drawNodeInner(it->second);
        drawNodeAxis(it->second);
    }
}

void Draw::drawNode(const Node &node) {}

void Draw::drawNodeAxis(const Node &node) {}

void Draw::drawNodeMeasurmentError(const Node &node) {}

void Draw::drawNodeInner(const Node &node) {}

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
}

// text

void Draw::drawTextOnScreen() {}

void Draw::generateText()
{
}

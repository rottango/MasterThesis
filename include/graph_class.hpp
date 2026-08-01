#pragma once

#include <map>
#include <unordered_map>
#include <utility>

#include <edge_class.hpp>
#include <node_class.hpp>

class Graph
{
public:
    void addNode();

    void removeNode();

    int findNode();

    void findEdge();

    void addEdge();

    void removeEdge();

private:
    void nodeIDGeneration();

    void nodeIDValidation();

    void edgeIDGeneration();

    void edgeIDValidation();

    void changeEdgeVertices();

    void removeAllVerticesEdges();

    std::unordered_map<int, Node> nodes_;
    std::map<std::pair<int, int>, Edge> edges_;
};
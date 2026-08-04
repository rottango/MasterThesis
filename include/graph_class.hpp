#pragma once

#include <map>
#include <unordered_map>
#include <utility>

#include <cstdint>
#include <edge_class.hpp>
#include <grouping_manager_class.hpp>
#include <node_class.hpp>

class Graph
{
public:
    Graph(std::unordered_map<uint8_t, Node> nodes_,
          std::map<std::pair<uint8_t, uint8_t>, Edge> edges_,
          std::unordered_map<uint8_t, GroupingManager> grouping_managers_);

    void addNode();

    void removeNode();

    void removeAllNodes();

    uint8_t findNode();

    void findEdge();

    void addEdge();

    void removeEdge();

private:
    void nodeIDGeneration();

    void nodeIDValidation();

    void edgeIDGeneration();

    void edgeIDValidation();

    void removeAllNodeEdges();

    std::unordered_map<uint8_t, Node> nodes_;
    std::map<std::pair<uint8_t, uint8_t>, Edge> edges_;
    std::unordered_map<uint8_t, GroupingManager> grouping_managers_;
};
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

    void removeNodeById();

    void removeAllNodes();

    Node findNodeById();

    bool DoesNodeExist();

    uint8_t NumerOfNodes();

    void addEdge();

    void removeEdgeById();

    void removeAlllEdges();

    Edge findEdgeById();

    bool DoesEdgeExist();

    uint8_t NumerOfEdges();

    std::unordered_map<uint8_t, Node> readOnlyNodes();

    std::map<std::pair<uint8_t, uint8_t>, Edge> readOnlyEdges();

private:
    void nodeIDGeneration();

    void nodeIDValidation();

    void edgeIDGeneration();

    void edgeIDValidation();

    void removeAllNodeEdges();

    std::unordered_map<uint8_t, Node> nodes_;
    std::map<std::pair<uint8_t, uint8_t>, Edge> edges_;
    std::unordered_map<uint8_t, GroupingManager> grouping_managers_;

    uint8_t next_node_id_;
    uint8_t next_edge_id_;
};
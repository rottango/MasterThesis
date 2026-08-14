#pragma once

#include <map>
#include <unordered_map>
#include <utility>

#include <cstdint>
#include <edge_class.hpp>
#include <group_class.hpp>
#include <grouping_manager_class.hpp>
#include <node_class.hpp>

class Graph
{
public:
    Graph();

    void addNode(cv::Point2d cartesian_x_y_point_,
                 double theta_rotation_degrees_,
                 uint8_t vehicle_size_,
                 uint8_t inner_,
                 uint8_t measurment_error_cm_,
                 colorPalet node_color_palet_);

    void removeNodeById(uint8_t node_id);

    void removeAllNodes();

    const Node &findNodeByIdReadOnly(uint8_t node_id) const;

    Node &findNodeByIdReadWrite(uint8_t node_id);

    bool doesNodeExist();

    uint8_t numerOfNodes() const;

    void addEdge(uint8_t observer_id,
                 uint8_t target_id_);

    void removeEdgeByNodeIds(std::pair<uint8_t, uint8_t> edge_pair);

    void removeAllEdges();

    const Edge &findEdgeByNodeIdsReadOnly(std::pair<uint8_t, uint8_t> edge_pair) const; // read-only reference to an existing object

    Edge &findEdgeByNodeIdsReadWrite(std::pair<uint8_t, uint8_t> edge_pair); // read-write reference to an existing object

    bool doesEdgeExist();

    uint8_t numerOfEdges() const;

    const std::unordered_map<uint8_t, Node> &getNodes() const;

    const std::map<std::pair<uint8_t, uint8_t>, Edge> &getEdges() const;

private:
    uint8_t nodeIDGeneration();

    bool nodeIDValidation(uint8_t node_id);

    uint8_t edgeIDGeneration();

    bool edgeIDValidation(uint8_t edge_id);

    std::unordered_map<uint8_t, Node> nodes_;
    std::map<std::pair<uint8_t, uint8_t>, Edge> edges_;
    std::unordered_map<uint8_t, GroupingManager> grouping_managers_;
    std::unordered_map<uint8_t, Group> groups;

    uint8_t current_node_id_ = 0;
    uint8_t current_edge_id_ = 0;
};
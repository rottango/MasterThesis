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
    Graph(std::unordered_map<uint8_t, Node> nodes_,
          std::map<std::pair<uint8_t, uint8_t>, Edge> edges_,
          std::unordered_map<uint8_t, GroupingManager> grouping_managers_,
          std::unordered_map<uint8_t, Group> groups);

    void addNode(cv::Point2d cartesian_x_y_point_,
                 double theta_rotation_degrees_,
                 uint8_t vehicle_size_,
                 uint8_t inner_,
                 uint8_t measurment_error_cm_,
                 colorPalet node_color_palet_);

    void removeNodeById();

    void removeAllNodes();

    Node findNodeById();

    bool DoesNodeExist();

    uint8_t NumerOfNodes();

    void addEdge(uint8_t edge_id,
                 uint8_t observer_id,
                 uint8_t target_id_);

    void removeEdgeById();

    void removeAlllEdges();

    Edge findEdgeById();

    bool DoesEdgeExist();

    uint8_t NumerOfEdges();

    std::unordered_map<uint8_t, Node> readOnlyNodes();

    std::map<std::pair<uint8_t, uint8_t>, Edge> readOnlyEdges();

private:
    uint8_t nodeIDGeneration();

    bool nodeIDValidation(uint8_t node_id);

    uint8_t edgeIDGeneration();

    bool edgeIDValidation(uint8_t edge_id);

    void removeAllNodeEdges();

    std::unordered_map<uint8_t, Node> nodes_;
    std::map<std::pair<uint8_t, uint8_t>, Edge> edges_;
    std::unordered_map<uint8_t, GroupingManager> grouping_managers_;
    std::unordered_map<uint8_t, Group> groups;

    uint8_t current_node_id_ = 0;
    uint8_t current_edge_id_ = 0;
};
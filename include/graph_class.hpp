#pragma once

#include <map>
#include <unordered_map>
#include <utility>

#include <cstdint>
#include <edge_class.hpp>
#include <group_class.hpp>
#include <grouping_manager_class.hpp>
#include <node_class.hpp>
#include <spdlog/spdlog.h>

class Graph
{
public:
    /**
     * @brief Construct a new Graph object
     * 
     */
    Graph();

    /**
     * @brief 
     * 
     * @param cartesian_x_y_point_ 
     * @param theta_rotation_degrees_ 
     * @param vehicle_size_ 
     * @param inner_ 
     * @param measurment_error_cm_ 
     * @param node_color_palet_ 
     * @return uint8_t 
     */
    uint8_t addNode(cv::Point2d cartesian_x_y_point_,
                    double theta_rotation_degrees_,
                    uint8_t vehicle_size_,
                    uint8_t inner_,
                    uint8_t measurment_error_cm_,
                    colorPalet node_color_palet_);

    /**
     * @brief 
     * 
     * @param node_id 
     */
    void removeNodeById(uint8_t node_id);

    /**
     * @brief 
     * 
     */
    void removeAllNodes();

    /**
     * @brief 
     * 
     * @param node_id 
     * @return const Node& 
     */
    const Node &findNodeByIdReadOnly(uint8_t node_id) const;

    /**
     * @brief 
     * 
     * @param node_id 
     * @return Node& 
     */
    Node &findNodeByIdReadWrite(uint8_t node_id);

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool doesNodeExist();

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    uint8_t numerOfNodes() const;

    /**
     * @brief 
     * 
     * @param observer_id 
     * @param target_id_ 
     * @return uint8_t 
     */
    uint8_t addEdge(uint8_t observer_id,
                    uint8_t target_id_);

    /**
     * @brief 
     * 
     * @param edge_pair 
     */
    void removeEdgeByNodeIds(std::pair<uint8_t, uint8_t> edge_pair);

    /**
     * @brief 
     * 
     */
    void removeAllEdges();

    /**
     * @brief 
     * 
     * @param edge_pair 
     * @return const Edge& 
     */
    const Edge &findEdgeByNodeIdsReadOnly(std::pair<uint8_t, uint8_t> edge_pair) const; // read-only reference to an existing object

    /**
     * @brief 
     * 
     * @param edge_pair 
     * @return Edge& 
     */
    Edge &findEdgeByNodeIdsReadWrite(std::pair<uint8_t, uint8_t> edge_pair); // read-write reference to an existing object

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool doesEdgeExist();

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    uint8_t numerOfEdges() const;

    /**
     * @brief Get the Nodes object
     * 
     * @return const std::unordered_map<uint8_t, Node>& 
     */
    const std::unordered_map<uint8_t, Node> &getNodes() const;

    /**
     * @brief Get the Edges object
     * 
     * @return const std::map<std::pair<uint8_t, uint8_t>, Edge>& 
     */
    const std::map<std::pair<uint8_t, uint8_t>, Edge> &getEdges() const;

    /**
     * @brief 
     * 
     */
    void updateNodesAndEdges();

private:
    
    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    uint8_t nodeIDGeneration();

    /**
     * @brief 
     * 
     * @param node_id 
     * @return true 
     * @return false 
     */
    bool isNodeIDValid(uint8_t node_id);

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    uint8_t edgeIDGeneration();

    /**
     * @brief 
     * 
     * @param edge_id 
     * @return true 
     * @return false 
     */
    bool isEdgeIDValid(uint8_t edge_id);

    /**
     * @brief   
     * 
     */
    void updateAllEdges();

    /**
     * @brief 
     * 
     * @param edge_id 
     * @param observer_id 
     * @param target_id_ 
     */
    void updateEdge(uint8_t edge_id,
                    uint8_t observer_id,
                    uint8_t target_id_);

    std::unordered_map<uint8_t, Node> nodes_;
    std::map<std::pair<uint8_t, uint8_t>, Edge> edges_;
    std::unordered_map<uint8_t, GroupingManager> grouping_managers_;
    std::unordered_map<uint8_t, Group> groups;

    uint8_t current_node_id_ = 0;
    uint8_t current_edge_id_ = 0;
};
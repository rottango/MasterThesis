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
     * @brief Add a node to the graph, giving it a unique node id
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
     * @brief Remove a node from the graph based on the node id
     * 
     * @param node_id 
     */
    void removeNodeById(uint8_t node_id);

    /**
     * @brief Remove all nodes from a graph
     * 
     */
    void removeAllNodes();

    /**
     * @brief Return a non modifiable read-only reference to a node object based on the node id  
     * 
     * @param node_id 
     * @return const Node& 
     */
    const Node &findNodeByIdReadOnly(uint8_t node_id) const;

    /**
     * @brief Return a modifiable read-write reference of a node object  based on the node id  
     * 
     * @param node_id 
     * @return Node& 
     */
    Node &findNodeByIdReadWrite(uint8_t node_id);

    /**
     * @brief Returns the numbers of nodes in the graph
     * 
     * @return uint8_t 
     */
    uint8_t numerOfNodes() const;

    /**
     * @brief  Add an edge to the graph between the observer and target nodes, giving it a unique edge id
     * 
     * @param observer_id 
     * @param target_id_ 
     * @return uint8_t 
     */
    uint8_t addEdge(uint8_t observer_id,
                    uint8_t target_id_);

    /**
     * @brief Remove an edge from the graph based on the observer's and target's id
     * 
     * @param edge_pair 
     */
    void removeEdgeByNodeIds(std::pair<uint8_t, uint8_t> edge_pair);

    /**
     * @brief Remove all edges from a graph
     * 
     */
    void removeAllEdges();

    /**
     * @brief Return a non modifiable read-only reference to an edge object based on the edge pair consisting of observer's ad target's id  
     * 
     * @param edge_pair 
     * @return const Edge& 
     */
    const Edge &findEdgeByNodeIdsReadOnly(std::pair<uint8_t, uint8_t> edge_pair) const; // read-only reference to an existing object

    /**
     * @brief Return a modifiable read-write reference of an edge object based on the edge pair consisting of observer's ad target's id  
     * 
     * @param edge_pair 
     * @return Edge& 
     */
    Edge &findEdgeByNodeIdsReadWrite(std::pair<uint8_t, uint8_t> edge_pair); // read-write reference to an existing object

    /**
     * @brief Return the number of edges
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
     * @brief Call updateAllEdges

     * 
     */
    void updateNodesAndEdges();

private:
    
    /**
     * @brief Generate a unique node id 
     * 
     * @return uint8_t 
     */
    uint8_t nodeIDGeneration();

    /**
     * @brief Verify that the passed node id generated is not taken.
     * 
     * @param node_id 
     * @return true 
     * @return false 
     */
    bool isNodeIDValid(uint8_t node_id);

    /**
     * @brief Generate a unique edge id
     * 
     * @return uint8_t 
     */
    uint8_t edgeIDGeneration();

    /**
     * @brief Verify that the passed edge id generated is not taken.
     * 
     * @param edge_id 
     * @return true 
     * @return false 
     */
    bool isEdgeIDValid(uint8_t edge_id);

    /**
     * @brief Call updateEdge for all edges in the graph
     * 
     */
    void updateAllEdges();

    /**
     * @brief Update the current distance from the observer and target and the angle between them
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
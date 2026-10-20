#pragma once

#include <cstdint>

#include <reusable_calculations.hpp>

/**
* @file edge_class.hpp
* @author rottango
* @date 20.10.2026
* @see ‘‘ OpenCV2 ’’ 
*
* @brief Header file for the edge class, thats the representation of a "relation of measuring" between two nodes - the source: observer, and the end node: target
*/

class Edge
{
    friend class Graph;

public:
    /**
     * @brief Construct a new Edge object
     * 
     * @param edge_id 
     * @param observer_id 
     * @param target_id_ 
     */
    Edge(uint8_t edge_id, uint8_t observer_id, uint8_t target_id_);

    /**
     * @brief Get the Edge Id object
     * 
     * @return uint8_t 
     */
    uint8_t getEdgeId() const;

    /**
     * @brief Get the Observer Id object
     * 
     * @return uint8_t 
     */
    uint8_t getObserverId() const;

    /**
     * @brief Get the Target Id object
     * 
     * @return uint8_t 
     */
    uint8_t getTargetId() const;

    /**
     * @brief Get the Distance Between Nodes Meters object
     * 
     * @return double 
     */
    double getDistanceBetweenNodesMeters() const;

    /**
     * @brief Get the Angle Between Nodes Degrees object
     * 
     * @return double 
     */
    double getAngleBetweenNodesDegrees() const;

    /**
     * @brief Get the Temp Timestamp object
     * 
     * @return double 
     */
    double getTempTimestamp() const;

    /**
     * @brief Get the Distance Between Nodes Meters Error object
     * 
     * @return double 
     */
    double getDistanceBetweenNodesMetersError() const;

    /**
     * @brief Get the Angle Between Nodes Degrees Error object
     * 
     * @return double 
     */
    double getAngleBetweenNodesDegreesError() const;

private:
    /**
     * @brief Set the Distance Between Nodes Meters object
     * 
     * @param distance_between_nodes_meters_ 
     */
    void setDistanceBetweenNodesMeters(double distance_between_nodes_meters_); // should be set by the graph object

    /**
     * @brief Set the Angle Between Nodes Degrees object
     * 
     * @param angle_between_nodes_degrees 
     * @param theta_rotation 
     */
    void setAngleBetweenNodesDegrees(double angle_between_nodes_degrees, double theta_rotation); // should be set by the graph object

    /**
     * @brief Set the Temp Timestamp object
     * 
     * @param temp_timestamp_ 
     */
    void setTempTimestamp(double temp_timestamp_); // should be set by the graph object

    /**
     * @brief Set the Distance Between Nodes Meters Error object
     * 
     * @param distance_between_nodes_meters_error_ 
     */
    void setDistanceBetweenNodesMetersError(double distance_between_nodes_meters_error_); // should be set by the graph object

    /**
     * @brief Set the Angle Between Nodes Degrees Error object
     * 
     * @param angle_between_nodes_degrees_error_ 
     */
    void setAngleBetweenNodesDegreesError(double angle_between_nodes_degrees_error_); // should be set by the graph object

    uint8_t edge_id_;
    uint8_t observer_id_;
    uint8_t target_id_;

    double distance_between_nodes_meters_;
    double angle_between_nodes_degrees_;
    double temp_timestamp_;

    double distance_between_nodes_meters_error_;
    double angle_between_nodes_degrees_error_;

    double uwb_signal_quality_;
};
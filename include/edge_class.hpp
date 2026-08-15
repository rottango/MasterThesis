#pragma once

#include <cstdint>

#include <reusable_calculations.hpp>

class Edge
{
    friend class Graph;

public:
    Edge(uint8_t edge_id,
         uint8_t observer_id,
         uint8_t target_id_);

    uint8_t getEdgeId() const;

    uint8_t getObserverId() const;

    uint8_t getTargetId() const;

    double getDistanceBetweenNodesMeters() const;

    double getAngleBetweenNodesDegrees() const;

    double getTempTimestamp() const;

    double getDistanceBetweenNodesMetersError() const;

    double getAngleBetweenNodesDegreesError() const;

private:
    void setDistanceBetweenNodesMeters(double distance_between_nodes_meters_); // should be set by the graph object

    void setAngleBetweenNodesDegrees(double angle_between_nodes_degrees_); // should be set by the graph object

    void setTempTimestamp(double temp_timestamp_); // should be set by the graph object

    void setDistanceBetweenNodesMetersError(double distance_between_nodes_meters_error_); // should be set by the graph object

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
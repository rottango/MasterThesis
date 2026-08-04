#pragma once

#include <cstdint>

class Edge
{
public:
    Edge(uint8_t edge_id,
         uint8_t observer_id,
         uint8_t target_id_) {
    };

private:
    uint8_t edge_id_;
    uint8_t observer_id_;
    uint8_t target_id_;

    double distance_between_nodes_meters_;
    double angle_between_nodes_degrees_;
    double temp_timestamp_;

    double distance_between_nodes_meters_error_;
    double angle_between_nodes_degrees_eror_;

    // bool is_active_;
    // bool is_obstructed_;
    // bool is_cross_group_connecting_;

    double uwb_signal_quality_;

    uint8_t getEdgeId();

    uint8_t getObserverId();

    uint8_t getTargetId();

    double getDistanceBetweenNodesMeters();

    double getAngleBetweenNodesDegrees();

    double getTempTimestamp();

    double getDistanceBetweenNodesMetersError();

    double getAngleBetweenNodesDegreesError();

    void setEdgeId(); // not to be used, because only constructor should create edge id, it shouldnt change

    void setObserverId(); // not to be used, because only constructor should create observer id, it shouldnt change, if should be changed, then it shoudl be deleted and a new edge created

    void setTargetId(); // not to be used, because only constructor should create target id, it shouldnt change, if should be changed, then it shoudl be deleted and a new edge created

    void setDistanceBetweenNodesMeters(double distance_between_nodes_meters_);

    void setAngleBetweenNodesDegrees(double angle_between_nodes_degrees_);

    void setTempTimestamp(double temp_timestamp_);

    void setDistanceBetweenNodesMetersError(double distance_between_nodes_meters_error_);

    void setAngleBetweenNodesDegreesError(double angle_between_nodes_degrees_eror_);
};
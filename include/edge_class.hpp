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

    double distance_between_vertices_meters_;
    double angle_between_vertices_degrees_;
    double temp_timestamp_;

    double distance_between_vertices_degrees_error_;
    double angle_between_vertices_degrees_eror_;

    bool is_active_;
    bool is_obstructed_;
    bool is_cross_group_connecting_;

    double uwb_signal_quality_;

    uint8_t getEdgeId();

    uint8_t getObserverId();

    uint8_t getTargetId();

    void setEdgeId();

    void setObserverId();

    void setTargetId();
};
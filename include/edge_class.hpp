
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

    double distance_between_vertices_meters;
    double angle_between_vertices_degrees;
    double temp_timestamp;

    double distance_between_vertices_degrees_error;
    double angle_between_vertices_degrees_eror;

    bool is_active;
    bool is_obstructed;
    bool is_cross_group_connecting;

    double uwb_signal_quality;

    uint8_t getEdgeId();

    uint8_t getObserverId();

    uint8_t getTargetId();

    void setEdgeId();

    void setObserverId();

    void setTargetId();
};
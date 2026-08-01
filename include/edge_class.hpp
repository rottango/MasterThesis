
class Edge
{
    int edge_id;
    int observer_id;
    int target_id;

    double distance_between_vertices_meters;
    double angle_between_vertices_degrees;
    double temp_timestamp;

    double distance_between_vertices_degrees_error;
    double angle_between_vertices_degrees_eror;

    bool is_active;
    bool is_obstructed;
    bool is_cross_group_connecting;

    double uwb_signal_quality;
};
#include <edge_class.hpp>

Edge::Edge(uint8_t edge_id,
           uint8_t observer_id,
           uint8_t target_id_)
{
    this->edge_id_ = edge_id;
    this->observer_id_ = observer_id;
    this->target_id_ = target_id_;
}

uint8_t Edge::getEdgeId() const
{
    return this->edge_id_;
}

uint8_t Edge::getObserverId() const
{
    return this->observer_id_;
}

uint8_t Edge::getTargetId() const
{
    return this->target_id_;
}

double Edge::getDistanceBetweenNodesMeters() const
{
    return this->distance_between_nodes_meters_;
}

double Edge::getAngleBetweenNodesDegrees() const
{

    return this->angle_between_nodes_degrees_;
}

double Edge::getTempTimestamp() const
{
    return this->temp_timestamp_;
}

double Edge::getDistanceBetweenNodesMetersError() const
{
    return this->distance_between_nodes_meters_error_;
}

double Edge::getAngleBetweenNodesDegreesError() const
{

    return this->angle_between_nodes_degrees_eror_;
}

void Edge::setDistanceBetweenNodesMeters(double distance_between_nodes_meters_) // should be set by the graph object
{
    this->distance_between_nodes_meters_ = distance_between_nodes_meters_;
}

void Edge::setAngleBetweenNodesDegrees(double angle_between_nodes_degrees_)
{
    this->angle_between_nodes_degrees_ = angle_between_nodes_degrees_;
}

void Edge::setTempTimestamp(double temp_timestamp_)
{
    this->temp_timestamp_ = temp_timestamp_;
}

void Edge::setDistanceBetweenNodesMetersError(double distance_between_nodes_meters_error_)
{
    this->distance_between_nodes_meters_error_ = distance_between_nodes_meters_error_;
}

void Edge::setAngleBetweenNodesDegreesError(double angle_between_nodes_degrees_eror_)
{
    this->angle_between_nodes_degrees_eror_ = angle_between_nodes_degrees_eror_;
}
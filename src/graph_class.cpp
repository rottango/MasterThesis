
#include <map>
#include <unordered_map>
#include <utility>

#include <edge_class.hpp>
#include <graph_class.hpp>
#include <node_class.hpp>

Graph::Graph(std::unordered_map<uint8_t, Node> nodes_,
             std::map<std::pair<uint8_t, uint8_t>, Edge> edges_,
             std::unordered_map<uint8_t, GroupingManager> grouping_managers_,
             std::unordered_map<uint8_t, Group> groups)
{
    if (!nodes_.empty())
    {
        this->nodes_ = nodes_;
    }
    if (!edges_.empty())
    {
        this->edges_ = edges_;
    }
    if (!grouping_managers_.empty())
    {
        this->grouping_managers_ = grouping_managers_;
    }
    if (!grouping_managers_.empty())
    {
        this->groups = groups;
    }
}

void Graph::addNode(cv::Point2d cartesian_x_y_point_,
                    double theta_rotation_degrees_,
                    uint8_t vehicle_size_,
                    uint8_t inner_,
                    uint8_t measurment_error_cm_,
                    colorPalet node_color_palet_)
{
    uint8_t generated_node_id;
    do
    {
        generated_node_id = nodeIDGeneration();

    } while (!nodeIDValidation(generated_node_id));

    nodes_[generated_node_id] = Node(generated_node_id, cartesian_x_y_point_,
                                     theta_rotation_degrees_,
                                     vehicle_size_,
                                     inner_,
                                     measurment_error_cm_,
                                     node_color_palet_);
}

void Graph::removeNodeById()
{
}

void Graph::removeAllNodes()
{
}

Node Graph::findNodeById()
{
}

Edge Graph::findEdgeById()
{
}

bool Graph::DoesNodeExist()
{
}

bool Graph::DoesEdgeExist()
{
}

void Graph::addEdge()
{
}

void Graph::removeEdgeById()
{
}

uint8_t Graph::nodeIDGeneration()
{
    this->current_node_id_ += 1;
    return this->current_node_id_;
}

bool Graph::nodeIDValidation(uint8_t node_id)
{
    // if no nodes are in the map, no node ids are taken.
    if (this->nodes_.empty())
    {
        return true;
    }
    // todo handle other logic
}

uint8_t Graph::edgeIDGeneration()
{
    this->current_edge_id_ += 1;
    return this->current_edge_id_;
}

bool Graph::edgeIDValidation(uint8_t edge_id)
{

    if (this->edges_.empty())
    {
        return true;
    }
    // todo handle other logic
}

void Graph::removeAllNodeEdges()
{
}
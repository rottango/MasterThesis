
#include <graph_class.hpp>

Graph::Graph()
{
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

    this->nodes_.insert({generated_node_id,
                         Node(generated_node_id, cartesian_x_y_point_,
                              theta_rotation_degrees_,
                              vehicle_size_,
                              inner_,
                              measurment_error_cm_,
                              node_color_palet_)});
}

void Graph::removeNodeById(uint8_t node_id)
{
    this->nodes_.erase(node_id);
}

void Graph::removeAllNodes()
{
    this->nodes_.clear();
}

const Node &Graph::findNodeById(uint8_t node_id) const // useful for inspecting the node.
{
    auto it = this->nodes_.find(node_id);

    if (it == nodes_.end())
    {
        std::cout << "The node with node_id: " << node_id << " does't exist.\n";
    }
    return it->second;
}

// bool Graph::doesNodeExist() // implemented in findNodeById
// {
// }

uint8_t Graph::numerOfNodes() const
{
    return nodes_.size();
}

void Graph::addEdge(uint8_t observer_id,
                    uint8_t target_id_)
{
    uint8_t generated_edge_id;
    do
    {
        generated_edge_id = edgeIDGeneration();

    } while (!edgeIDValidation(generated_edge_id));

    this->edges_.insert({std::pair(observer_id, target_id_),
                         Edge(generated_edge_id,
                              observer_id,
                              target_id_)});
}

void Graph::removeEdgeByNodeIds(std::pair<uint8_t, uint8_t> edge_pair)
{
    edges_.erase(edge_pair);
}

void Graph::removeAllEdges()
{
    edges_.clear();
}

const Edge &Graph::findEdgeByNodeIds(std::pair<uint8_t, uint8_t> edge_pair) const // read-only reference to an existing object
{
    auto it = this->edges_.find(edge_pair);

    if (it == edges_.end())
    {
        std::cout << "The edge between node_id: " << edge_pair.first << "and " << edge_pair.second << " does't exist.\n";
    }
    return it->second;
}

// bool Graph::doesEdgeExist() // implemented in findEdgeByNodeIds
// {
// }

uint8_t Graph::numerOfEdges() const
{
    return edges_.size();
}

const std::unordered_map<uint8_t, Node> &Graph::getNodes() const
{
    return this->nodes_;
}

const std::map<std::pair<uint8_t, uint8_t>, Edge> &Graph::getEdges() const
{
    this->edges_;
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
    } // todo handle other logic
}

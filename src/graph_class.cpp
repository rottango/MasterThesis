#include <graph_class.hpp>

Graph::Graph()
{
}

uint8_t Graph::addNode(cv::Point2d cartesian_x_y_point_,
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

    } while (!isNodeIDValid(generated_node_id));

    this->nodes_.insert({generated_node_id,
                         Node(generated_node_id, cartesian_x_y_point_,
                              theta_rotation_degrees_,
                              vehicle_size_,
                              inner_,
                              measurment_error_cm_,
                              node_color_palet_)});
    return generated_node_id;
}

void Graph::removeNodeById(uint8_t node_id)
{
    this->nodes_.erase(node_id);
}

void Graph::removeAllNodes()
{
    this->nodes_.clear();
}

const Node &Graph::findNodeByIdReadOnly(uint8_t node_id) const // useful for inspecting the node.
{
    auto it = this->nodes_.find(node_id);

    if (it == nodes_.end())
    {
        spdlog::warn("The node with node_id: ({}) does't exist", node_id);
    }
    return it->second;
}

Node &Graph::findNodeByIdReadWrite(uint8_t node_id)
{
    auto it = this->nodes_.find(node_id);

    if (it == nodes_.end())
    {
        spdlog::warn("The node with node_id: ({}) does't exist", node_id);
    }
    return it->second;
}

uint8_t Graph::numerOfNodes() const
{
    return nodes_.size();
}

uint8_t Graph::addEdge(uint8_t observer_id,
                       uint8_t target_id_)
{
    if (observer_id == target_id_)
    {
        return 0;
    }

    uint8_t generated_edge_id;
    do
    {
        generated_edge_id = edgeIDGeneration();

    } while (!isEdgeIDValid(generated_edge_id));

    this->edges_.insert({std::pair(observer_id, target_id_),
                         Edge(generated_edge_id,
                              observer_id,
                              target_id_)});

    this->findEdgeByNodeIdsReadWrite(std::pair<uint8_t, uint8_t>(observer_id, target_id_)).setAngleBetweenNodesDegrees(bearingBetweenTwoPointsDegrees(this->findNodeByIdReadOnly(observer_id).getXYPoint(), this->findNodeByIdReadOnly(target_id_).getXYPoint()), findNodeByIdReadOnly(observer_id).getThetaRotationDegrees());
    return generated_edge_id;
}

void Graph::removeEdgeByNodeIds(std::pair<uint8_t, uint8_t> edge_pair)
{
    edges_.erase(edge_pair);
}

void Graph::removeAllEdges()
{
    edges_.clear();
}

const Edge &Graph::findEdgeByNodeIdsReadOnly(std::pair<uint8_t, uint8_t> edge_pair) const // read-only reference to an existing object
{
    auto it = this->edges_.find(edge_pair);

    if (it == edges_.end())
    {
        spdlog::warn("The edge between node_id: ({}), and: ({}) doesn't exist", edge_pair.first, edge_pair.second);
    }
    return it->second;
}

Edge &Graph::findEdgeByNodeIdsReadWrite(std::pair<uint8_t, uint8_t> edge_pair) // read-write reference to an existing object
{
    auto it = this->edges_.find(edge_pair);

    if (it == edges_.end())
    {
        spdlog::warn("The edge between node_id: ({}), and: ({}) doesn't exist", edge_pair.first, edge_pair.second);
    }
    return it->second;
}

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
    return this->edges_;
}

uint8_t Graph::nodeIDGeneration()
{
    this->current_node_id_ += 1;

    return this->current_node_id_;
}

bool Graph::isNodeIDValid(uint8_t node_id)
{

    // if no nodes are in the map, no node ids are taken.
    if (this->nodes_.empty())
    {
        spdlog::warn("No nodes in the graph");

        return true;
    }
    else
    {
        if (this->nodes_.contains(node_id))
        {
            spdlog::warn("Node id is already taken");
            return false;
        }
        return true;
    }

    // todo handle other logic
}

uint8_t Graph::edgeIDGeneration()
{
    this->current_edge_id_ += 1;

    return this->current_edge_id_;
}

bool Graph::isEdgeIDValid(uint8_t edge_id)
{
    if (this->edges_.empty())
    {
        spdlog::warn("No edges in the graph");
        return true;
    }

    for (auto it = edges_.begin(); it != edges_.end(); it++)
    {
        if (it->second.getEdgeId() == edge_id)
        {
            spdlog::warn("Edge id already taken");
            return false;
        }
    }
    return true;
}

void Graph::updateNodesAndEdges()
{
    updateAllEdges();
    // update everything else and all nodes?
}

// todo handle other logic
void Graph::updateAllEdges()
{
    for (auto it = this->edges_.begin(); it != edges_.end(); it++)
    {
        updateEdge(it->second.getEdgeId(),
                   it->second.getObserverId(),
                   it->second.getTargetId());
    }
}

void Graph::updateEdge(uint8_t edge_id,
                       uint8_t observer_id,
                       uint8_t target_id_)
{
    Edge &edge =
        this->findEdgeByNodeIdsReadWrite(std::pair<uint8_t, uint8_t>(observer_id, target_id_));
    const Node &observer =
        this->findNodeByIdReadWrite(observer_id);
    const Node &target =
        this->findNodeByIdReadWrite(target_id_);

    // setDistanceBetweenNodesMeters
    edge.setDistanceBetweenNodesMeters(distanceBetweenTwoPoints(observer.getXYPoint(), target.getXYPoint()));
    // setAngleBetweenNodesDegrees
    edge.setAngleBetweenNodesDegrees(bearingBetweenTwoPointsDegrees(observer.getXYPoint(), target.getXYPoint()), observer.getThetaRotationDegrees());
    // setTempTimestamp

    // setDistanceBetweenNodesMetersError

    // setAngleBetweenNodesDegreesError
}
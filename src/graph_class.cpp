#include <graph_class.hpp>

Graph::Graph()
{
    spdlog::info("Entering Graph::Graph()");
    spdlog::info("Exiting Graph::Graph()");
}

uint8_t Graph::addNode(cv::Point2d cartesian_x_y_point_,
                       double theta_rotation_degrees_,
                       uint8_t vehicle_size_,
                       uint8_t inner_,
                       uint8_t measurment_error_cm_,
                       colorPalet node_color_palet_)
{
    spdlog::info("Entering Graph::addNode()");

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
    spdlog::info("Exiting Graph::addNode()");
    return generated_node_id;
}

void Graph::removeNodeById(uint8_t node_id)
{
    spdlog::info("Entering Graph::removeNodeById()");
    this->nodes_.erase(node_id);
    spdlog::info("Exiting Graph::removeNodeById()");
}

void Graph::removeAllNodes()
{
    spdlog::info("Entering Graph::removeAllNodes()");
    this->nodes_.clear();
    spdlog::info("Exiting Graph::removeAllNodes()");
}

const Node &Graph::findNodeByIdReadOnly(uint8_t node_id) const // useful for inspecting the node.
{
    spdlog::info("Entering Graph::findNodeByIdReadOnly()");

    auto it = this->nodes_.find(node_id);

    if (it == nodes_.end())
    {
        std::cout << "The node with node_id: " << node_id << " does't exist.\n";
    }

    spdlog::info("Exiting Graph::findNodeByIdReadOnly()");

    return it->second;
}

Node &Graph::findNodeByIdReadWrite(uint8_t node_id)
{
    spdlog::info("Entering Graph::findNodeByIdReadWrite()");

    auto it = this->nodes_.find(node_id);

    if (it == nodes_.end())
    {
        std::cout << "The node with node_id: " << static_cast<int>(node_id) << " does't exist.\n";
    }
    spdlog::info("Exiting Graph::findNodeByIdReadWrite()");

    return it->second;
}

// bool Graph::doesNodeExist() // implemented in findNodeByIdReadOnly
// {
// }

uint8_t Graph::numerOfNodes() const
{
    spdlog::info("Entering Graph::numerOfNodes()");
    spdlog::info("Exiting Graph::numerOfNodes()");
    return nodes_.size();
}

uint8_t Graph::addEdge(uint8_t observer_id,
                       uint8_t target_id_)
{
    spdlog::info("Entering Graph::addEdge()");

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
    spdlog::info("Exiting Graph::addEdge()");
}

void Graph::removeEdgeByNodeIds(std::pair<uint8_t, uint8_t> edge_pair)
{
    spdlog::info("Entering Graph::removeEdgeByNodeIds()");

    edges_.erase(edge_pair);
    spdlog::info("Exiting Graph::removeEdgeByNodeIds()");
}

void Graph::removeAllEdges()
{
    spdlog::info("Entering Graph::removeAllEdges()");

    edges_.clear();
    spdlog::info("Exiting Graph::removeAllEdges()");
}

const Edge &Graph::findEdgeByNodeIdsReadOnly(std::pair<uint8_t, uint8_t> edge_pair) const // read-only reference to an existing object
{
    spdlog::info("Entering Graph::findEdgeByNodeIdsReadOnly()");

    auto it = this->edges_.find(edge_pair);

    if (it == edges_.end())
    {
        std::cout << "The edge between node_id: " << edge_pair.first << "and " << edge_pair.second << " does't exist.\n";
    }

    spdlog::info("Exiting Graph::findEdgeByNodeIdsReadOnly()");

    return it->second;
}

Edge &Graph::findEdgeByNodeIdsReadWrite(std::pair<uint8_t, uint8_t> edge_pair) // read-write reference to an existing object
{
    spdlog::info("Entering Graph::findEdgeByNodeIdsReadWrite()");

    auto it = this->edges_.find(edge_pair);

    if (it == edges_.end())
    {
        std::cout << "The edge between node_id: " << edge_pair.first << "and " << edge_pair.second << " does't exist.\n";
    }
    spdlog::info("Exiting Graph::findEdgeByNodeIdsReadWrite()");

    return it->second;
}

// bool Graph::doesEdgeExist() // implemented in findEdgeByNodeIdsReadOnly
// {
// }

uint8_t Graph::numerOfEdges() const
{
    spdlog::info("Entering Graph::numerOfEdges()");
    spdlog::info("Exiting Graph::numerOfEdges()");

    return edges_.size();
}

const std::unordered_map<uint8_t, Node> &Graph::getNodes() const
{
    spdlog::info("Entering Graph::getNodes()");
    spdlog::info("Exiting Graph::getNodes()");

    return this->nodes_;
}

const std::map<std::pair<uint8_t, uint8_t>, Edge> &Graph::getEdges() const
{
    spdlog::info("Entering Graph::getEdges()");
    spdlog::info("Exiting Graph::getEdges()");

    return this->edges_;
}

uint8_t Graph::nodeIDGeneration()
{
    spdlog::info("Entering Graph::nodeIDGeneration()");

    this->current_node_id_ += 1;
    spdlog::info("Exiting Graph::nodeIDGeneration()");

    return this->current_node_id_;
}

bool Graph::isNodeIDValid(uint8_t node_id)
{
    spdlog::info("Entering Graph::isNodeIDValid()");

    // if no nodes are in the map, no node ids are taken.
    if (this->nodes_.empty())
    {
        spdlog::info("Exiting Graph::isNodeIDValid() - empty");

        return true;
    }
    else
    {
        spdlog::info("Exiting Graph::isNodeIDValid() - not empty");

        if (this->nodes_.contains(node_id))
        {
            return false;
        }
        return true;
    }

    // todo handle other logic
}

uint8_t Graph::edgeIDGeneration()
{
    spdlog::info("Entering Graph::edgeIDGeneration()");

    this->current_edge_id_ += 1;
    spdlog::info("Exiting Graph::edgeIDGeneration()");

    return this->current_edge_id_;
}

bool Graph::isEdgeIDValid(uint8_t edge_id)
{
    spdlog::info("Entering Graph::isEdgeIDValid()");

    if (this->edges_.empty())
    {
        spdlog::info("Exiting Graph::isEdgeIDValid() - empty");

        return true;
    }

    for (auto it = edges_.begin(); it != edges_.end(); it++)
    {
        if (it->second.getEdgeId() == edge_id)
        {
            return false;
        }
    }

    spdlog::info("Exiting Graph::isEdgeIDValid() - not empty");
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
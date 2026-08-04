
#include <map>
#include <unordered_map>
#include <utility>

#include <edge_class.hpp>
#include <graph_class.hpp>
#include <node_class.hpp>

Graph::Graph(std::unordered_map<uint8_t, Node> nodes_,
             std::map<std::pair<uint8_t, uint8_t>, Edge> edges_,
             std::unordered_map<uint8_t, GroupingManager> grouping_managers_)
{
}

void Graph::addNode()
{
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

void Graph::nodeIDGeneration()
{
}

void Graph::nodeIDValidation()
{
}

void Graph::edgeIDGeneration()
{
}

void Graph::edgeIDValidation()
{
}

void Graph::removeAllNodeEdges()
{
}

#include <map>
#include <unordered_map>
#include <utility>

#include <edge_class.hpp>
#include <node_class.hpp>
class Graph
{

    std::unordered_map<int, Node> nodes;
    std::map<std::pair<int, int>, Edge> edges;

    void nodeIDGeneration();

    void nodeIDValidation();

    void edgeIDGeneration();

    void edgeIDValidation();
};
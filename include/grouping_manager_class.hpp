#pragma once

#include <cstdint>

#include <group_class.hpp>
#include <unordered_map>

class GroupingManager
{
public:
    GroupingManager(uint8_t group_size_param_,
                    uint8_t proximity_param_,
                    uint8_t hysteresis_param_);

    void addGroup();

    void removeGroup();

    uint8_t getGroupId();

private:
    uint8_t group_size_param_; // prefered group size by the groupping manager
    uint8_t proximity_param_;  // how close nodes are to be to be considered for one group
    uint8_t hysteresis_param_; // param to prevemt rapid swoitching of groups
    // bool group_status_;
    // uint8_t leader_node_id_;

    std::vector<uint8_t> list_of_node_ids;
    std::unordered_map<uint8_t, Group> groups_;

    uint8_t groupIdWhereNodeIdIs();

    std::vector<uint8_t> nodeIdsInGroupByGroupId();

    uint8_t groupIDGeneration();

    bool groupIDValidation();
};
#pragma once

#include <cstdint>

#include <group_class.hpp>
#include <unordered_map>

class GroupingManager
{
public:

    /**
     * @brief Construct a new Grouping Manager object
     * 
     * @param group_size_param_ 
     * @param proximity_param_ 
     * @param hysteresis_param_ 
     */
    GroupingManager(uint8_t group_size_param_,
                    uint8_t proximity_param_,
                    uint8_t hysteresis_param_);

    /**
     * @brief 
     * 
     */
    void addGroup();

    /**
     * @brief 
     * 
     */
    void removeGroup();

    /**
     * @brief Get the Group Id object
     * 
     * @return uint8_t 
     */
    uint8_t getGroupId();

private:
    uint8_t group_size_param_; // prefered group size by the groupping manager
    uint8_t proximity_param_;  // how close nodes are to be to be considered for one group
    uint8_t hysteresis_param_; // param to prevemt rapid swoitching of groups
    // bool group_status_;
    // uint8_t leader_node_id_;

    std::vector<uint8_t> list_of_node_ids;
    std::unordered_map<uint8_t, Group> groups_;

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    uint8_t groupIdWhereNodeIdIs();

    /**
     * @brief 
     * 
     * @return std::vector<uint8_t> 
     */
    std::vector<uint8_t> nodeIdsInGroupByGroupId();

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    uint8_t groupIDGeneration();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool groupIDValidation();
};
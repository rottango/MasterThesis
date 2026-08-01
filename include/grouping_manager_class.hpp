#pragma once

#include <group_class.hpp>
#include <opencv2/opencv.hpp>
#include <unordered_map>

class GroupingManager
{
public:
private:
    uint8_t group_size_param_; // prefered group size by the groupping manager
    uint8_t proximity_param_;  // how close nodes are to be to be considered for one group
    uint8_t hysteresis_param_; // param to prevemt rapid swoitching of groups

    std::unordered_map<uint8_t, Group> groups_;
};
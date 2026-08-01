#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
class Group
{
public:
    uint8_t group_id;
    std::vector<uint8_t> node_ids;
    uint8_t group_size;
};
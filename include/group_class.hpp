#pragma once

#include <cstdint>
#include <vector>

/**
* @file group_class.hpp
* @author rottango
* @date 20.10.2026
* @see ‘‘ OpenCV2 ’’ 
*
* @brief Header file for the group class, which is not yet implemented, as its not necessary for basic functionality. It will be necessary when I will want to generalize this solution to N:N
*/

class Group
{
public:
    /**
     * @brief Construct a new Group object
     * 
     * @param group_id 
     * @param node_ids 
     * @param group_size 
     */
    Group(uint8_t group_id,
          std::vector<uint8_t> node_ids,
          uint8_t group_size);

private:
    uint8_t group_id;
    std::vector<uint8_t> node_ids;
    uint8_t group_size;
};
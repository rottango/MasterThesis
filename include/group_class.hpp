#pragma once

#include <cstdint>
#include <vector>

class Group
{
public:
    Group(uint8_t group_id,
          std::vector<uint8_t> node_ids,
          uint8_t group_size);

private:
    uint8_t group_id;
    std::vector<uint8_t> node_ids;
    uint8_t group_size;
};
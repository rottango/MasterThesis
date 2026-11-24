#pragma once

#include <cstddef>
#include <cstdint>

struct TLVRequest
{
    std::byte Type;
    std::byte Length;
};

struct AnchorsRaw
{
    std::byte value_position_x[4];
    std::byte value_position_y[4];
    std::byte value_position_z[4];
    std::byte uwb_address[2];
    std::byte rssi;
    std::byte seat_number_and_neighbor_network;
};

struct AnchorsDecoded
{
    std::uint16_t uwb_address;
    std::int32_t value_position_x;
    std::int32_t value_position_y;
    std::int32_t value_position_z;
    std::int8_t rssi;
    std::uint8_t seat_number_and_neighbor_network;
};

struct ANxRawTag
{ // from documentation TLV repsonse from dwm_loc_get
    std::byte uwb_address[2];
    std::byte distance[4];
    std::byte distance_quality_factor;

    std::byte value_position_x[4];
    std::byte value_position_y[4];
    std::byte value_position_z[4];
};

struct ANxDecodedTag
{
    std::uint16_t uwb_address;
    std::int32_t distance;
    std::uint8_t distance_quality_factor;

    std::int32_t value_position_x;
    std::int32_t value_position_y;
    std::int32_t value_position_z;
};

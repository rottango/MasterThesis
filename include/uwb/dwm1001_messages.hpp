
#pragma once

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <array>

#include <dwm1001_messages_helper.hpp>
#include <dwm1001_enum.hpp>

inline std::string errorCodeToText(const DWM1001ErrorCode &error_code)
{
    switch (error_code)
    {
    case OK:
        return "OK";
    case UNKNOWN_OR_BROKEN_TLV:
        return "UNKNOWN_OR_BROKEN_TLV";

    case INTERNAL_ERROR:
        return "INTERNAL_ERROR";

    case INVALID_PARAMETER:
        return "INVALID_PARAMETER";

    case BUSY:
        return "BUSY";
    case OPERATION_NOT_PERMITTED:
        return "OPERATION_NOT_PERMITTED";
    default:
        return "ERROR CODE NOT RECOGNIZED";
    }
};

struct DwmUpdRateSet
{
    ApiFunction api_function = DWM_UPD_RATE_SET;

    TLVRequest request{std::byte{0x04}, std::byte{0x00}};

    uint16_t update_rate;
    uint16_t update_rate_stationary;

    struct UwbPositionRaw
    {
        std::byte type_general;
        std::byte length_general;
        std::byte value_err_code_general;
    } uwb_position_raw;

    struct UwbPositionDecoded
    {
        std::uint8_t type_general;
        std::uint8_t length_general;
        std::uint8_t value_err_code_general;
    } uwb_position_decoded;

    bool read(std::array<uint8_t, 3> &response)
    {
        if (sizeof(response) != 3)
        {
            return false;
        }

        this->uwb_position_raw.type_general = static_cast<std::byte>(response[0]);
        this->uwb_position_raw.length_general = static_cast<std::byte>(response[1]);
        this->uwb_position_raw.value_err_code_general = static_cast<std::byte>(response[2]);

        return true;
    }

    bool decode()
    {

        this->uwb_position_decoded.type_general = static_cast<std::uint8_t>(this->uwb_position_raw.type_general);
        this->uwb_position_decoded.length_general = static_cast<std::uint8_t>(this->uwb_position_raw.length_general);
        this->uwb_position_decoded.value_err_code_general = static_cast<std::uint8_t>(this->uwb_position_raw.value_err_code_general);

        return true;
    }

    void display()
    {
        std::cout << std::dec << "General Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
    }
};

struct DwmUpdRateGet
{
    ApiFunction api_function = DWM_UPD_RATE_GET;

    TLVRequest request{std::byte{0x04}, std::byte{0x00}};

    struct UwbPositionRaw
    {
        std::byte type_general;
        std::byte length_general;
        std::byte value_err_code_general;
        std::byte type;
        std::byte length;
        std::byte update_rate[2];
        std::byte update_rate_stationary[2];
    } uwb_position_raw;

    struct UwbPositionDecoded
    {
        std::uint8_t type_general;
        std::uint8_t length_general;
        std::uint8_t value_err_code_general;
        std::uint8_t type;
        std::uint8_t length;
        std::uint16_t update_rate;
        std::uint16_t update_rate_stationary;
    } uwb_position_decoded;

    bool read(std::array<uint8_t, 9> &response)
    {
        if (sizeof(response) != 9)
        {
            return false;
        }

        this->uwb_position_raw.type_general = static_cast<std::byte>(response[0]);
        this->uwb_position_raw.length_general = static_cast<std::byte>(response[1]);
        this->uwb_position_raw.value_err_code_general = static_cast<std::byte>(response[2]);
        this->uwb_position_raw.type = static_cast<std::byte>(response[3]);
        this->uwb_position_raw.length = static_cast<std::byte>(response[4]);

        // TODO rest ...

        return true;
    }

    bool decode()
    {

        this->uwb_position_decoded.type_general = static_cast<std::uint8_t>(this->uwb_position_raw.type_general);
        this->uwb_position_decoded.length_general = static_cast<std::uint8_t>(this->uwb_position_raw.length_general);
        this->uwb_position_decoded.value_err_code_general = static_cast<std::uint8_t>(this->uwb_position_raw.value_err_code_general);
        this->uwb_position_decoded.type = static_cast<std::uint8_t>(this->uwb_position_raw.type);
        this->uwb_position_decoded.length = static_cast<std::uint8_t>(this->uwb_position_raw.length);

        // TODO rest ...

        return true;
    }

    void display()
    {
        std::cout << std::dec << "General Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Type: " << static_cast<unsigned>(this->uwb_position_decoded.type) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type) << "\n";
        std::cout << std::dec << "Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length) << "\n";

        // TODO rest ...
    };
};

struct DwmAnchorListGet
{
    ApiFunction api_function = DWM_ANCHOR_LIST_GET;

    TLVRequest request{std::byte{0x0B}, std::byte{0x01}};
    uint8_t page_number;

    struct UwbPositionRaw
    {
        std::byte type_general;
        std::byte length_general;
        std::byte value_err_code_general;
        std::byte type;
        std::byte length;

        std::byte number_of_elements; // number of anchors in anchor list
        AnchorsRaw anchor_list[15];   // anchor nr 1 is index 0, anchor nr 15 is index 14
    } uwb_position_raw;

    struct UwbPositionDecoded
    {
        std::uint8_t type_general;
        std::uint8_t length_general;
        std::uint8_t value_err_code_general;
        std::uint8_t type;
        std::uint8_t length;

        std::uint8_t number_of_elements; // number of anchors in anchor list
        AnchorsDecoded anchor_list[15];  // anchor nr 1 is index 0, anchor nr 15 is index 14
    } uwb_position_decoded;

    bool read(std::array<uint8_t, 3> &response) // TODO: ... I dont know how to do the size thing here, i think we have to assume max size is for all 15 anchors, and check the inside to see how much data we actually have
    {
        if (sizeof(response) != 3)
        {
            return false;
        }

        this->uwb_position_raw.type_general = static_cast<std::byte>(response[0]);
        this->uwb_position_raw.length_general = static_cast<std::byte>(response[1]);
        this->uwb_position_raw.value_err_code_general = static_cast<std::byte>(response[2]);
        this->uwb_position_raw.type = static_cast<std::byte>(response[3]);
        this->uwb_position_raw.length = static_cast<std::byte>(response[4]);

        return true;
    }

    bool decode()
    {

        this->uwb_position_decoded.type_general = static_cast<std::uint8_t>(this->uwb_position_raw.type_general);
        this->uwb_position_decoded.length_general = static_cast<std::uint8_t>(this->uwb_position_raw.length_general);
        this->uwb_position_decoded.value_err_code_general = static_cast<std::uint8_t>(this->uwb_position_raw.value_err_code_general);
        this->uwb_position_decoded.type = static_cast<std::uint8_t>(this->uwb_position_raw.type);
        this->uwb_position_decoded.length = static_cast<std::uint8_t>(this->uwb_position_raw.length);

        return true;
    }

    void display()
    {
        std::cout << std::dec << "General Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Type: " << static_cast<unsigned>(this->uwb_position_decoded.type) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type) << "\n";
        std::cout << std::dec << "Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length) << "\n";
    }
};

struct DwmLocGet
{
    ApiFunction api_function = DWM_LOC_GET;

    TLVRequest request{std::byte{0x0C}, std::byte{0x00}};

    struct UwbPositionRaw
    {
        std::byte type_general;
        std::byte length_general;
        std::byte value_err_code_general;

        std::byte type;
        std::byte length;
        std::byte value_position_x[4];
        std::byte value_position_y[4];
        std::byte value_position_z[4];
        std::byte value_quality_factor;

        std::byte type_specific;
        std::byte length_specific;
        std::byte value_distances_encoded;

        ANxRaw list_of_an[4];
    } uwb_position_raw;

    struct UwbPositionDecoded
    {
        std::uint8_t type_general;
        std::uint8_t length_general;
        std::uint8_t value_err_code_general;

        std::uint8_t type;
        std::uint8_t length;
        std::int32_t value_position_x;
        std::int32_t value_position_y;
        std::int32_t value_position_z;
        std::uint8_t value_quality_factor;

        std::uint8_t type_specific;
        std::uint8_t length_specific;
        std::uint8_t value_distances_encoded;

        ANxDecoded list_of_an[4];
    } uwb_position_decoded;

    bool read(std::array<uint8_t, 3> &response) // TODO: Here we again i think have to assume all AN4 are populated, and then just see how much we actually read, and then decide how much actual data is there.
    {
        if (sizeof(response) != 3)
        {
            return false;
        }

        this->uwb_position_raw.type_general = static_cast<std::byte>(response[0]);
        this->uwb_position_raw.length_general = static_cast<std::byte>(response[1]);
        this->uwb_position_raw.value_err_code_general = static_cast<std::byte>(response[2]);
        this->uwb_position_raw.type = static_cast<std::byte>(response[3]);
        this->uwb_position_raw.length = static_cast<std::byte>(response[4]);

        return true;
    }

    bool decode()
    {

        this->uwb_position_decoded.type_general = static_cast<std::uint8_t>(this->uwb_position_raw.type_general);
        this->uwb_position_decoded.length_general = static_cast<std::uint8_t>(this->uwb_position_raw.length_general);
        this->uwb_position_decoded.value_err_code_general = static_cast<std::uint8_t>(this->uwb_position_raw.value_err_code_general);
        this->uwb_position_decoded.type = static_cast<std::uint8_t>(this->uwb_position_raw.type);
        this->uwb_position_decoded.length = static_cast<std::uint8_t>(this->uwb_position_raw.length);

        this->uwb_position_decoded.value_position_x = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[0]));
        this->uwb_position_decoded.value_position_y = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[0]));
        this->uwb_position_decoded.value_position_z = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[0]));

        this->uwb_position_decoded.value_quality_factor = static_cast<std::uint8_t>(this->uwb_position_raw.value_quality_factor);

        return true;
    }

    void display()
    {
        std::cout << std::dec << "General Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Type: " << static_cast<unsigned>(this->uwb_position_decoded.type) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type) << "\n";
        std::cout << std::dec << "Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length) << "\n";
        std::cout << std::dec << "Position x [mm]: " << this->uwb_position_decoded.value_position_x << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_x[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Position y [mm]: " << this->uwb_position_decoded.value_position_y << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_y[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Position z [mm]: " << this->uwb_position_decoded.value_position_z << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_z[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Quality [%]: " << static_cast<unsigned>(this->uwb_position_decoded.value_quality_factor) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_quality_factor) << "\n";
    }
};

struct DwmPosGet
{
    ApiFunction api_function = DWM_POS_GET;

    struct UwbPositionRaw
    {
        std::byte type_general;
        std::byte length_general;
        std::byte value_err_code_general;
        std::byte type;
        std::byte length;
        std::byte value_position_x[4];
        std::byte value_position_y[4];
        std::byte value_position_z[4];
        std::byte value_quality_factor;
    } uwb_position_raw;

    struct UwbPositionDecoded
    {
        std::int32_t value_position_x;
        std::int32_t value_position_y;
        std::int32_t value_position_z;
        std::uint8_t type_general;
        std::uint8_t length_general;
        std::uint8_t value_err_code_general;
        std::uint8_t type;
        std::uint8_t length;
        std::uint8_t value_quality_factor;
    } uwb_position_decoded;

    bool read(const std::array<uint8_t, 18> &response)
    {
        if (sizeof(response) != 18)
        {
            return false;
        }

        this->uwb_position_raw.type_general = static_cast<std::byte>(response[0]);
        this->uwb_position_raw.length_general = static_cast<std::byte>(response[1]);
        this->uwb_position_raw.value_err_code_general = static_cast<std::byte>(response[2]);
        this->uwb_position_raw.type = static_cast<std::byte>(response[3]);
        this->uwb_position_raw.length = static_cast<std::byte>(response[4]);

        this->uwb_position_raw.value_position_x[0] = static_cast<std::byte>(response[5]);
        this->uwb_position_raw.value_position_x[1] = static_cast<std::byte>(response[6]);
        this->uwb_position_raw.value_position_x[2] = static_cast<std::byte>(response[7]);
        this->uwb_position_raw.value_position_x[3] = static_cast<std::byte>(response[8]);
        this->uwb_position_raw.value_position_y[0] = static_cast<std::byte>(response[9]);
        this->uwb_position_raw.value_position_y[1] = static_cast<std::byte>(response[10]);
        this->uwb_position_raw.value_position_y[2] = static_cast<std::byte>(response[11]);
        this->uwb_position_raw.value_position_y[3] = static_cast<std::byte>(response[12]);
        this->uwb_position_raw.value_position_z[0] = static_cast<std::byte>(response[13]);
        this->uwb_position_raw.value_position_z[1] = static_cast<std::byte>(response[14]);
        this->uwb_position_raw.value_position_z[2] = static_cast<std::byte>(response[15]);
        this->uwb_position_raw.value_position_z[3] = static_cast<std::byte>(response[16]);

        this->uwb_position_raw.value_quality_factor = static_cast<std::byte>(response[17]);

        return true;
    }

    bool decode()
    {

        this->uwb_position_decoded.type_general = static_cast<std::uint8_t>(this->uwb_position_raw.type_general);
        this->uwb_position_decoded.length_general = static_cast<std::uint8_t>(this->uwb_position_raw.length_general);
        this->uwb_position_decoded.value_err_code_general = static_cast<std::uint8_t>(this->uwb_position_raw.value_err_code_general);
        this->uwb_position_decoded.type = static_cast<std::uint8_t>(this->uwb_position_raw.type);
        this->uwb_position_decoded.length = static_cast<std::uint8_t>(this->uwb_position_raw.length);

        this->uwb_position_decoded.value_position_x = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_x[0]));
        this->uwb_position_decoded.value_position_y = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_y[0]));
        this->uwb_position_decoded.value_position_z = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.value_position_z[0]));

        this->uwb_position_decoded.value_quality_factor = static_cast<std::uint8_t>(this->uwb_position_raw.value_quality_factor);

        return true;
    }

    void display()
    {
        std::cout << std::dec << "General Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Type: " << static_cast<unsigned>(this->uwb_position_decoded.type) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type) << "\n";
        std::cout << std::dec << "Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length) << "\n";
        std::cout << std::dec << "Position x [mm]: " << this->uwb_position_decoded.value_position_x << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_x[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Position y [mm]: " << this->uwb_position_decoded.value_position_y << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_y[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Position z [mm]: " << this->uwb_position_decoded.value_position_z << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_z[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Quality [%]: " << static_cast<unsigned>(this->uwb_position_decoded.value_quality_factor) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_quality_factor) << "\n";
    }
};

struct UwbMessages
{
    ApiFunction request_message_type;

    DwmPosGet dwm_pos_get;
    DwmUpdRateGet dwm_upd_rate_get;
    DwmUpdRateSet dwm_upd_rate_set;
    DwmAnchorListGet dwm_anchor_list_get;
    DwmLocGet dwm_loc_get;
};
/*
inline DWM1001ErrorCode verifyErrorCode(const struct UwbMessages &UwbMessages){
    switch(UwbPositionDecoded.value_err_code_general){
        case OK:
            return OK;
        case UNKNOWN_OR_BROKEN_TLV:
            std::cout<<errorCodeToText(UNKNOWN_OR_BROKEN_TLV)<<"\n";
            return UNKNOWN_OR_BROKEN_TLV;
        case INTERNAL_ERROR:
            std::cout<<errorCodeToText(INTERNAL_ERROR)<<"\n";
            return INTERNAL_ERROR;
        case INVALID_PARAMETER:
            std::cout<<errorCodeToText(INVALID_PARAMETER)<<"\n";
            return INVALID_PARAMETER;
        case BUSY:
            std::cout<<errorCodeToText(BUSY)<<"\n";
            return BUSY;
        case OPERATION_NOT_PERMITTED:
            std::cout<<errorCodeToText(OPERATION_NOT_PERMITTED)<<"\n";
            return OPERATION_NOT_PERMITTED;
        default:
            return UNRECOGNIZED_ERROR_CODE;
    }
};
*/
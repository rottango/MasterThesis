
#pragma once

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

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

    std::byte byte_update_rate[2]{};
    std::byte byte_update_rate_stationary[2]{};

    uint16_t update_rate = 1;
    uint16_t update_rate_stationary = 1;

    std::uint8_t request[6] = {0x03, 0x04};
    std::uint16_t read_size = 3;

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

    void int_update_rate_to_byte()
    {
        this->byte_update_rate[0] = static_cast<std::byte>(this->update_rate & 0xFF);
        this->byte_update_rate[1] = static_cast<std::byte>(this->update_rate >> 8);
        this->byte_update_rate_stationary[0] = static_cast<std::byte>(this->update_rate_stationary & 0xFF);
        this->byte_update_rate_stationary[1] = static_cast<std::byte>(this->update_rate_stationary >> 8);
        this->request[2] = static_cast<std::uint8_t>(byte_update_rate[0]);
        this->request[3] = static_cast<std::uint8_t>(byte_update_rate[1]);
        this->request[4] = static_cast<std::uint8_t>(byte_update_rate_stationary[0]);
        this->request[5] = static_cast<std::uint8_t>(byte_update_rate_stationary[1]);
    }

    bool read(std::vector<uint8_t> &response)
    {
        if (response.size() != read_size)
        {
            std::cout << "size of response: " << response.size() << "\n";

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
        std::cout << std::dec << "\nGeneral Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Set update rate each [ms] :" << (update_rate * 100) << "\t" << std::hex << std::uppercase << (update_rate * 100) << "\n";
        std::cout << std::dec << "Set stationary update rate each [ms] :" << (update_rate_stationary * 100) << "\t" << std::hex << std::uppercase << (update_rate_stationary * 100) << "\n";
    }
};

struct DwmUpdRateGet
{
    ApiFunction api_function = DWM_UPD_RATE_GET;

    std::uint8_t request[2] = {0x04, 0x00};
    std::uint16_t read_size = 9;

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

    bool read(std::vector<uint8_t> &response)
    {
        if (response.size() != read_size)
        {
            std::cout << "size of response: " << response.size() << "\n";

            return false;
        }

        this->uwb_position_raw.type_general = static_cast<std::byte>(response[0]);
        this->uwb_position_raw.length_general = static_cast<std::byte>(response[1]);
        this->uwb_position_raw.value_err_code_general = static_cast<std::byte>(response[2]);
        this->uwb_position_raw.type = static_cast<std::byte>(response[3]);
        this->uwb_position_raw.length = static_cast<std::byte>(response[4]);
        this->uwb_position_raw.update_rate[0] = static_cast<std::byte>(response[5]);
        this->uwb_position_raw.update_rate[1] = static_cast<std::byte>(response[6]);
        this->uwb_position_raw.update_rate_stationary[0] = static_cast<std::byte>(response[7]);
        this->uwb_position_raw.update_rate_stationary[1] = static_cast<std::byte>(response[8]);

        return true;
    }

    bool decode()
    {

        this->uwb_position_decoded.type_general = static_cast<std::uint8_t>(this->uwb_position_raw.type_general);
        this->uwb_position_decoded.length_general = static_cast<std::uint8_t>(this->uwb_position_raw.length_general);
        this->uwb_position_decoded.value_err_code_general = static_cast<std::uint8_t>(this->uwb_position_raw.value_err_code_general);
        this->uwb_position_decoded.type = static_cast<std::uint8_t>(this->uwb_position_raw.type);
        this->uwb_position_decoded.length = static_cast<std::uint8_t>(this->uwb_position_raw.length);
        this->uwb_position_decoded.update_rate = static_cast<int32_t>(static_cast<std::uint32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.update_rate[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.update_rate[0])));
        this->uwb_position_decoded.update_rate_stationary = static_cast<int32_t>(static_cast<std::uint32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.update_rate_stationary[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.update_rate_stationary[0])));

        return true;
    }

    void display()
    {
        std::cout << std::dec << "\nGeneral Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Type: " << static_cast<unsigned>(this->uwb_position_decoded.type) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type) << "\n";
        std::cout << std::dec << "Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length) << "\n";
        std::cout << std::dec << "Set update rate each [ms] :" << (this->uwb_position_decoded.update_rate * 100) << "\t" << std::hex << std::uppercase << (this->uwb_position_decoded.update_rate * 100) << "\n";
        std::cout << std::dec << "Set stationary update rate each [ms] :" << (this->uwb_position_decoded.update_rate_stationary * 100) << "\t" << std::hex << std::uppercase << (this->uwb_position_decoded.update_rate_stationary * 100) << "\n";
        // TODO rest ...
    };
};

struct DwmAnchorListGet
{
    ApiFunction api_function = DWM_ANCHOR_LIST_GET;

    std::uint8_t request[3] = {0x0B, 0x01, 0x00}; // 3rd byte is the page_number
    std::uint16_t read_size = 300;
    uint8_t page_number;
    uint8_t number_of_anchors = 3;
    struct UwbPositionRaw
    {
        std::byte type_general;
        std::byte length_general;
        std::byte value_err_code_general;
        std::byte type;
        std::byte length;

        std::byte number_of_elements; // number of anchors in anchor list
        AnchorsRaw anchor_list[3];    // anchor nr 1 is index 0, anchor nr 15 is index 14
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

    bool read(std::vector<uint8_t> &response) // TODO: ... I dont know how to do the size thing here, i think we have to assume max size is for all 15 anchors, and check the inside to see how much data we actually have
    {
        // if (response.size()  !=)
        // {
        //     std::cout << "size of response: " << response.size() << "\n";

        //     return false;
        // }

        this->uwb_position_raw.type_general = static_cast<std::byte>(response[0]);
        this->uwb_position_raw.length_general = static_cast<std::byte>(response[1]);
        this->uwb_position_raw.value_err_code_general = static_cast<std::byte>(response[2]);
        this->uwb_position_raw.type = static_cast<std::byte>(response[3]);
        this->uwb_position_raw.length = static_cast<std::byte>(response[4]);
        this->uwb_position_raw.number_of_elements = static_cast<std::byte>(response[5]);

        uint8_t temp_index = 6;
        for (int i = 0; i < number_of_anchors; i++) // TODO: Decide how many times execute the loop.
        {
            this->uwb_position_raw.anchor_list[i].uwb_address[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].uwb_address[1] = static_cast<std::byte>(response[temp_index++]);

            this->uwb_position_raw.anchor_list[i].value_position_x[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_x[1] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_x[2] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_x[3] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_y[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_y[1] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_y[2] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_y[3] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_z[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_z[1] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_z[2] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].value_position_z[3] = static_cast<std::byte>(response[temp_index++]);

            this->uwb_position_raw.anchor_list[i].rssi = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.anchor_list[i].seat_number_and_neighbor_network = static_cast<std::byte>(response[temp_index++]);
        }

        return true;
    }

    bool decode()
    {

        this->uwb_position_decoded.type_general = static_cast<std::uint8_t>(this->uwb_position_raw.type_general);
        this->uwb_position_decoded.length_general = static_cast<std::uint8_t>(this->uwb_position_raw.length_general);
        this->uwb_position_decoded.value_err_code_general = static_cast<std::uint8_t>(this->uwb_position_raw.value_err_code_general);
        this->uwb_position_decoded.type = static_cast<std::uint8_t>(this->uwb_position_raw.type);
        this->uwb_position_decoded.length = static_cast<std::uint8_t>(this->uwb_position_raw.length);

        this->uwb_position_decoded.number_of_elements = static_cast<std::uint8_t>(this->uwb_position_raw.number_of_elements);

        for (int i = 0; i < number_of_anchors; i++)
        {
            this->uwb_position_decoded.anchor_list[i].uwb_address = static_cast<int16_t>(static_cast<std::uint16_t>(static_cast<std::uint16_t>(this->uwb_position_raw.anchor_list[i].uwb_address[1]) << 8 | static_cast<std::uint16_t>(this->uwb_position_raw.anchor_list[i].uwb_address[0])));

            this->uwb_position_decoded.anchor_list[i].value_position_x = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_x[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_x[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_x[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_x[0]));
            this->uwb_position_decoded.anchor_list[i].value_position_y = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_y[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_y[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_y[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_y[0]));
            this->uwb_position_decoded.anchor_list[i].value_position_z = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_z[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_z[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_z[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.anchor_list[i].value_position_z[0]));
            this->uwb_position_decoded.anchor_list[i].rssi = static_cast<std::int8_t>(this->uwb_position_raw.anchor_list[i].rssi);
            this->uwb_position_decoded.anchor_list[i].seat_number_and_neighbor_network = static_cast<std::uint8_t>(this->uwb_position_raw.anchor_list[i].seat_number_and_neighbor_network);
        }
        return true;
    }

    void display() // TODO: finish displaying
    {
        std::cout << std::dec << "\nGeneral Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Type: " << static_cast<unsigned>(this->uwb_position_decoded.type) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type) << "\n";
        std::cout << std::dec << "Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length) << "\n";
        std::cout << std::dec << "Number of anchors: " << static_cast<unsigned>(this->uwb_position_decoded.number_of_elements) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.number_of_elements) << "\n";

        std::cout << std::dec << "Printing out the data of each anchors: \n";
        for (int i = 0; i < number_of_anchors; i++)
        {
            std::cout << std::dec << "Anchor number: " << i + 1 << "\n";
            std::cout << std::dec << "UWB Address: " << this->uwb_position_decoded.anchor_list[i].uwb_address << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.anchor_list->uwb_address[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].uwb_address[1]) << std::setfill(' ') << "\n";

            std::cout << std::dec << "Position x [mm]: " << this->uwb_position_decoded.anchor_list[i].value_position_x << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_x[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_x[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_x[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_x[3]) << std::setfill(' ') << "\n";
            std::cout << std::dec << "Position y [mm]: " << this->uwb_position_decoded.anchor_list[i].value_position_y << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_y[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_y[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_y[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_y[3]) << std::setfill(' ') << "\n";
            std::cout << std::dec << "Position z [mm]: " << this->uwb_position_decoded.anchor_list[i].value_position_z << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_z[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_z[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_z[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].value_position_z[3]) << std::setfill(' ') << "\n";

            std::cout << std::dec << "RSSI: " << static_cast<unsigned>(this->uwb_position_decoded.anchor_list[i].rssi) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].rssi) << "\n";
            std::cout << std::dec << "Seat number and neighbornetwork: " << static_cast<unsigned>(this->uwb_position_decoded.anchor_list[i].seat_number_and_neighbor_network) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.anchor_list[i].seat_number_and_neighbor_network) << "\n";
        }
    }
};

struct DwmLocGet
{
    ApiFunction api_function = DWM_LOC_GET;

    std::uint8_t request[2] = {0x0C, 0x00};
    std::uint16_t read_size = 101;

    std::uint8_t number_of_anchors = 4;

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

        ANxRawTag list_of_an[4];
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

        ANxDecodedTag list_of_an[4];
    } uwb_position_decoded;

    bool read(std::vector<uint8_t> &response) // TODO: Here we again i think have to assume all AN4 are populated, and then just see how much we actually read, and then decide how much actual data is there.
    {
        // if (response.size()  != 3)
        // {
        // std::cout << "size of response: " << response.size() << "\n";
        //     return false;
        // }

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

        this->uwb_position_raw.type_specific = static_cast<std::byte>(response[18]);
        this->uwb_position_raw.length_specific = static_cast<std::byte>(response[19]);
        this->uwb_position_raw.value_distances_encoded = static_cast<std::byte>(response[20]);

        uint8_t temp_index = 21;
        for (int i = 0; i < number_of_anchors; i++)
        {
            this->uwb_position_raw.list_of_an[i].uwb_address[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].uwb_address[1] = static_cast<std::byte>(response[temp_index++]);

            this->uwb_position_raw.list_of_an[i].distance[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].distance[1] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].distance[2] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].distance[3] = static_cast<std::byte>(response[temp_index++]);

            this->uwb_position_raw.list_of_an[i].distance_quality_factor = static_cast<std::byte>(response[temp_index++]);

            this->uwb_position_raw.list_of_an[i].value_position_x[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_x[1] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_x[2] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_x[3] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_y[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_y[1] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_y[2] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_y[3] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_z[0] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_z[1] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_z[2] = static_cast<std::byte>(response[temp_index++]);
            this->uwb_position_raw.list_of_an[i].value_position_z[3] = static_cast<std::byte>(response[temp_index++]);

            this->uwb_position_raw.list_of_an[i].value_quality_factor = static_cast<std::byte>(response[temp_index++]);
        }

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

        this->uwb_position_decoded.value_quality_factor = static_cast<uint8_t>(this->uwb_position_raw.value_quality_factor);

        this->uwb_position_decoded.type_specific = static_cast<std::uint8_t>(this->uwb_position_raw.type_specific);
        this->uwb_position_decoded.length_specific = static_cast<std::uint8_t>(this->uwb_position_raw.length_specific);

        this->uwb_position_decoded.value_distances_encoded = static_cast<std::uint8_t>(this->uwb_position_raw.value_distances_encoded);

        for (int i = 0; i < number_of_anchors; i++)
        {
            this->uwb_position_decoded.list_of_an[i].uwb_address = static_cast<int16_t>(static_cast<std::uint16_t>(static_cast<std::uint16_t>(this->uwb_position_raw.list_of_an[i].uwb_address[1]) << 8 | static_cast<std::uint16_t>(this->uwb_position_raw.list_of_an[i].uwb_address[0])));

            this->uwb_position_decoded.list_of_an[i].distance = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].distance[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].distance[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].distance[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].distance[0]));

            this->uwb_position_decoded.list_of_an[i].distance_quality_factor = static_cast<uint8_t>(this->uwb_position_raw.list_of_an[i].distance_quality_factor);

            this->uwb_position_decoded.list_of_an[i].value_position_x = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_x[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_x[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_x[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_x[0]));
            this->uwb_position_decoded.list_of_an[i].value_position_y = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_y[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_y[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_y[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_y[0]));
            this->uwb_position_decoded.list_of_an[i].value_position_z = static_cast<int32_t>(static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_z[3]) << 24 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_z[2]) << 16 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_z[1]) << 8 | static_cast<std::uint32_t>(this->uwb_position_raw.list_of_an[i].value_position_z[0]));
            this->uwb_position_decoded.list_of_an[i].value_quality_factor = static_cast<std::uint8_t>(this->uwb_position_raw.list_of_an[i].value_quality_factor);
        }

        return true;
    }

    void display() // TODO!
    {
        std::cout << std::dec << "\nGeneral Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
        std::cout << std::dec << "General Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_general) << "\n";
        std::cout << std::dec << "General Error Code: " << static_cast<unsigned>(this->uwb_position_decoded.value_err_code_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_err_code_general) << "\n";
        std::cout << std::dec << "Type: " << static_cast<unsigned>(this->uwb_position_decoded.type) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type) << "\n";
        std::cout << std::dec << "Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length) << "\n";
        std::cout << std::dec << "Position x [mm]: " << this->uwb_position_decoded.value_position_x << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_x[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_x[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Position y [mm]: " << this->uwb_position_decoded.value_position_y << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_y[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_y[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Position z [mm]: " << this->uwb_position_decoded.value_position_z << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.value_position_z[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.value_position_z[3]) << std::setfill(' ') << "\n";
        std::cout << std::dec << "Quality [%]: " << static_cast<unsigned>(this->uwb_position_decoded.value_quality_factor) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_quality_factor) << "\n";

        std::cout << std::dec << "Specific Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_specific) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_specific) << "\n";
        std::cout << std::dec << "Specific Length [B]: " << static_cast<unsigned>(this->uwb_position_decoded.length_specific) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.length_specific) << "\n";
        std::cout << std::dec << "Number of distnaces encoded: " << static_cast<unsigned>(this->uwb_position_decoded.value_distances_encoded) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.value_distances_encoded) << "\n";

        std::cout << std::dec << "Printing out the data of each anchors: \n";
        for (int i = 0; i < number_of_anchors; i++)
        {
            std::cout << std::dec << "Anchor number: " << i + 1 << "\n";

            std::cout << std::dec << "UWB Address: " << this->uwb_position_decoded.list_of_an[i].uwb_address << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].uwb_address[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].uwb_address[1]) << std::setfill(' ') << "\n";
            std::cout << std::dec << "Distance [mm]: " << this->uwb_position_decoded.list_of_an[i].distance << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].distance[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].distance[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].distance[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].distance[3]) << std::setfill(' ') << "\n";
            std::cout << std::dec << "Distance quality [%]: " << static_cast<unsigned>(this->uwb_position_decoded.list_of_an[i].distance_quality_factor) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].distance_quality_factor) << "\n";

            std::cout << std::dec << "Position x [mm]: " << this->uwb_position_decoded.list_of_an[i].value_position_x << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_x[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_x[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_x[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_x[3]) << std::setfill(' ') << "\n";
            std::cout << std::dec << "Position y [mm]: " << this->uwb_position_decoded.list_of_an[i].value_position_y << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_y[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_y[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_y[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_y[3]) << std::setfill(' ') << "\n";
            std::cout << std::dec << "Position z [mm]: " << this->uwb_position_decoded.list_of_an[i].value_position_z << "\t" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_z[0]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_z[1]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_z[2]) << " " << std::setw(2) << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_position_z[3]) << std::setfill(' ') << "\n";
            std::cout << std::dec << "Quality [%]: " << static_cast<unsigned>(this->uwb_position_decoded.list_of_an[i].value_quality_factor) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.list_of_an[i].value_quality_factor) << "\n";
        }
    }
};

struct DwmPosGet
{
    ApiFunction api_function = DWM_POS_GET;

    std::uint8_t request[2] = {0x02, 0x00};
    std::uint16_t read_size = 18;

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

    bool read(const std::vector<uint8_t> &response)
    {
        if (response.size() != read_size)
        {
            std::cout << "size of response: " << response.size() << "\n";
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
        std::cout << std::dec << "\nGeneral Type: " << static_cast<unsigned>(this->uwb_position_decoded.type_general) << "\t" << std::hex << std::uppercase << static_cast<unsigned>(this->uwb_position_raw.type_general) << "\n";
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
    ApiFunction current_request_function;

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
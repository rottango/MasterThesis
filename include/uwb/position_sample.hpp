
#pragma once

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>

enum UwbErrorCode{
    OK,
    UNKNOWN_OR_BROKEN_TLV,
    INTERNAL_ERROR,
    INVALID_PARAMETER,
    BUSY,
    OPERATION_NOT_PERMITTED,
    UNRECOGNIZED_ERROR_CODE
};

inline std::string errorCodeToText(const UwbErrorCode &error_code){
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
    return "ERROR";
};

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
};

struct UwbPositionDecoded{
    std::int32_t value_position_x;
    std::int32_t value_position_y;
    std::int32_t value_position_z;
    std::uint8_t type_general;
    std::uint8_t length_general;
    std::uint8_t value_err_code_general;
    std::uint8_t type;
    std::uint8_t length;
    std::uint8_t value_quality_factor;
};

inline bool decodeUwbPosition(const struct UwbPositionRaw &UwbPositionRaw, struct UwbPositionDecoded &UwbPositionDecoded){

    UwbPositionDecoded.type_general = static_cast<std::uint8_t>(UwbPositionRaw.type_general);
    UwbPositionDecoded.length_general = static_cast<std::uint8_t>(UwbPositionRaw.length_general);
    UwbPositionDecoded.value_err_code_general = static_cast<std::uint8_t>(UwbPositionRaw.value_err_code_general);
    UwbPositionDecoded.type = static_cast<std::uint8_t>(UwbPositionRaw.type);
    UwbPositionDecoded.length = static_cast<std::uint8_t>(UwbPositionRaw.length);


    UwbPositionDecoded.value_position_x = static_cast<int32_t>(static_cast<std::uint32_t>(UwbPositionRaw.value_position_x[3]) << 24 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_x[2]) << 16 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_x[1]) << 8 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_x[0]));
    UwbPositionDecoded.value_position_y = static_cast<int32_t>(static_cast<std::uint32_t>(UwbPositionRaw.value_position_y[3]) << 24 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_y[2]) << 16 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_y[1]) << 8 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_y[0]));
    UwbPositionDecoded.value_position_z = static_cast<int32_t>(static_cast<std::uint32_t>(UwbPositionRaw.value_position_z[3]) << 24 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_z[2]) << 16 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_z[1]) << 8 | static_cast<std::uint32_t>(UwbPositionRaw.value_position_z[0]));

    UwbPositionDecoded.value_quality_factor = static_cast<std::uint8_t>(UwbPositionRaw.value_quality_factor);

    return true;
}

inline void displayUwbPositionData(const struct UwbPositionDecoded &UwbPositionDecoded, const struct UwbPositionRaw &UwbPositionRaw){
    std::cout<<std::dec<<"General Type: "<<static_cast<unsigned>(UwbPositionDecoded.type_general)<<"\t" <<std::hex << std::uppercase << static_cast<unsigned>(UwbPositionRaw.type_general)<<"\n";
    std::cout<<std::dec<<"General Length [B]: "<<static_cast<unsigned>(UwbPositionDecoded.length_general)<<"\t" <<std::hex << std::uppercase << static_cast<unsigned>(UwbPositionRaw.length_general)<<"\n";
    std::cout<<std::dec<<"General Error Code: "<<static_cast<unsigned>(UwbPositionDecoded.value_err_code_general)<<"\t" <<std::hex << std::uppercase << static_cast<unsigned>(UwbPositionRaw.value_err_code_general)<<"\n";
    std::cout<<std::dec<<"Type: "<<static_cast<unsigned>(UwbPositionDecoded.type)<<"\t" <<std::hex << std::uppercase << static_cast<unsigned>(UwbPositionRaw.type)<<"\n";
    std::cout<<std::dec<<"Length [B]: "<<static_cast<unsigned>(UwbPositionDecoded.length)<<"\t" <<std::hex << std::uppercase << static_cast<unsigned>(UwbPositionRaw.length)<<"\n";
    std::cout<<std::dec<<"Position x [mm]: "<<UwbPositionDecoded.value_position_x<<"\t" <<std::hex << std::uppercase << std::setw(2)<< std::setfill('0') << static_cast<unsigned>(UwbPositionRaw.value_position_x[0]) <<" "<<std::setw(2)<<static_cast<unsigned>(UwbPositionRaw.value_position_x[1]) <<" "<<std::setw(2)<< static_cast<unsigned>(UwbPositionRaw.value_position_x[2]) <<" "<<std::setw(2)<<static_cast<unsigned>(UwbPositionRaw.value_position_x[3]) <<std::setfill(' ')<<"\n";
    std::cout<<std::dec<<"Position y [mm]: "<<UwbPositionDecoded.value_position_y<<"\t" <<std::hex << std::uppercase << std::setw(2)<< std::setfill('0') << static_cast<unsigned>(UwbPositionRaw.value_position_y[0]) <<" "<<std::setw(2)<<static_cast<unsigned>(UwbPositionRaw.value_position_y[1]) <<" "<<std::setw(2)<< static_cast<unsigned>(UwbPositionRaw.value_position_y[2]) <<" "<<std::setw(2)<<static_cast<unsigned>(UwbPositionRaw.value_position_y[3]) <<std::setfill(' ')<<"\n";
    std::cout<<std::dec<<"Position z [mm]: "<<UwbPositionDecoded.value_position_z<<"\t" <<std::hex << std::uppercase << std::setw(2)<< std::setfill('0') << static_cast<unsigned>(UwbPositionRaw.value_position_z[0]) <<" "<<std::setw(2)<<static_cast<unsigned>(UwbPositionRaw.value_position_z[1]) <<" "<<std::setw(2)<< static_cast<unsigned>(UwbPositionRaw.value_position_z[2]) <<" "<<std::setw(2)<<static_cast<unsigned>(UwbPositionRaw.value_position_z[3]) <<std::setfill(' ')<<"\n";
    std::cout<<std::dec<<"Quality [%]: "<<static_cast<unsigned>(UwbPositionDecoded.value_quality_factor)<<"\t" <<std::hex << std::uppercase << static_cast<unsigned>(UwbPositionRaw.value_quality_factor)<<"\n";
}


inline UwbErrorCode verifyErrorCode(const struct UwbPositionDecoded &UwbPositionDecoded){
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

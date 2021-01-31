//
// Created by nicola on 31/01/2021.
//
#pragma once

#include <cstdint>
#include <string>

enum MouseStatusProps
{
    MSP_NAME = 1 << 0,
    MSP_LEGCOUNT = 1 << 1,
    MSP_HEADCOUNT = 1 << 2,
    MSP_HEALTH = 1 << 3,
    MSP_MAX
};

class MouseStatus {
public:
    void Write(class OutputMemoryBitStream& stream, uint32_t props);
    void Read(class InputMemoryBitStream& stream);

    std::string name;
    uint16_t leg_count;
    uint16_t head_count;
    uint16_t health;
};



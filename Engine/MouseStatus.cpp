//
// Created by nicola on 31/01/2021.
//

#include "MouseStatus.h"
#include "MemoryStream.h"
#include "RoboMath.h"

void MouseStatus::Write(OutputMemoryBitStream &stream, uint32_t props) {

    stream.WriteBits(props, GetRequiredBits<MSP_MAX>::Value);

    if ((props & MSP_NAME) != 0)
    {
        stream.Write(name);
    }
    if ((props & MSP_LEGCOUNT) != 0)
    {
        stream.Write(leg_count);
    }
    if ((props & MSP_HEADCOUNT) != 0)
    {
        stream.Write(head_count);
    }
    if ((props & MSP_HEALTH) != 0)
    {
        stream.Write(health);
    }
}

void MouseStatus::Read(InputMemoryBitStream &stream) {

    uint32_t written_props;
    stream.Read(written_props, GetRequiredBits<MSP_MAX>::Value);

    if ((written_props & MSP_NAME) != 0) {
        stream.Read(name);
    }
    if ((written_props & MSP_LEGCOUNT) != 0) {
        stream.Read(leg_count);
    }
    if ((written_props & MSP_HEADCOUNT) != 0) {
        stream.Read(head_count);
    }
    if ((written_props & health) != 0)
    {
        stream.Read(health);
    }
}

//
// Created by nicola on 27/01/2021.
//
#pragma once


#include <cstdint>

enum ReplicatedAction
{
    RA_CREATE,
    RA_UPDATE,
    RA_DESTROY,
    RA_MAX
};

class ReplicationHeader {
public:
    ReplicationHeader() = default;
    ReplicationHeader(ReplicatedAction action, uint32_t networkId, uint32_t classId) :
            m_ReplicatedAction(action),
            m_NetworkID(networkId),
            m_ClassID(classId)
    {

    }

    void Write(class OutputMemoryBitStream& stream);
    void Read(class InputMemoryBitStream& stream);

    ReplicatedAction m_ReplicatedAction;
    uint32_t m_NetworkID;
    uint32_t m_ClassID;
};

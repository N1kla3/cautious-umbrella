//
// Created by nicola on 27/01/2021.
//

#include "ReplicationHeader.h"
#include "MemoryStream.h"
#include "RoboMath.h"

void ReplicationHeader::Write(OutputMemoryBitStream &stream) {
    stream.WriteBits(m_ReplicatedAction, GetRequiredBits<RA_MAX>::Value);
    stream.Write(m_NetworkID);
    if (m_ReplicatedAction != RA_DESTROY)
    {
        stream.Write(m_ClassID);
    }
}

void ReplicationHeader::Read(InputMemoryBitStream &stream) {
    stream.Read(m_ReplicatedAction, GetRequiredBits<RA_MAX>::Value);
    stream.Read(m_NetworkID);
    if (m_ReplicatedAction != RA_DESTROY)
    {
        stream.Read(m_ClassID);
    }
}

//
// Created by nicola on 05/02/2021.
//

#include "RPCManager.h"
#include "MemoryStream.h"
#include <cassert>

void RPCManager::RegisterUnwrapFunction(uint32_t name, RPCUnwrapFunc func)
{
    assert(m_NameToRPCTable.find(name) == m_NameToRPCTable.end());
    m_NameToRPCTable[name] = func;
}

void RPCManager::ProcessRPC(InputMemoryBitStream &stream)
{
    uint32_t name;
    stream.Read(name);
    m_NameToRPCTable.at(name)(stream);
}

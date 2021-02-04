//
// Created by nicola on 05/02/2021.
//

#pragma once

#include <cstdint>
#include <unordered_map>

typedef void (*RPCUnwrapFunc)(class InputMemoryBitStream&);

class RPCManager
{
public:
    void RegisterUnwrapFunction(uint32_t name, RPCUnwrapFunc func);
    void ProcessRPC(InputMemoryBitStream& stream);

private:
    std::unordered_map<uint32_t, RPCUnwrapFunc> m_NameToRPCTable{};
};


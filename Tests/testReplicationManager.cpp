//
// Created by nicola on 25/01/2021.
//
#include "gtest/gtest.h"
#include "../Engine/ReplicationManager.h"
#include "../Engine/LinkingContext.hpp"
#include "../Engine/GameObject.h"
#include "../Engine/RPCManager.h"

TEST(ReplicationManager, worldstate)
{
    OutputMemoryBitStream outStream;
    char *buffer = nullptr;
    InputMemoryBitStream inStream(buffer, 32);

    auto link = new LinkingContext();
    ReplicationManager manager(link);
    auto first = new GameObject;
    auto second = new GameObject;
    manager.ReplicateWorldState(outStream, {first, second});
    //TODO need to think
}

TEST(ReplicationManager, repHeader)
{

}

void UnwrapFunction(InputMemoryBitStream& stream)
{
    std::cout << "hell0";
}

TEST(ReplicationManager, RPCmanager)
{
    RPCManager manager;
    manager.RegisterUnwrapFunction('PSND', UnwrapFunction);
    //TODO write mock for streams for good tests
}
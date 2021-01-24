//
// Created by nicola on 05/01/2021.
//
#pragma once

#include <vector>

class OutputMemoryBitStream;
class GameObject;
class LinkingContext;

enum PacketType
{
    PT_HELLO,
    PT_REPLICATIONDATA,
    PT_DISCONNECT,
    PT_MAX
};

class ReplicationManager {
public:
    void ReplicateWorldState(OutputMemoryBitStream& inStream, const std::vector<GameObject*>& allObjects);
private:
    void ReplicateIntoStream(OutputMemoryBitStream& stream, GameObject* gameObject);

    LinkingContext* m_LinkingContext;
};


//
// Created by nicola on 05/01/2021.
//
#pragma once

#include <vector>
#include <unordered_set>

class OutputMemoryBitStream;
class InputMemoryBitStream;
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

    void ReceiveReplicatedWorld(InputMemoryBitStream& outStream);

private:
    void ReplicateIntoStream(OutputMemoryBitStream& stream, GameObject* gameObject);

    GameObject* ReceiveReplicatedObject(InputMemoryBitStream& stream);

    LinkingContext* m_LinkingContext;

    std::unordered_set<GameObject*> m_ObjectReplicatedToMe;
};

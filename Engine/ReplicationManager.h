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
    explicit ReplicationManager(LinkingContext *link_context) :
            m_LinkingContext(link_context)
    {

    }

    void ReplicateWorldState(OutputMemoryBitStream& inStream, const std::vector<GameObject*>& allObjects);

    void ReceiveReplicatedWorld(InputMemoryBitStream& outStream, class ObjectCreationRegistry* registry);

    void ReplicateCreate(OutputMemoryBitStream& stream, GameObject* gameObject);
    void ReplicateDestroy(OutputMemoryBitStream& stream, GameObject* gameObject);
    void ReplicateUpdate(OutputMemoryBitStream& stream, GameObject* gameObject);

    void ProcessReplicationData(InputMemoryBitStream& stream, class ObjectCreationRegistry* registry);
private:
    void ReplicateIntoStream(OutputMemoryBitStream& stream, GameObject* gameObject);

    GameObject *ReceiveReplicatedObject(InputMemoryBitStream &stream, class ObjectCreationRegistry * registry);

    LinkingContext* m_LinkingContext;

    std::unordered_set<GameObject*> m_ObjectReplicatedToMe{};
};


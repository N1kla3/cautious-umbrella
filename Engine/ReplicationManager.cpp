//
// Created by nicola on 05/01/2021.
//

#include "ObjectCreationRegistry.h"
#include "ReplicationManager.h"
#include "LinkingContext.hpp"
#include "MemoryStream.h"
#include "RoboMath.h"
#include "ReplicationHeader.h"

void ReplicationManager::ReplicateWorldState(OutputMemoryBitStream &inStream, const std::vector<GameObject *> &allObjects) {
    inStream.WriteBits(PT_REPLICATIONDATA, GetRequiredBits<PT_MAX>::Value);

    for (auto object : allObjects)
    {
        ReplicateIntoStream(inStream, object);
    }
}

void ReplicationManager::ReplicateIntoStream(OutputMemoryBitStream &stream, GameObject *gameObject) {
    stream.Write(m_LinkingContext->GetNetworkId(gameObject));
    stream.Write(gameObject->GetClassId());
    gameObject->Write(stream);
}

void ReplicationManager::ReceiveReplicatedWorld(InputMemoryBitStream& outStream) {
    std::unordered_set<GameObject*> received_objects;

    while (outStream.GetRemainingBitCount() > 0)
    {
        auto received_object = ReceiveReplicatedObject(outStream, nullptr);
        received_objects.insert(received_object);
    }

    for (auto go : m_ObjectReplicatedToMe)
    {
        if (received_objects.find(go) != received_objects.end())
        {
            m_LinkingContext->RemoveGameObject(go);
            delete go;//TODO: for now
        }
    }

    m_ObjectReplicatedToMe = received_objects;
}

GameObject *ReplicationManager::ReceiveReplicatedObject(InputMemoryBitStream &stream, ObjectCreationRegistry* registry) {
    uint32_t network_id;
    uint32_t class_id;
    stream.Read(network_id);
    stream.Read(class_id);

    auto go = m_LinkingContext->GetGameObject(network_id);
    if (!go)
    {
        go = registry->CreateGameObject(class_id);
        m_LinkingContext->AddGameObject(go, network_id);
    }

    go->Read(stream);

    return go;
}

void ReplicationManager::ReplicateCreate(OutputMemoryBitStream &stream, GameObject *gameObject) {
    ReplicationHeader header(RA_CREATE, m_LinkingContext->GetNetworkId(gameObject), gameObject->GetClassId());
    header.Write(stream);
    gameObject->Write(stream);
}

void ReplicationManager::ReplicateDestroy(OutputMemoryBitStream &stream, GameObject *gameObject) {
    ReplicationHeader header(RA_DESTROY, m_LinkingContext->GetNetworkId(gameObject, false), gameObject->GetClassId());
    header.Write(stream);
}

void ReplicationManager::ReplicateUpdate(OutputMemoryBitStream &stream, GameObject *gameObject) {
    ReplicationHeader header(RA_UPDATE, m_LinkingContext->GetNetworkId(gameObject, false), gameObject->GetClassId());
    header.Write(stream);
    gameObject->Write(stream);
}

void ReplicationManager::ProcessReplicationData(InputMemoryBitStream &stream, ObjectCreationRegistry* registry) {
    ReplicationHeader header{};
    header.Read(stream);

    switch (header.m_ReplicatedAction) {
        case RA_UPDATE:
        {
            auto go = m_LinkingContext->GetGameObject(header.m_NetworkID);
            if (go)
            {
                go->Read(stream);
            }
            else
            {
                auto class_id = header.m_ClassID;
                go = registry->CreateGameObject(class_id);
                go->Read(stream);
                delete go;
            }
            break;
        }

        case RA_CREATE:
        {
            auto go = registry->CreateGameObject(header.m_ClassID);
            m_LinkingContext->AddGameObject(go, header.m_NetworkID);
            go->Read(stream);
            break;
        }

        case RA_DESTROY:
        {
            auto go = m_LinkingContext->GetGameObject(header.m_NetworkID);
            m_LinkingContext->RemoveGameObject(go);
            delete go; //TODO for now
            break;
        }

        default:
        {
            break;
        }
    }
}

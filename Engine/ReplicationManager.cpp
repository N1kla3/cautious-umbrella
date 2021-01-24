//
// Created by nicola on 05/01/2021.
//

#include "ReplicationManager.h"
#include "LinkingContext.hpp"
#include "GameObject.h"
#include "MemoryStream.h"
#include "RoboMath.h"

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

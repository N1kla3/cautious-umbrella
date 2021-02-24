//
// Created by nicola on 29/12/2020.
//
#pragma once

#include <cstdint>
#include <unordered_map>

class GameObject;

class LinkingContext {
public:

    LinkingContext() :
            m_NextNetworkId(1)
    {

    }

    uint32_t GetNetworkId(GameObject *inGameObject, bool inShouldCreateIfNotFound = true) {
        auto it = m_GameObjectToNetworkIdMap.find(inGameObject);
        if (it != m_GameObjectToNetworkIdMap.end()) {
            return it->second;
        } else if (inShouldCreateIfNotFound) {
            uint32_t newNetworkId = m_NextNetworkId++;
            AddGameObject(inGameObject, newNetworkId);
            return newNetworkId;
        } else {
            return 0;
        }
    }

    [[nodiscard]] GameObject *GetGameObject(uint32_t inNetworkId) const {
        auto it = m_NetworkIdToGameObjectMap.find(inNetworkId);
        if (it != m_NetworkIdToGameObjectMap.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    void AddGameObject(GameObject *inGameObject, uint32_t inNetworkId) {
        m_NetworkIdToGameObjectMap[inNetworkId] = inGameObject;
        m_GameObjectToNetworkIdMap[inGameObject] = inNetworkId;
    }

    void RemoveGameObject(GameObject *inGameObject) {
        uint32_t network_id = m_GameObjectToNetworkIdMap[inGameObject];
        m_GameObjectToNetworkIdMap.erase(inGameObject);
        m_NetworkIdToGameObjectMap.erase(network_id);
    }

private:
    std::unordered_map<uint32_t, GameObject *> m_NetworkIdToGameObjectMap{};
    std::unordered_map<const GameObject *, uint32_t> m_GameObjectToNetworkIdMap{};

    uint32_t m_NextNetworkId;
};
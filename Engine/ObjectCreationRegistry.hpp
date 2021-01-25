//
// Created by nicola on 29/12/2020.
//
#pragma once

#include <cassert>
#include "GameObject.h"

typedef GameObject* (*GameObjectCreationFunc)();

class ObjectCreationRegistry {
public:
    static ObjectCreationRegistry& Get()
    {
        static ObjectCreationRegistry sInstance;
        return sInstance;
    }

    template<class T>
    void RegisterCreationFunction()
    {
        assert(m_NameToGameObjectCreationFunctionMap.find(T::ClassId)
               == m_NameToGameObjectCreationFunctionMap.end());
        m_NameToGameObjectCreationFunctionMap[T::ClassId] = T::CreateInstance;
    }

    GameObject* CreateGameObject(uint32_t ClassId)
    {
        GameObjectCreationFunc creationFunc = m_NameToGameObjectCreationFunctionMap[ClassId];
        if (creationFunc) {
            GameObject *gameObject = creationFunc();
            return gameObject;
        }
        return nullptr;
    }
//TODO: remove singleton
private:
    ObjectCreationRegistry()= default;
    std::unordered_map<uint32_t, GameObjectCreationFunc> m_NameToGameObjectCreationFunctionMap;
};

void RegisterObjectCreation()
{
    ObjectCreationRegistry::Get().RegisterCreationFunction<GameObject>();
}


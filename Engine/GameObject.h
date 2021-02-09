//
// Created by nicola on 29/12/2020.
//
#pragma once

#include <cstdint>
#include <memory>
#include "MemoryStream.h"
#include "RoboMath.h"

#define CLASS_IDENTIFICATION(Code, Class) \
enum{ClassId = Code};                     \
virtual uint32_t GetClassId() const {return ClassId;} \
static GameObject* CreateInstance() {return new Class();}

class GameObject {
public:
    CLASS_IDENTIFICATION('GOBJ', GameObject)

    GameObject();
    virtual ~GameObject();

    virtual uint32_t GetAllStateMask() const;
    virtual void Update();
    virtual void HandleDying();

    //Getters and setters
    [[nodiscard]] const Vector3& GetLocation() const;
    void SetLocation(const Vector3& vector) noexcept;

    [[nodiscard]] const Vector3& GetColor() const;
    void SetColor(const Vector3& color) noexcept;

    [[nodiscard]] float GetCollisionRadius() const;
    void SetCollisionRadius(float radius) noexcept;

    [[nodiscard]] float GetRotation() const;
    void SetRotation(float rotation) noexcept;

    [[nodiscard]] float GetScale() const;
    void SetScale(float scale) noexcept;

    [[nodiscard]] int GetWorldIndex() const;
    void SetWorldIndex(int worldIndex) noexcept;

    [[nodiscard]] int GetNetworkId() const;
    void SetNetworkId(int networkId) noexcept;

    [[nodiscard]] bool DoesWantToDie() const;
    void SetDoesWantToDie(bool value) noexcept;

    virtual void Write(OutputMemoryBitStream& inStream);

    virtual void Read(InputMemoryBitStream& outStream);

private:
    Vector3 m_Location{};
    Vector3 m_Color;

    float m_CollisionRadius;

    float m_Rotation;
    float m_Scale;

    int m_IndexInWorld;
    int m_NetworkId;

    bool m_DoesWantToDie;
};

typedef std::shared_ptr<GameObject> SharedGameObject;

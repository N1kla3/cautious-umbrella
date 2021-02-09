//
// Created by nicola on 29/12/2020.
//

#include "GameObject.h"

void GameObject::Write(OutputMemoryBitStream& inStream)
{
//TODO: write later
}

void GameObject::Read(InputMemoryBitStream& outStream)
{
//TODO: read later
}

GameObject::GameObject()
        : m_CollisionRadius(0.5f),
          m_DoesWantToDie(false),
          m_IndexInWorld(-1),
          m_NetworkId(0),
          m_Rotation(0.f),
          m_Scale(1.f),
          m_Color(Colors::White)
{

}

uint32_t GameObject::GetAllStateMask() const
{
    return 0;
}

void GameObject::Update()
{

}

void GameObject::HandleDying()
{

}

GameObject::~GameObject() = default;

const Vector3& GameObject::GetLocation() const
{
    return m_Location;
}

void GameObject::SetLocation(const Vector3& vector) noexcept
{
    m_Location = vector;
}

const Vector3& GameObject::GetColor() const
{
    return m_Color;
}

void GameObject::SetColor(const Vector3& color) noexcept
{
    m_Color = color;
}

float GameObject::GetCollisionRadius() const
{
    return m_CollisionRadius;
}

void GameObject::SetCollisionRadius(float radius) noexcept
{
    m_CollisionRadius = radius;
}

float GameObject::GetRotation() const
{
    return m_Rotation;
}

void GameObject::SetRotation(float rotation) noexcept
{
    m_Rotation = rotation;
}

float GameObject::GetScale() const
{
    return m_Scale;
}

void GameObject::SetScale(float scale) noexcept
{
    m_Scale = scale;
}

int GameObject::GetWorldIndex() const
{
    return m_IndexInWorld;
}

void GameObject::SetWorldIndex(int worldIndex) noexcept
{
    m_IndexInWorld = worldIndex;
}

int GameObject::GetNetworkId() const
{
    return m_NetworkId;
}

void GameObject::SetNetworkId(int networkId) noexcept
{
    m_NetworkId = networkId;
}

bool GameObject::DoesWantToDie() const
{
    return m_DoesWantToDie;
}

void GameObject::SetDoesWantToDie(bool value) noexcept
{
    m_DoesWantToDie = value;
}

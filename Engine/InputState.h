//
// Created by nicola on 12/02/2021.
//

#pragma once

class InputState
{
public:
    InputState() = default;

    [[nodiscard]]float GetHorizontalAmount() const;
    [[nodiscard]]float GetVerticalAmount() const;

    [[nodiscard]]bool IsShooting() const;

    void Write(class OutputMemoryBitStream& stream) const;
    void Read(class InputMemoryBitStream& stream);

private:
    float m_RightAmount = 0.f;
    float m_LeftAmount = 0.f;
    float m_UpAmount = 0.f;
    float m_DownAmount = 0.f;

    bool m_IsShooting{false};
};

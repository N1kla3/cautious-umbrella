//
// Created by nicola on 12/02/2021.
//

#include "InputState.h"
#include "MemoryStream.h"

namespace
{
    void WriteBinarySignedValue(OutputMemoryBitStream& stream, float value)
    {
        bool is_non_zero = value != 0.f;
        stream.Write(is_non_zero);
        if (is_non_zero)
        {
            stream.Write(value > 0.f);
        }
    }

    float ReadBinarySignedValue(InputMemoryBitStream& stream)
    {
        bool is_non_zero;
        stream.Read(is_non_zero);
        if (is_non_zero)
        {
            bool value;
            stream.Read(value);
            return value ? 1.f : -1.f;
        }
        else
        {
            return 0.f;
        }
    }
}

float InputState::GetHorizontalAmount() const
{
    return m_RightAmount - m_LeftAmount;
}

float InputState::GetVerticalAmount() const
{
    return m_UpAmount - m_DownAmount;
}

bool InputState::IsShooting() const
{
    return m_IsShooting;
}

void InputState::Write(OutputMemoryBitStream& stream) const
{
    WriteBinarySignedValue(stream, GetHorizontalAmount());
    WriteBinarySignedValue(stream, GetVerticalAmount());
    stream.Write(IsShooting());
}

void InputState::Read(InputMemoryBitStream& stream)
{
    m_RightAmount = ReadBinarySignedValue(stream);
    m_UpAmount = ReadBinarySignedValue(stream);
    stream.Read(m_IsShooting);
}
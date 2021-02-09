//
// Created by nicola on 10/02/2021.
//
#pragma once

#include <cstdint>

class Timing
{
public:
    Timing();

    void Update();

    float GetDeltaTime() const;

    double GetTime() const;

    float GetTimef() const;

    float GetFrameStartTime() const;

private:
    float m_DeltaTime;
    uint64_t m_DeltaTick;

    double m_LastFrameStartTime;
    float m_FrameStartTimef;
    double m_PerfCountDuration;
};

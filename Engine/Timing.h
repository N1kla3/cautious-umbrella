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

    [[nodiscard]] float GetDeltaTime() const;

    [[nodiscard]] double GetTime() const;

    [[nodiscard]] float GetTimef() const;

    [[nodiscard]] float GetFrameStartTime() const;

    static Timing instance;

private:
    float m_DeltaTime;
    uint64_t m_DeltaTick;

    double m_LastFrameStartTime;
    float m_FrameStartTimef;
    double m_PerfCountDuration;
};

//
// Created by nicola on 10/02/2021.
//

#include "Timing.h"
#include "chrono"

using namespace std::chrono;

constexpr float DESIRED_FRAME_TIME = 0.0166f;

Timing Timing::instance;

namespace
{
    high_resolution_clock::time_point StartTime;
}

Timing::Timing()
{
    ::StartTime = high_resolution_clock::now();
}

void Timing::Update()
{
    double current_time = GetTime();
    m_DeltaTime = (float) (current_time - m_LastFrameStartTime);

    while (m_DeltaTime < DESIRED_FRAME_TIME)
    {
        current_time = GetTime();
        m_DeltaTime = (float)(current_time - m_LastFrameStartTime);
    }

    m_LastFrameStartTime = current_time;
    m_FrameStartTimef = static_cast<float>(m_LastFrameStartTime);
}

float Timing::GetDeltaTime() const
{
    return m_DeltaTime;
}

double Timing::GetTime() const
{
    auto now = high_resolution_clock::now();
    auto ms = duration_cast<milliseconds>(now - StartTime).count();
    return static_cast<double>(ms) / 1000;
}

float Timing::GetTimef() const
{
    return (float)GetTime();
}

float Timing::GetFrameStartTime() const
{
    return m_FrameStartTimef;
}

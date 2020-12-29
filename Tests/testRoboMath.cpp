//
// Created by nicola on 28/12/2020.
//
#include "gtest/gtest.h"
#include "../Engine/RoboMath.h"

TEST(math, vector){
    Vector3 a;
    Vector3 b(0, 0, 0);
    Vector3 c(2, 2, 2);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a + c == c) << "correct sum";
    EXPECT_TRUE(a ==  Vector3::Zero);
    EXPECT_TRUE(c * 2.f == 2.f * c) << "correct product";
    auto vector = RoboMath::GetRandomVector(b, c);
}

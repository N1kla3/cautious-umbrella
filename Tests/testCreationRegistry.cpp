//
// Created by nicola on 29/12/2020.
//
#include "gtest/gtest.h"
#include "../Engine/ObjectCreationRegistry.hpp"

TEST(CreationRegistry, initilization){
    ObjectCreationRegistry::Get();
    RegisterObjectCreation();
    auto obj = ObjectCreationRegistry::Get().CreateGameObject('GOBJ');
    auto objnul = ObjectCreationRegistry::Get().CreateGameObject('asdg');
    EXPECT_TRUE(obj);
    EXPECT_FALSE(objnul);
}
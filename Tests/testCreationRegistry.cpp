//
// Created by nicola on 29/12/2020.
//
#include "gtest/gtest.h"
#include "../Engine/ObjectCreationRegistry.h"

TEST(CreationRegistry, initilization){
    ObjectCreationRegistry registr;
    registr.RegisterObjectCreation();
    auto obj = registr.CreateGameObject('GOBJ');
    auto objnul = registr.CreateGameObject('asdg');
    EXPECT_TRUE(obj);
    EXPECT_FALSE(objnul);
}
//
// Created by nicola on 29/12/2020.
//
#include "gtest/gtest.h"
#include "../Engine/LinkingContext.hpp"
#include "../Engine/GameObject.h"

TEST(Linking, creation){
     LinkingContext link;
     link.AddGameObject(new GameObject, 3);
     link.AddGameObject(new GameObject, 5);
     EXPECT_FALSE(link.GetGameObject(4));
}

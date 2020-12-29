//
// Created by nicola on 29/12/2020.
//
#include "gtest/gtest.h"
#include "../Engine/MemoryStream.h"

TEST(MemoryStream, unorderedMap){
    OutputMemoryBitStream stream;
    std::unordered_map<int, int> map;
    map[2] = 3;
    map[3] = 5;
    map[12] = 33;
    stream.Write(map);
    char* buff = const_cast<char *>(stream.GetBufferPtr());
    InputMemoryBitStream reader(buff, stream.GetBitLength());
    std::unordered_map<int, int> mape;
    reader.Read(mape);
    EXPECT_EQ(mape.at(2), 3);
    EXPECT_EQ(mape.at(12), 33);
    EXPECT_EQ(mape.at(3), 5);
    EXPECT_FALSE(mape.find(4) != mape.end());
}

TEST(MemoryStream, unorderedMapGenericRead){
    OutputMemoryBitStream stream;
    std::unordered_map<int, int> map;
    map[2] = 3;
    map[3] = 5;
    map[12] = 33;
    stream.Write(map);
    char* buff = const_cast<char *>(stream.GetBufferPtr());
    InputMemoryBitStream reader(buff, stream.GetBitLength());
    std::unordered_map<int, int> mape;
    reader.Read<int, int>(mape);
    EXPECT_EQ(mape.at(2), 3);
    EXPECT_EQ(mape.at(12), 33);
    EXPECT_EQ(mape.at(3), 5);
    EXPECT_FALSE(mape.find(4) != mape.end());
}
//
// Created by nicola on 29/12/2020.
//
#pragma once

#include <cstdint>

#define CLASS_IDENTIFICATION(Code, Class) \
enum{ClassId = Code};                     \
virtual uint32_t GetClassId() const {return ClassId;} \
static GameObject* CreateInstance() {return new Class();}

class GameObject {
public:
    CLASS_IDENTIFICATION('GOBJ', GameObject)
};


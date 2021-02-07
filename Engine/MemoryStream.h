//
// Created by nicola on 28/12/2020.
//
#pragma once

#include <cstdint>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unordered_map>

class GameObject;

class Vector3;

class Quaternion;

inline uint32_t ConvertToFixed(float inNumber, float inMin, float inPrecision) {
    return static_cast<int>((inNumber - inMin) / inPrecision );
}

inline float ConvertFromFixed(uint32_t inNumber, float inMin, float inPrecision) {
    return static_cast<float>( inNumber ) * inPrecision + inMin;
}


class OutputMemoryBitStream {

public:

    OutputMemoryBitStream() :
            m_BitHead(0),
            m_Buffer(nullptr) {
        ReallocBuffer(1500 * 8);
    }

    ~OutputMemoryBitStream() { std::free(m_Buffer); }

    void WriteBits(uint8_t inData, uint32_t inBitCount);

    void WriteBits(const void *inData, uint32_t inBitCount);

    [[nodiscard]] const char *GetBufferPtr() const { return m_Buffer; }

    [[nodiscard]] uint32_t GetBitLength() const { return m_BitHead; }

    [[nodiscard]] uint32_t GetByteLength() const { return (m_BitHead + 7) >> 3; }

    void WriteBytes(const void *inData, uint32_t inByteCount) { WriteBits(inData, inByteCount << 3); }

    /*
    void Write( uint32_t inData, uint32_t inBitCount = 32 )	{ WriteBits( &inData, inBitCount ); }
    void Write( int inData, uint32_t inBitCount = 32 )		{ WriteBits( &inData, inBitCount ); }
    void Write( float inData )								{ WriteBits( &inData, 32 ); }

    void Write( uint16_t inData, uint32_t inBitCount = 16 )	{ WriteBits( &inData, inBitCount ); }
    void Write( int16_t inData, uint32_t inBitCount = 16 )	{ WriteBits( &inData, inBitCount ); }

    void Write( uint8_t inData, uint32_t inBitCount = 8 )	{ WriteBits( &inData, inBitCount ); }
    */

    template<typename T>
    void Write(T inData, uint32_t inBitCount = sizeof(T) * 8) {
        static_assert(std::is_arithmetic<T>::value ||
                      std::is_enum<T>::value,
                      "Generic Write only supports primitive data types");
        WriteBits(&inData, inBitCount);
    }

    void Write(bool inData) { WriteBits(&inData, 1); }

    void Write(const Vector3 &inVector);

    void Write(const Quaternion &inQuat);

    void Write(const std::string &inString) {
        uint32_t elementCount = static_cast<uint32_t>( inString.size());
        Write(elementCount);
        for (const auto &element : inString) {
            Write(element);
        }
    }

    void Write(const std::unordered_map<int, int>& map);

protected:
    void ReallocBuffer(uint32_t inNewBitCapacity);

    char *m_Buffer;
    uint32_t m_BitHead;
    uint32_t m_BitCapacity;
};

class InputMemoryBitStream {

public:

    InputMemoryBitStream(char *inBuffer, uint32_t inBitCount) :
            m_Buffer(inBuffer),
            m_BitCapacity(inBitCount),
            m_BitHead(0),
            m_IsBufferOwner(false) {}

    InputMemoryBitStream(const InputMemoryBitStream &inOther) :
            m_BitCapacity(inOther.m_BitCapacity),
            m_BitHead(inOther.m_BitHead),
            m_IsBufferOwner(true) {
        //allocate buffer of right size
        int byteCount = m_BitCapacity / 8;
        m_Buffer = static_cast<char*>( malloc(byteCount));
        //copy
        std::memcpy(m_Buffer, inOther.m_Buffer, byteCount);
    }

    ~InputMemoryBitStream() { if (m_IsBufferOwner) { free(m_Buffer); }; }

    [[nodiscard]] const char *GetBufferPtr() const { return m_Buffer; }

    [[nodiscard]] uint32_t GetRemainingBitCount() const { return m_BitCapacity - m_BitHead; }

    void ReadBits(uint8_t &outData, uint32_t inBitCount);

    void ReadBits(void *outData, uint32_t inBitCount);

    void ReadBytes(void *outData, uint32_t inByteCount) { ReadBits(outData, inByteCount << 3); }

    template<typename T>
    void Read(T &inData, uint32_t inBitCount = sizeof(T) * 8) {
        static_assert(std::is_arithmetic<T>::value ||
                      std::is_enum<T>::value,
                      "Generic Read only supports primitive data types");
        ReadBits(&inData, inBitCount);
    }

    void Read(uint32_t &outData, uint32_t inBitCount = 32) { ReadBits(&outData, inBitCount); }

    void Read(int &outData, uint32_t inBitCount = 32) { ReadBits(&outData, inBitCount); }

    void Read(float &outData) { ReadBits(&outData, 32); }

    void Read(uint16_t &outData, uint32_t inBitCount = 16) { ReadBits(&outData, inBitCount); }

    void Read(int16_t &outData, uint32_t inBitCount = 16) { ReadBits(&outData, inBitCount); }

    void Read(uint8_t &outData, uint32_t inBitCount = 8) { ReadBits(&outData, inBitCount); }

    void Read(bool &outData) { ReadBits(&outData, 1); }

    void Read(Quaternion &outQuat);

    void ResetToCapacity(uint32_t inByteCapacity) {
        m_BitCapacity = inByteCapacity << 3;
        m_BitHead = 0;
    }


    void Read(std::string &inString) {
        uint32_t elementCount;
        Read(elementCount);
        inString.resize(elementCount);
        for (auto &element : inString) {
            Read(element);
        }
    }

    void Read(std::unordered_map<int, int>& map);

    template<typename tKey, typename tValue>
    void Read(std::unordered_map<tKey, tValue>& map){
        static_assert(std::is_arithmetic<tKey>::value ||
                      std::is_enum<tKey>::value &&
                      std::is_arithmetic<tValue>::value ||
                      std::is_enum<tValue>::value,
                      "Generic Read only supports primitive data types");
        size_t size;
        Read(size);
        for (auto i = 0; i < size; i++)
        {
            tKey key;
            tValue value;
            Read<tKey>(key);
            Read<tValue>(value);
            map[key] = value;
        }
    }

    void Read(Vector3 &inVector);

protected:
    char *m_Buffer;
    uint32_t m_BitHead;
    uint32_t m_BitCapacity;
    bool m_IsBufferOwner;
};


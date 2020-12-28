//
// Created by nicola on 28/12/2020.
//

#include "MemoryStream.h"
#include "RoboMath.h"

void OutputMemoryBitStream::WriteBits(uint8_t inData, uint32_t inBitCount) {
    uint32_t nextBitHead = m_BitHead + static_cast< uint32_t >( inBitCount );

    if (nextBitHead > m_BitCapacity) {
        ReallocBuffer(std::max(m_BitCapacity * 2, nextBitHead));
    }

    //calculate the byteOffset into our buffer
    //by dividing the head by 8
    //and the bitOffset by taking the last 3 bits
    uint32_t byteOffset = m_BitHead >> 3;
    uint32_t bitOffset = m_BitHead & 0x7;

    uint8_t currentMask = ~(0xff << bitOffset);
    m_Buffer[byteOffset] = (m_Buffer[byteOffset] & currentMask) | (inData << bitOffset);

    //calculate how many bits were not yet used in
    //our target byte in the buffer
    uint32_t bitsFreeThisByte = 8 - bitOffset;

    //if we needed more than that, carry to the next byte
    if (bitsFreeThisByte < inBitCount) {
        //we need another byte
        m_Buffer[byteOffset + 1] = inData >> bitsFreeThisByte;
    }

    m_BitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void *inData, uint32_t inBitCount) {
    const char *srcByte = static_cast< const char * >( inData );
    //write all the bytes
    while (inBitCount > 8) {
        WriteBits(*srcByte, 8);
        ++srcByte;
        inBitCount -= 8;
    }
    //write anything left
    if (inBitCount > 0) {
        WriteBits(*srcByte, inBitCount);
    }
}

void OutputMemoryBitStream::Write(const Vector3 &inVector) {
    Write(inVector.mX);
    Write(inVector.mY);
    Write(inVector.mZ);
}

void InputMemoryBitStream::Read(Vector3 &outVector) {
    Read(outVector.mX);
    Read(outVector.mY);
    Read(outVector.mZ);
}

void OutputMemoryBitStream::Write(const Quaternion &inQuat) {
    float precision = (2.f / 65535.f);
    Write(ConvertToFixed(inQuat.mX, -1.f, precision), 16);
    Write(ConvertToFixed(inQuat.mY, -1.f, precision), 16);
    Write(ConvertToFixed(inQuat.mZ, -1.f, precision), 16);
    Write(inQuat.mW < 0);
}


void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewBitLength) {
    if (m_Buffer == nullptr) {
        //just need to memset on first allocation
        m_Buffer = static_cast<char *>( std::malloc(inNewBitLength >> 3));
        memset(m_Buffer, 0, inNewBitLength >> 3);
    } else {
        //need to memset, then copy the buffer
        char *tempBuffer = static_cast<char *>( std::malloc(inNewBitLength >> 3));
        memset(tempBuffer, 0, inNewBitLength >> 3);
        memcpy(tempBuffer, m_Buffer, m_BitCapacity >> 3);
        std::free(m_Buffer);
        m_Buffer = tempBuffer;
    }

    //handle realloc failure
    //...
    m_BitCapacity = inNewBitLength;
}


void test1() {
    OutputMemoryBitStream mbs;

    mbs.WriteBits(11, 5);
    mbs.WriteBits(52, 6);
}

void InputMemoryBitStream::ReadBits(uint8_t &outData, uint32_t inBitCount) {
    uint32_t byteOffset = m_BitHead >> 3;
    uint32_t bitOffset = m_BitHead & 0x7;

    outData = static_cast< uint8_t >( m_Buffer[byteOffset] ) >> bitOffset;

    uint32_t bitsFreeThisByte = 8 - bitOffset;
    if (bitsFreeThisByte < inBitCount) {
        //we need another byte
        outData |= static_cast< uint8_t >( m_Buffer[byteOffset + 1] ) << bitsFreeThisByte;
    }

    //don't forget a mask so that we only read the bit we wanted...
    outData &= (~(0x00ff << inBitCount));

    m_BitHead += inBitCount;
}

void InputMemoryBitStream::ReadBits(void *outData, uint32_t inBitCount) {
    uint8_t *destByte = reinterpret_cast< uint8_t * >( outData );
    //write all the bytes
    while (inBitCount > 8) {
        ReadBits(*destByte, 8);
        ++destByte;
        inBitCount -= 8;
    }
    //write anything left
    if (inBitCount > 0) {
        ReadBits(*destByte, inBitCount);
    }
}

void InputMemoryBitStream::Read(Quaternion &outQuat) {
    float precision = (2.f / 65535.f);

    uint32_t f = 0;

    Read(f, 16);
    outQuat.mX = ConvertFromFixed(f, -1.f, precision);
    Read(f, 16);
    outQuat.mY = ConvertFromFixed(f, -1.f, precision);
    Read(f, 16);
    outQuat.mZ = ConvertFromFixed(f, -1.f, precision);

    outQuat.mW = sqrtf(1.f -
                       outQuat.mX * outQuat.mX +
                       outQuat.mY * outQuat.mY +
                       outQuat.mZ * outQuat.mZ);
    bool isNegative;
    Read(isNegative);

    if (isNegative) {
        outQuat.mW *= -1;
    }
}

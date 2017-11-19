#include <iostream>
#include <vector>
#include "PrimitiveTypedefs.h"
#include "Assert.h"
#include "include/2DGraphics/Image.h"
#include "BitReader.h"



/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class BitReader
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructors
*/
BitReader::BitReader(const std::vector<byte>& byteVec)
{
    this->byteVec.reserve(byteVec.size());
    this->byteVec.insert(this->byteVec.begin(), byteVec.begin(), byteVec.end());
    currentByteIndex = 0;
    currentBitIndex = 0;
}

/*
* Accessors
*/
bool BitReader::CurrentBitIndexIsValid() const
{
    return currentBitIndex >= 0 && currentBitIndex < 7;
}

bool BitReader::CurrentByteIndexIsValid() const
{
    return currentByteIndex >= 0 && (unsigned int)currentByteIndex < byteVec.size();
}

int BitReader::GetCurrentBitIndex() const
{
    return currentBitIndex;
}

int BitReader::GetCurrentByteIndex() const
{
    return currentByteIndex;
}

//long BitReader::PeekBitsAsLittleEndian(int numBitsToPeek) const
//{
//    long retVal = 0;
//    int tempCurrentBitIndex = currentBitIndex;
//    while (numBitsToPeek > 0)
//    {
//        if (numBitsToPeek > GetNumRemainingBitsInCurrentByte())
//        {
//        }
//        else
//        {
//            retVal = GetIsolatedBits(byteVec[currentByteIndex], currentBitIndex, currentBitIndex + numBitsToPeek - 1);
//        }
//    }
//    return retVal;
//}

long BitReader::PeekBitsAsLittleEndian(const int numBitsToPeek) const
{
    std::string messagePrefix = "BitReader.PeekBitsAsLittleEndian: ";
    long retVal = 0;
    int numBitsPeekedInThisRead = 0;
    int numBitsPeeked = 0;
    if (numBitsToPeek > GetNumRemainingBitsInCurrentByte())
    {
        int byteOffset = 0;
        while (numBitsPeeked != numBitsToPeek)
        {
            AssertTrue(numBitsPeeked < numBitsToPeek, messagePrefix + "numBitsPeekded >= numBitsToPeek");

            if ((unsigned int)(currentByteIndex + byteOffset) >= byteVec.size())
            {
                std::cout << "\n\n";
                std::cout << "Error: Tried reading non-existent bits!";
                std::cout << "\n\n";
                return 0;
            }
            
            int startBitIndex = (0 == byteOffset) ? currentBitIndex : 0;
            int endBitIndex = startBitIndex + (numBitsToPeek - numBitsPeeked) - 1;
            if (endBitIndex >= 8)
            {
                endBitIndex = 7;
            }
            int isolatedBits = PeekIsolatedBitsInByte(currentByteIndex + byteOffset, startBitIndex, endBitIndex);
            numBitsPeekedInThisRead = endBitIndex - startBitIndex + 1;
            numBitsPeeked += numBitsPeekedInThisRead;
            
            retVal = (isolatedBits << (numBitsPeeked - numBitsPeekedInThisRead)) | retVal;
            //retVal = (retVal << (endBitIndex - startBitIndex + 1)) | isolatedBits;
            if (7 == endBitIndex)
            {
                byteOffset++;
            }
        }
    }
    else
    {
        retVal = PeekIsolatedBitsInByte(currentByteIndex, currentBitIndex, currentBitIndex + numBitsToPeek - 1);
    }
    return retVal;
}

int BitReader::GetNumRemainingBitsInCurrentByte() const
{
    return 8 - currentBitIndex;
}

//To isolate bits, all bits in positions higher than endBitPosition and lower than startBitPosition should be zeroed out,
//and the isolated bit right-shifted so that the startBitPosition sits at the LSB.
//MSB               LSB
//*   * * * * * *   *
//<--higher position
//  lower position -->
//
//startBitePosition and endBitPosition are 0-based, and are inclusive bits in the bits to isolate.
int BitReader::PeekIsolatedBitsInByte(int byteIndex, int startBitPosition, int endBitPosition) const
{
    std::string messagePrefix = "BitReader.PeekIsolatedBits: ";
    AssertTrue(byteIndex >= 0 && (unsigned int)byteIndex < byteVec.size(), messagePrefix + "byteIndex < 0 || byteIndex >= byteVec.size()");
    AssertTrue(startBitPosition >= 0 && startBitPosition <= 7, messagePrefix + "startBitPosition < 0 || startBitPosition > 7");
    AssertTrue(endBitPosition >= startBitPosition && endBitPosition <= 7, 
                messagePrefix + "endBitPosition < startBitPosition || endBitPosition > 7");

    unsigned char retVal = byteVec[byteIndex];
    retVal = retVal << (7 - endBitPosition);
    retVal = retVal >> (7 - endBitPosition);
    retVal = retVal >> startBitPosition;
    return retVal;
}

//int BitReader::PeekIsolatedBitsInCurrentByte()
//{
//    std::string messagePrefix = "BitReader.GetIsolatedBits(): ";
//    AssertTrue(CurrentBitIndexIsValid(), messagePrefix + "!CurrentBitIndexIsValid()");
//    AssertTrue(CurrentByteIndexIsValid(), messagePrefix + "!CurrentByteIndexIsValid()");
//
//    int retVal = byteVec[currentByteIndex] >> currentBitIndex;
//    //currentBitIndex = 0;
//    //currentByteIndex++;
//    return retVal;
//}

//int BitReader::PeekIsolatedBitsInCurrentByte(int endBitPositionInclusive)
//{
//    std::string messagePrefix = "BitReader.GetIsolatedBits(int): ";
//    AssertTrue(CurrentBitIndexIsValid(), messagePrefix + "!CurrentBitIndexIsValid()");
//    AssertTrue(CurrentByteIndexIsValid(), messagePrefix + "!CurrentByteIndexIsValid()");
//    AssertTrue(endBitPositionInclusive >= currentBitIndex && endBitPositionInclusive <= 7, 
//                        messagePrefix + "endPostion < currentIndex || endPosition > 7");
//
//    int leftShiftAmount = 7 - endBitPositionInclusive;
//    int retVal = (byteVec[currentByteIndex] << leftShiftAmount) >> (leftShiftAmount + currentBitIndex);
//    //currentBitIndex = (endBitPositionInclusive + 1 > 7) ? 0 : endBitPositionInclusive + 1;
//    //currentByteIndex = (0 == currentBitIndex) ? currentByteIndex + 1 : currentByteIndex;
//    return retVal;
//}

/*
* Mutators
*/
long BitReader::GetBitsAsLittleEndian(int numBitsToGet)
{
    long retVal = PeekBitsAsLittleEndian(numBitsToGet);
    int tempCurrentBitIndex = currentBitIndex;
    currentBitIndex = (numBitsToGet + tempCurrentBitIndex) % 8;
    currentByteIndex += (numBitsToGet + tempCurrentBitIndex) / 8;
    return retVal;
}



/*
* ----------------------------------------------------------------------------------------------
* NOTE: Can delete all of these test functions after the BitReaderTestRunner methods have been written.
* ----------------------------------------------------------------------------------------------
*/
/*
* Global functions
*/
//void TestBitReader_Constructor()
//{
//    const int expectedValue1 = 25;
//    const int expectedValue2 = 36;
//    const int expectedValue3 = 49;
//    std::vector<byte> byteVec;
//    byteVec.push_back(expectedValue1);
//    byteVec.push_back(expectedValue2);
//    byteVec.push_back(expectedValue3);
//    BitReader bitReader = BitReader(byteVec);
//    
//    int actualValue1 = bitReader.GetBitsAsLittleEndian(8);
//    int actualValue2 = bitReader.GetBitsAsLittleEndian(8);
//    int actualValue3 = bitReader.GetBitsAsLittleEndian(8);
//    std::string errorMessage1 = "TestBitReader_Constructor error: byteVec value expected=" + std::to_string(expectedValue1) + ", actual=" + std::to_string(actualValue1);
//    std::string errorMessage2 = "TestBitReader_Constructor error: byteVec value expected=" + std::to_string(expectedValue2) + ", actual=" + std::to_string(actualValue2);
//    std::string errorMessage3 = "TestBitReader_Constructor error: byteVec value expected=" + std::to_string(expectedValue3) + ", actual=" + std::to_string(actualValue3);
//
//    AssertTrue(expectedValue1 == actualValue1, errorMessage1);
//    AssertTrue(expectedValue2 == actualValue2, errorMessage2);
//    AssertTrue(expectedValue3 == actualValue3, errorMessage3);
//}
//
//void TestBitReader_GetCurrentByteIndex()
//{
//
//}
//
//void TestBitReader_PeekBitsAsLittleEndian()
//{
//
//}
//
//void TestBitReader_GetNumRemainingBitsInCurrentByte()
//{
//
//}
//
//void TestBitReader_GetIsolatedBits()
//{
//
//}
//
//void TestBitReader_GetBitsAsLittleEndian()
//{
//
//}
//
//
//void AssertTrue(bool boolExpression, const std::string& errorMessage)
//{
//    if (!boolExpression)
//    {
//        std::cout << "\n\n" << "AssertTrue error: " << errorMessage << "\n\n";
//        exit(0);
//    }
//}


  
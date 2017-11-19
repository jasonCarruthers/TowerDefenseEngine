#include <iostream>
#include <string>
#include <vector>
#include "PrimitiveTypedefs.h"
#include "Assert.h"
#include "include/Utilities/Logger.h"
#include "BitReader.h"
#include "BitReaderTestRunner.h"



/*
* Global variables used in the BitReaderTestRunner class. Not visible to other files.
*/
byte byte1 = 0xF0;
byte byte2 = 0xAA;
byte byte3 = 0xCC;


/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class BitReaderTestRunner
* -------------------------------------------------------------------------------------------------------
*/
/*
* Initialize static variables
*/
bool BitReaderTestRunner::EXISTS = false;

/*
* Constructors
*/
BitReaderTestRunner::BitReaderTestRunner()
{
}

/*
* Accessors
*/
BitReaderTestRunner* BitReaderTestRunner::GetInstance()
{
    static BitReaderTestRunner* bitReaderTestRunner;
    if (!EXISTS)
    {
        EXISTS = true;
        bitReaderTestRunner = new BitReaderTestRunner();
    }
    return bitReaderTestRunner;
}

void BitReaderTestRunner::RunTests()
{
    std::string infoMessagePrefix = "BitReaderTestRunner::RunTests: ";
    Logger::GetInstancePtr()->Log(infoMessagePrefix + "Starting.", Logger::LogType_Info);

    BitReaderTestRunner* testRunner = BitReaderTestRunner::GetInstance();
    testRunner->TestConstructor();
    testRunner->TestCurrentBitIndexIsValid();
    testRunner->TestCurrentByteIndexIsValid();
    testRunner->TestGetCurrentByteIndex();
    testRunner->TestPeekBitsAsLittleEndian();
    testRunner->TestGetNumRemainingBitsInCurrentByte();
    testRunner->TestPeekIsolatedBitsInByte();
    testRunner->TestGetBitsAsLittleEndian();

    Logger::GetInstancePtr()->Log(infoMessagePrefix + "Finished.", Logger::LogType_Info);
}

void BitReaderTestRunner::TestConstructor()
{
    std::vector<byte> byteVec;
    byteVec.push_back(byte1);
    byteVec.push_back(byte2);
    byteVec.push_back(byte3);
    BitReader bitReader = BitReader(byteVec);

    std::string messagePrefix = "BitReaderTestRunner.TestConstructor: ";
    AssertTrue(0 == bitReader.currentBitIndex, messagePrefix + "0 != currentBitIndex");
    AssertTrue(0 == bitReader.currentByteIndex, messagePrefix + "0 != currentByteIndex");
    AssertTrue(3 == bitReader.byteVec.size(), messagePrefix + "3 != byteVec.size()");
    AssertTrue(byte1 == bitReader.byteVec[0], messagePrefix + "byte1 != byteVec[0]");
    AssertTrue(byte2 == bitReader.byteVec[1], messagePrefix + "byte2 != byteVec[1]");
    AssertTrue(byte3 == bitReader.byteVec[2], messagePrefix + "byte3 != byteVec[2]");
}

void BitReaderTestRunner::TestCurrentBitIndexIsValid()
{
    std::string messagePrefix = "BitReaderTestRunner.TestCurrentBitIndexIsValid: ";

    std::vector<byte> byteVec;
    BitReader bitReader = BitReader(byteVec);

    AssertTrue(0 == bitReader.currentBitIndex, messagePrefix + "0 != currentBitIndex");
    AssertTrue(bitReader.CurrentBitIndexIsValid(), messagePrefix + "CurrentBitIndexIsValid() returned false");

    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current bit index from 0 to -1.", Logger::LogType_Debug);
    bitReader.currentBitIndex = -1;
    AssertFalse(bitReader.CurrentBitIndexIsValid(), messagePrefix + "CurrentBitIndexIsValid() returned true");

    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current bit index from -1 to 8.", Logger::LogType_Debug);
    bitReader.currentBitIndex = 8;
    AssertFalse(bitReader.CurrentBitIndexIsValid(), messagePrefix + "CurrentBitIndexIsValid() returned true");
}

void BitReaderTestRunner::TestCurrentByteIndexIsValid()
{
    std::string messagePrefix = "BitReaderTestRunner.TestCurrentByteIndexIsValid: ";

    std::vector<byte> byteVec;
    BitReader bitReader = BitReader(byteVec);

    AssertTrue(0 == bitReader.currentByteIndex, messagePrefix + "0 != currentByteIndex");
    AssertFalse(bitReader.CurrentByteIndexIsValid(), messagePrefix + "CurrentByteIndexIsValid() returned true");

    Logger::GetInstancePtr()->Log(messagePrefix + "Inserting byte1 into the byteVec", Logger::LogType_Debug);
    bitReader.byteVec.push_back(byte1);
    AssertTrue(bitReader.CurrentByteIndexIsValid(), messagePrefix + "CurrentByteIndexIsValid() returned false");

    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current byte index from 0 to -1", Logger::LogType_Debug);
    bitReader.currentByteIndex = -1;
    AssertFalse(bitReader.CurrentByteIndexIsValid(), messagePrefix + "CurrentByteIndexIsValid() returned true");

    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current byte index from -1 to 1", Logger::LogType_Debug);
    bitReader.currentByteIndex = 1;
    AssertFalse(bitReader.CurrentByteIndexIsValid(), messagePrefix + "CurrentByteIndexIsValid() returned true");
}

void BitReaderTestRunner::TestGetCurrentByteIndex()
{
    std::vector<byte> byteVec;
    byteVec.push_back(byte1);
    byteVec.push_back(byte2);
    byteVec.push_back(byte3);
    BitReader bitReader = BitReader(byteVec);

    std::string messagePrefix = "BitReaderTestRunner.TestGetCurrentByteIndex: ";
    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current byte index from 0 to 2.", Logger::LogType_Debug);
    bitReader.currentByteIndex = 2;

    AssertTrue(2 == bitReader.GetCurrentByteIndex(), messagePrefix + "2 != GetCurrentByteIndex()");
}

void BitReaderTestRunner::TestPeekBitsAsLittleEndian()
{
    std::vector<byte> byteVec;
    byteVec.push_back(byte1);
    byteVec.push_back(byte2);
    byteVec.push_back(byte3);
    BitReader bitReader = BitReader(byteVec);
    
    std::string messagePrefix = "BitReaderTestRunner.TestPeekBitsAsLittleEndian: ";
    AssertTrue(byte1 == bitReader.PeekBitsAsLittleEndian(8), messagePrefix + "byte1 != PeekBitsAsLittleEndian(8)");

    bitReader.currentBitIndex = 4;
    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current bit index from position 0 to position 4.", Logger::LogType_Debug);
    AssertTrue(0x0F == bitReader.PeekBitsAsLittleEndian(4), messagePrefix + "0x0F != PeekBitsAsLittleEndian(4)");
}

void BitReaderTestRunner::TestGetNumRemainingBitsInCurrentByte()
{
    std::vector<byte> byteVec;
    byteVec.push_back(byte1);
    byteVec.push_back(byte2);
    byteVec.push_back(byte3);
    BitReader bitReader = BitReader(byteVec);

    std::string messagePrefix = "BitReaderTestRunner.TestGetNumRemainingBitsInCurrentByte: ";
    AssertTrue(8 == bitReader.GetNumRemainingBitsInCurrentByte(), messagePrefix + "8 != GetNumRemainingBitsInCurrentByte()");

    bitReader.currentBitIndex = 5;
    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current bit index from position 0 to position 5.", Logger::LogType_Debug);
    AssertTrue(3 == bitReader.GetNumRemainingBitsInCurrentByte(), messagePrefix + "3 != GetNumRemainingBitsInCurrentByte()");

    bitReader.currentBitIndex = 7;
    Logger::GetInstancePtr()->Log(messagePrefix + "Setting current bit index from position 5 to position 7.", Logger::LogType_Debug);
    AssertTrue(1 == bitReader.GetNumRemainingBitsInCurrentByte(), messagePrefix + "1 != GetNumRemainingBitsInCurrentByte()");
}

void BitReaderTestRunner::TestPeekIsolatedBitsInByte()
{
    std::vector<byte> byteVec;
    byteVec.push_back(byte1);
    byteVec.push_back(byte2);
    byteVec.push_back(byte3);
    BitReader bitReader = BitReader(byteVec);
    
    std::string messagePrefix = "BitReaderTestRunner.TestGetIsolatedBits: ";
    AssertTrue(0x0F == bitReader.PeekIsolatedBitsInByte(0, 4, 7), messagePrefix + "0x0F != GetIsolatedBits(byte1, 4, 7)");
}

void BitReaderTestRunner::TestGetBitsAsLittleEndian()
{
    std::vector<byte> byteVec;
    byteVec.push_back(byte1);
    byteVec.push_back(byte2);
    byteVec.push_back(byte3);
    BitReader bitReader = BitReader(byteVec);

    std::string messagePrefix = "BitReaderTestRunner.TestGetBitsAsLittleEndian: ";
    Logger::GetInstancePtr()->Log(messagePrefix + "Setting bit index from position 0 to position 3", Logger::LogType_Debug);
    bitReader.currentBitIndex = 3;

    int retVal = bitReader.GetBitsAsLittleEndian(19);
    AssertTrue(0x01955E == retVal, messagePrefix + "0x01955E != GetBitsAsLittleEndian(19)");
}

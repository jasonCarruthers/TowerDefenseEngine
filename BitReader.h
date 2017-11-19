#ifndef HFILE_BIT_READER
#define HFILE_BIT_READER


class BitReader
{
    /*
    * Friends
    */
friend class BitReaderTestRunner;

    /*
    * Constructors
    */
public: BitReader(const std::vector<byte>& byteVec);

    /*
    * Accessors
    */
private: bool CurrentBitIndexIsValid() const;
private: bool CurrentByteIndexIsValid() const;
public: int GetCurrentBitIndex() const;
public: int GetCurrentByteIndex() const;
public: long PeekBitsAsLittleEndian(const int numBitsToPeek) const;
private: int GetNumRemainingBitsInCurrentByte() const;
private: int PeekIsolatedBitsInByte(int byteIndex, int startBitPosition, int endBitPosition) const;
//private: int PeekIsolatedBitsInCurrentByte(); //Peeks the remaining bits in the current byte.
//private: int PeekIsolatedBitsInCurrentByte(int endBitPositionInclusive); //Peeks bits up to and including the bit at position endBitPositionInclusive.

    /*
    * Mutators
    */
public: long GetBitsAsLittleEndian(int numBitsToGet);

        /*
        * Variables
        */
private:
    std::vector<byte> byteVec;
    int currentByteIndex;
    int currentBitIndex; //Always in Little Endian, so LSB is position 0 and MSB is position 7.
};



/*
* Global function prototypes
*/
//extern void TestBitReader_Constructor();
//extern void TestBitReader_GetCurrentByteIndex();
//extern void TestBitReader_PeekBitsAsLittleEndian();
//extern void TestBitReader_GetNumRemainingBitsInCurrentByte();
//extern void TestBitReader_GetIsolatedBits();
//extern void TestBitReader_GetBitsAsLittleEndian();
//
//extern void AssertTrue(bool boolExpression, const std::string& errorMessage);


#endif /*HFILE_BIT_READER*/
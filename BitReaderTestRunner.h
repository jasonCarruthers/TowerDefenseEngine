#ifndef BIT_READER_TEST_RUNNER_HFILE
#define BIT_READER_TEST_RUNNER_HFILE




class BitReaderTestRunner
{
/*
* Constructors
*/
private: BitReaderTestRunner();

/*
* Accessors
*/
private: static BitReaderTestRunner* GetInstance();
public: static void RunTests();
public: void TestConstructor();
public: void TestCurrentBitIndexIsValid();
public: void TestCurrentByteIndexIsValid();
public: void TestGetCurrentByteIndex();
public: void TestPeekBitsAsLittleEndian();
public: void TestGetNumRemainingBitsInCurrentByte();
public: void TestPeekIsolatedBitsInByte();
public: void TestGetBitsAsLittleEndian();

/*
* Variables
*/
private: static bool EXISTS;
};

#endif /*BIT_READER_TEST_RUNNER_HFILE*/
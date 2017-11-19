//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "./include/2DGraphics/Image.h"
//#include "ImageTest.h"
//
//
//const std::string FILE_PATH = "image/TestGIF.gif";
//
//
//std::ifstream OpenTestFile()
//{
//    std::ifstream file;
//    file.open(FILE_PATH, std::ifstream::in);
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File did not open successfuly." << "\n\n";
//    }
//    return file;
//}
//
//void RunUnitTests()
//{
//    TestReadingHeader();
//    TestReadingLogicalScreenDescriptor();
//    TestReadingGlobalColorTable();
//    TestReadingImageDescriptor();
//    TestReadingTableBasedImageData();
//    TestReadingTrailer();
//}
//
//void TestReadingHeader()
//{
//    std::string fileContents = "474946383961";
//    WriteTestGIFToFile(fileContents);
//
//    std::ifstream file = OpenTestFile();
//
//    GIF::Header header;
//    header.Read(file);
//
//    bool passed = header.signature == "GIF" && header.version == "89a";
//    std::string passedText = passed ? "PASSED" : "FAILED";
//    std::cout << "[UNIT TEST] TestReadingHeader " << passedText << "." << "\n";
//
//    file.close();
//}
//
//void TestReadingLogicalScreenDescriptor()
//{
//    std::string logicalScreenWidth = "0200"; //Little endian representation for 2.
//    std::string logicalScreenHeight = "0100"; //Little endian representation for 1.
//    std::string packedBits = "A0";
//    std::string backgroundColorIndex = "00";
//    std::string pixelAspectRatio = "00";
//    std::string fileContents = logicalScreenWidth + logicalScreenHeight + packedBits + backgroundColorIndex + pixelAspectRatio;
//    WriteTestGIFToFile(fileContents);
//
//    std::ifstream file = OpenTestFile();
//
//    GIF::LogicalScreenDescriptor lsd;
//    lsd.Read(file);
//
//    //std::cout << std::hex << lsd.logicalScreenWidth;
//    //std::cout << "\n" << std::hex << lsd.logicalScreenHeight;
//    //std::cout << "\n" << std::hex << lsd.globalColorTableFlag;
//    //std::cout << "\n" << std::hex << lsd.colorResolution;
//    //std::cout << "\n" << std::hex << lsd.sortFlag;
//    //std::cout << "\n" << std::hex << lsd.sizeOfGlobalColorTable;
//    //std::cout << "\n" << std::hex << (int)lsd.backgroundColorIndex;
//    //std::cout << "\n" << std::hex << (int)lsd.pixelAspectRatio;
//    //std::cout << "\n";
//
//    bool passed = 2 == lsd.logicalScreenWidth &&
//                  1 == lsd.logicalScreenHeight &&
//                  1 == lsd.globalColorTableFlag &&
//                  2 == lsd.colorResolution &&
//                  0 == lsd.sortFlag &&
//                  0 == lsd.sizeOfGlobalColorTable &&
//                  0 == lsd.backgroundColorIndex &&
//                  0 == lsd.pixelAspectRatio;     
//    std::string passedText = passed ? "PASSED" : "FAILED";
//    std::cout << "[UNIT TEST] TestReadingLogicalScreenDescriptor " << passedText << "." << "\n";
//
//    file.close();
//}
//
//void TestReadingGlobalColorTable()
//{
//    std::string firstColor = "FF0000";
//    std::string secondColor = "00FF00";
//    std::string fileContents = firstColor + secondColor;
//    WriteTestGIFToFile(fileContents);
//
//    std::ifstream file = OpenTestFile();
//
//    GIF::GlobalColorTable gct;
//    gct.Read(file, 0);
//
//    bool passed = Color3(1, 0, 0) == gct.globalColorTableVec[0] &&
//                  Color3(0, 1, 0) == gct.globalColorTableVec[1];
//    std::string passedText = passed ? "PASSED" : "FAILED";
//    std::cout << "[UNIT TEST] TestReadingGlobalColorTable " << passedText << "." << "\n";
//
//    file.close();
//}
//
//void TestReadingImageDescriptor()
//{
//    std::string imageSeparator = "2C";
//    std::string imageLeftPosition = "0000"; //Little endian representation for 0.
//    std::string imageTopPosition = "0000"; //Little endian representation for 0.
//    std::string imageWidth = "0200"; //Little endian representation for 2.
//    std::string imageHeight = "0100"; //Little endian representation for 1.
//    std::string packedFields = "00";
//    std::string fileContents = imageSeparator + imageLeftPosition + imageTopPosition + imageWidth + imageHeight + packedFields;
//    WriteTestGIFToFile(fileContents);
//
//    std::ifstream file = OpenTestFile();
//
//    GIF::ImageDescriptor id;
//    id.Read(file);
//
//    bool passed = 44 == id.imageSeparator &&
//                  0 == id.imageLeftPosition &&
//                  0 == id.imageTopPosition &&
//                  2 == id.imageWidth &&
//                  1 == id.imageHeight &&
//                  0 == id.localColorTableFlag &&
//                  0 == id.interlaceFlag &&
//                  0 == id.sortFlag &&
//                  0 == id.reserved &&
//                  0 == id.sizeOfLocalColorTable;
//    std::string passedText = passed ? "PASSED" : "FAILED";
//    std::cout << "[UNIT TEST] TestReadingImageDescriptor " << passedText << "." << "\n";
//
//    file.close();
//}
//
//void TestReadingTableBasedImageData()
//{
//    std::string lzwMinimumCodeSize = "01";
//    std::string blockSize = "01";
//    std::string dataBytes = "02";
//    std::string blockTerminator = "00";
//    std::string clearCode = "02";
//    std::string endOfInformationCode = "03";
//    std::string imageData = blockSize + dataBytes + blockTerminator + endOfInformationCode;
//    std::string fileContents = lzwMinimumCodeSize + imageData;
//    WriteTestGIFToFile(fileContents);
//
//    std::ifstream file = OpenTestFile();
//
//    GIF::TableBasedImageData tbid;
//    tbid.Read(file, 2, 1, GIF::DEFAULT_COLOR_TABLE);
//
//    bool passed = 1 == tbid.lzwMinimumCodeSize == 1 &&
//                  0 == tbid.imageData[0] &&
//                  1 == tbid.imageData[1];
//    std::string passedText = passed ? "PASSED" : "FAILED";
//    std::cout << "[UNIT TEST] TestReadingTableBasedImageData " << passedText << "." << "\n";
//
//    file.close();
//}
//
//void TestReadingTrailer()
//{
//    std::string fileContents = "3B";
//    WriteTestGIFToFile(fileContents);
//
//    std::ifstream file = OpenTestFile();
//
//    GIF::Trailer trailer;
//    trailer.Read(file);
//
//    bool passed = trailer.gifTrailer == (char)59;
//    std::string passedText = passed ? "PASSED" : "FAILED";
//    std::cout << "[UNIT TEST] TestReadingTrailer " << passedText << "." << "\n";
//
//    file.close();
//}
//
//
///*
//* The follow represents a 2x1 (width x height) GIF where the first pixel is pure red and the second is pure blue.
//*
//* Grammar:
//* <GIF Data Stream>           ::= Header <Logical Screen> <Data>* Trailer
//* <Logical Screen>            ::= Logical Screen Descriptor [Global Color Table]
//* <Data>                      ::= <Graphic Block> | <Special-Purpose Block>
//* <Graphic Block>             ::= [Graphic Control Extension] <Graphic-Rendering Block>
//* <Graphic-Rendering Block>   :: = <Table-Based Image> | Plain Text Extension
//* <Table-Based Image>         ::= Image Descriptor [Local Color Table] Image Data
//* <Special-Purpose Block>     ::= Application Extension | Comment Extension
//*/
//void CreateTestGIF_2x1White()
//{
//    std::string header = "474946383961";
//    std::string logicalScreenWidth = "0200"; //Little endian representation for 2.
//    std::string logicalScreenHeight = "0100"; //Little endian representation for 1.
//    std::string packedBits = "A0";
//    std::string backgroundColorIndex = "00";
//    std::string pixelAspectRatio = "02";
//    std::string logicalScreenDescriptor = logicalScreenWidth + logicalScreenHeight + packedBits + backgroundColorIndex + pixelAspectRatio;
//    std::string firstColor = "FF0000";
//    std::string secondColor = "00FF00";
//    std::string globalColorTable = firstColor + secondColor;
//    //std::string imageDescriptor = "2C000000000000000000";
//    //std::string imageData = "0103";
//    //std::string imageData = "010101";
//    std::string trailer = "3B";
//    std::string fileContents = header + logicalScreenDescriptor + globalColorTable + /*imageDescriptor + imageData +*/ trailer;
//    //std::string fileContents = "4749463839610201F2000000FFFFFF2C0000020100053B";
//
//    WriteTestGIFToFile(fileContents);
//}
//
///*
//* Takes a string of hex values, representing a GIF, and writes them to a new GIF file.
//*/
//void WriteTestGIFToFile(const std::string& fileContents)
//{
//    /*
//    * Create the file.
//    */
//    std::ifstream file;
//    std::ofstream datafile(FILE_PATH, std::ios_base::binary | std::ios_base::out);
//
//    char buf[3];
//    buf[2] = 0;
//
//    std::stringstream input(fileContents);
//    input.flags(std::ios_base::hex);
//    while (input)
//    {
//        input >> buf[0] >> buf[1];
//        long val = strtol(buf, nullptr, 16);
//        datafile << static_cast<unsigned char>(val & 0xff);
//    }
//
//    /*
//    * Close the file.
//    */
//    file.close();
//}
//
////void WriteTestGIFToFile()
////{
////    std::string header = "474946383961";
////    std::string logicalScreenDescriptor = "00020001F00000";
////    std::string globalColorTable = "000000FFFFFF";
////    std::string imageDescriptor = "2C000000000000000000";
////    std::string imageData = "0103";
////    //std::string imageData = "010101";
////    std::string trailer = "3B";
////    std::string fileContents = header + logicalScreenDescriptor + globalColorTable + imageDescriptor + imageData + trailer;
////    //std::string fileContents = "4749463839610201F2000000FFFFFF2C0000020100053B";
////
////    /*
////    * Create the file.
////    */
////    std::string filePath = "image/TestGIF.gif";
////    std::ifstream file;
////    std::ofstream datafile(filePath, std::ios_base::binary | std::ios_base::out);
////
////    char buf[3];
////    buf[2] = 0;
////
////    std::stringstream input(fileContents);
////    input.flags(std::ios_base::hex);
////    while (input)
////    {
////        input >> buf[0] >> buf[1];
////        long val = strtol(buf, nullptr, 16);
////        datafile << static_cast<unsigned char>(val & 0xff);
////    }
////
////    /*
////    * Close the file.
////    */
////    file.close();
////}
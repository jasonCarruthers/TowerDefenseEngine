#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "../../PrimitiveTypedefs.h"
#include "../../include/2DGraphics/Image.h"
#include "../../include/2DGraphics/Color.h"
#include "../../include/Window/Pixel.h"
#include "../../BitReader.h"



/*
* Global functions
*/
//TODO: Test.
char BaseTenDigitToASCII(int num)
{
    num -= 48;

    if (num < 0 || num > 9)
    {
        std::cout << "\n\n" << "Error: num is not between 0 and 9 (in function BaseTenDigitToASCII)." << "\n\n";
    }

    return (char)num;
}

//TODO: Test.
std::string IntToStringBinary(int num)
{
    std::string stringBinary = "";
    while (num > 0)
    {
        stringBinary.insert(stringBinary.begin(), BaseTenDigitToASCII(num % 2));
        num /= 2;
    }
    return stringBinary;
}

//TODO: Test
int StringBinaryToInt(const std::string& stringBinary)
{
    int num = 0;
    int multiplier = 1;
    for (unsigned int index = 0; index < stringBinary.size(); index++)
    {
        num += multiplier * stringBinary[stringBinary.size() - 1 - index];
        multiplier *= 2;
    }
    return num;
}





/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Image
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructors
*/
Image::Image()
{
    imageArr = nullptr;
}

/*
* Accessors
*/
//DEPRECATED
//byte Image::PeekNextByte(std::ifstream& file, bool isSigned)
//{
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File not open. Could not peek next byte." << "\n\n";
//        return NULL;
//    }
//
//    char peekByte = file.peek();
//    if (isSigned && EOF == peekByte)
//    {
//        std::cout << "\n\n" << "Error: EOF reached! Could not peek next byte." << "\n\n";
//        std::cout << "Is peekByte == EOF?\t" << (int)peekByte << "\t" << (int)EOF << "\n";
//        return EOF;
//    }
//
//    //For testing
//    byte peekTestByte = file.peek();
//    if ((byte)peekByte != (byte)peekTestByte)
//    {
//        std::cout << "\n\n" << "Error: Peeking mutated file." << "\n\n";
//    }
//
//    return peekByte;
//}

//DEPRECATED
//Peeks the second to next byte.
//byte Image::PeekSecondToNextByte(std::ifstream& file, bool isSigned)
//{
//    byte nextByte = GetNextByte(file, isSigned);
//    byte secondToNextByte = PeekNextByte(file, isSigned);
//    file.putback(nextByte);
//
//    int peekTestByte = file.peek();
//    if (nextByte != peekTestByte)
//    {
//        std::cout << "\n\n" << "Error: Peeking mutated file." << "\n\n";
//    }
//
//    return secondToNextByte;
//}

//DEPRECATED
//byte Image::GetNextByte(std::ifstream& file, char& nextChar, bool isSigned)
//{
//    nextChar = NULL;
//
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File not open. Could not get next 8 bits." << "\n\n";
//        return;
//    }
//
//    file.get(nextChar);
//    if (isSigned && EOF == nextChar)
//        std::cout << "\n\n" << "Error: EOF reached! Could not get next 8 bits." << "\n\n";
//}

//DEPRECATED
//TODO: Test
//byte Image::GetNextByte(std::ifstream& file, bool isSigned)
//{
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File not open. Could not get next byte." << "\n\n";
//        return NULL;
//    }
//
//    byte nextByte = file.get();
//    if (isSigned && EOF == nextByte)
//    {
//        std::cout << "\n\n" << "Error: EOF reached! Could not get next byte." << "\n\n";
//        return EOF;
//    }
//
//    return nextByte;
//}

byte Image::GetNextByte(std::ifstream& file)
{
    if (!file.is_open())
    {
        std::cout << "\n\n" << "Error: File not open. Could not get next byte." << "\n\n";
        return NULL;
    }

    byte nextByte = file.get();
    return nextByte;
}

//DEPRECATED
//twoBytes Image::GetNextTwoBytes(std::ifstream& file, unsigned int& nextUnsignedInt, bool isSigned)
//{
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File not open. Could not get next 16 bits." << "\n\n";
//        return;
//    }
//    
//    unsigned int nextByte = GetNextByte(file, isSigned);
//    GetNext8Bits(file, nextChar, isSigned);
//    nextUnsignedInt = nextUnsignedInt << (int)nextChar;
//}

//DEPRECATED
//TODO: Test
//twoBytes Image::GetNextTwoBytes(std::ifstream& file, bool isSigned)
//{
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File not open. Could not get next two bytes." << "\n\n";
//        return NULL;
//    }
//
//    byte nextByte = GetNextByte(file, isSigned);
//    byte secondToNextByte = GetNextByte(file, isSigned);
//    twoBytes nextTwoBytes = nextByte;
//    nextTwoBytes = nextTwoBytes << 8;
//    nextTwoBytes = nextTwoBytes | secondToNextByte;
//    return nextTwoBytes;
//}

//DEPRECATED
//TODO: Test
//twoBytes Image::GetNextTwoBytesInLittleEndian(std::ifstream& file, bool isSigned)
//{
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File not open. Could not get next two bytes in little endian." << "\n\n";
//        return 0;
//    }
//
//    twoBytes nextTwoBytesInLittleEndian = GetNextByte(file, isSigned);
//    byte nextByte = GetNextByte(file, isSigned);
//    nextTwoBytesInLittleEndian = nextTwoBytesInLittleEndian | (nextByte << 8);
//    return nextTwoBytesInLittleEndian;
//}

twoBytes Image::GetTwoBytesAsLittleEndian(byte firstByte, byte secondByte)
{
    return (secondByte << 8) | firstByte;
}

twoBytes Image::GetTwoBytesAsBigEndian(byte firstByte, byte secondByte)
{
    return (firstByte << 8) | secondByte;
}




/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class GIF
* -------------------------------------------------------------------------------------------------------
*/
/*
* Static constants
*/
const std::vector<Color3> GIF::DEFAULT_COLOR_TABLE{ Color3(0, 0, 0),
                                                    Color3(1, 1, 1),
                                                    Color3(1, 0, 0),
                                                    Color3(0, 1, 0),
                                                    Color3(0, 0, 1)};

const byte GIF::EXTENSION_INTRODUCER = 33;               //0x21

const byte GIF::IMAGE_DESCRIPTOR_LABEL = 44;             //0x2C
const byte GIF::GRAPHIC_CONTROL_EXTENSION_LABEL = 249;   //0xF9
const byte GIF::COMMENT_EXTENSION_LABEL = 254;           //0xFE
const byte GIF::PLAIN_TEXT_EXTENSION_LABEL = 1;          //0x01
const byte GIF::APPLICATION_EXTENSION_LABEL = 255;       //0xFF
const byte GIF::TRAILER_LABEL = 59;                      //0x3B

const std::string GIF::VERSION_87a = "87a";
const std::string GIF::VERSION_89a = "89a";

const std::string GIF::LOGICAL_SCREEN_DESCRIPTOR_REQUIRED_VERSION = VERSION_87a;
const std::string GIF::GLOBAL_COLOR_TABLE_REQUIRED_VERSION = VERSION_87a;
const std::string GIF::IMAGE_DESCRIPTOR_REQUIRED_VERSION = VERSION_87a;
const std::string GIF::LOCAL_COLOR_TABLE_REQUIRED_VERSION = VERSION_87a;
const std::string GIF::GRAPHIC_CONTROL_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string GIF::COMMENT_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string GIF::PLAIN_TEXT_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string GIF::APPLICATION_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string GIF::TRAILER_REQUIRED_VERSION = VERSION_87a;

/*
* Constructors
*/
GIF::GIF(const std::string& filePath)
{
    if (!filePath.empty())
        Load(filePath);
    else
        std::cout << "Error: No file path given." << "\n";

}

/*
* Accessors
*/
int GIF::GetWidth() const
{
    return (0 == imageDescriptor.imageWidth) ?
        logicalScreenDescriptor.logicalScreenWidth : imageDescriptor.imageWidth;
}

int GIF::GetHeight() const
{
    return (0 == imageDescriptor.imageHeight) ?
        logicalScreenDescriptor.logicalScreenHeight : imageDescriptor.imageHeight;
}

std::vector<byte> GIF::ReadBytesFromGIFFile(const std::string& filePath)
{
    std::vector<byte> byteVec;

    /*
    * Open the file at the end, so that tellg() returns the size of the file. Then reserve that many bytes in byteVec.
    */
    std::ifstream file(filePath, std::ifstream::ate | std::ifstream::binary);
    if (!file.is_open())
    {
        std::cout << "\n\n" << "Error: File did not open successfuly." << "\n\n";
        return byteVec;
    }
    int numBytes = (int) file.tellg();
    byteVec.reserve(numBytes);
    file.close();

    /*
    * Open the file, this time at the beginning.
    */
    file.open(filePath, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "\n\n" << "Error: File did not open successfuly." << "\n\n";
        return byteVec;
    }

    //byte lastByteRead = NULL;
    //while (lastByteRead != GIF::TRAILER_LABEL)
    /*
    * NOTE: If this for loop works, which is dependent on tellg() returning the correct value for file size,
    * then you can get rid of the bool parameter in the GetNextByte method.
    */
    for (int byteIndex = 0; byteIndex < numBytes; byteIndex++)
    {
        byteVec.push_back(GetNextByte(file));
        //lastByteRead = byteVec[byteIndex];
    }

    file.close();
    return byteVec;
}

std::string GIF::GetBlockNameRequiredVersion(GIF::BlockName blockName) const
{
    switch (blockName)
    {
    case BlockName_Header:                  std::cout << "Error: Header does not have a required version." << "\n"; return "";
    case BlockName_LogicalScreenDescriptor: return LOGICAL_SCREEN_DESCRIPTOR_REQUIRED_VERSION;
    case BlockName_GlobalColorTable:        return GLOBAL_COLOR_TABLE_REQUIRED_VERSION;
    case BlockName_ImageDescriptor:         return IMAGE_DESCRIPTOR_REQUIRED_VERSION;
    case BlockName_LocalColorTable:         return LOCAL_COLOR_TABLE_REQUIRED_VERSION;
    case BlockName_GraphicControlExtension: return GRAPHIC_CONTROL_EXTENSION_REQUIRED_VERSION;
    case BlockName_CommentExtension:        return COMMENT_EXTENSION_REQUIRED_VERSION;
    case BlockName_PlainTextExtension:      return PLAIN_TEXT_EXTENSION_REQUIRED_VERSION;
    case BlockName_ApplicationExtension:    return APPLICATION_EXTENSION_REQUIRED_VERSION;
    case BlockName_Trailer:                 return TRAILER_REQUIRED_VERSION;
    default:                                std::cout << "Error: Invalid BlockName." << "\n"; return "";
    }
}

bool GIF::IsVersionCompatible(GIF::BlockName blockName, std::string version) const
{
    return GIF::VERSION_87a == version ? GetBlockNameRequiredVersion(blockName) == version : true;
}

GIF::BlockName GIF::GetBlockNameFromExtensionName(ExtensionName extensionName)
{
    switch (extensionName)
    {
        case ExtensionName_GraphicControlExtension: return BlockName_GraphicControlExtension;
        case ExtensionName_CommentExtension: return BlockName_CommentExtension;
        case ExtensionName_PlainTextExtension: return BlockName_PlainTextExtension;
        case ExtensionName_ApplicationExtension: return BlockName_ApplicationExtension;
        default: std::cout << "\n\n" << "Error: No matching block name for the given extension name." << "\n\n"; return BlockName_Header;
    }
}

bool GIF::IsSpecificExtension(ExtensionName extensionName, int byteVecIndex)
{
    int nextByte = byteVec[byteVecIndex];
    int secondToNextByte = byteVec[byteVecIndex + 1];
    BlockName blockName = GetBlockNameFromExtensionName(extensionName);
    return IsExtensionIntroducer(nextByte) && IsMatchingLabel(blockName, secondToNextByte);
}

bool GIF::IsExtensionIntroducer(byte num) const
{
    return EXTENSION_INTRODUCER == num;
}

bool GIF::IsMatchingLabel(GIF::BlockName blockName, int label) const
{
    switch (blockName)
    {
    case BlockName_Header:                      std::cout << "Error: Header has no label." << "\n"; return false;
    case BlockName_LogicalScreenDescriptor:     std::cout << "Error: Logical screen descriptor has no label." << "\n"; return false;
    case BlockName_GlobalColorTable:            std::cout << "Error: Global color table has no label." << "\n"; return false;
    case BlockName_ImageDescriptor:             return IMAGE_DESCRIPTOR_LABEL == label;
    case BlockName_LocalColorTable:             std::cout << "Error: Local color table has no label." << "\n"; return false;
    //case BlockName_TableBasedImageData:         std::cout << "Error: Table based image data has no label." << "\n"; return false;
    case BlockName_GraphicControlExtension:     return GRAPHIC_CONTROL_EXTENSION_LABEL == label;
    case BlockName_CommentExtension:            return COMMENT_EXTENSION_LABEL == label;
    case BlockName_PlainTextExtension:          return PLAIN_TEXT_EXTENSION_LABEL == label;
    case BlockName_ApplicationExtension:        return APPLICATION_EXTENSION_LABEL == label;
    case BlockName_Trailer:                     return TRAILER_LABEL == label;
    default: std::cout << "Error: Invalid BlockName." << "\n"; return false;
    }
}

//Assumes an extension introducer was already found before calling this function.
int GIF::ReadExtension(int byteVecIndex)
{
    //The caller only peeked the extension introducer, so that byte still needs to be read.
    byteVecIndex++;

    byte label = byteVec[byteVecIndex];
    byteVecIndex++;
    switch (label)
    {
    case GRAPHIC_CONTROL_EXTENSION_LABEL:   graphicControlExtension.Read(byteVec, byteVecIndex); break;
    case COMMENT_EXTENSION_LABEL:           commentExtension.Read(byteVec, byteVecIndex);        break;
    case PLAIN_TEXT_EXTENSION_LABEL:        plainTextExtension.Read(byteVec, byteVecIndex);      break;
    case APPLICATION_EXTENSION_LABEL:       applicationExtension.Read(byteVec, byteVecIndex);    break;
    default:                                std::cout << "\n\n" << "Error: Found extension introducer, but no extension label." << "\n\n"; break;
    }
    return byteVecIndex;
}

void GIF::Draw() const
{
    //For now, just draw the first Frame.
    for (unsigned int y = 0; y < tableBasedImageData.imageData[0].height; y++)
    {
        for (unsigned int x = 0; x < tableBasedImageData.imageData[0].width; x++)
        {
            int componentColorIndex = y * GetWidth() + x;
            //Color3 pixelColor = Color3(imageArr[componentColorIndex],
            //    imageArr[componentColorIndex + 1],
            //    imageArr[componentColorIndex + 2]);
            Color3 pixelColor = tableBasedImageData.imageData[0].pixelColorVec[componentColorIndex];
            SetPixel(x, GetHeight() - 1 - y, pixelColor);
        }
    }
    //RefreshScreen();
}

void GIF::DisplayVariables() const
{
    /*
    * Output Header
    */
    std::cout << "Header.Signature: \t\t\t\t\t" << header.signature << "\n";
    std::cout << "Header.Version:   \t\t\t\t\t" << header.version << "\n";
    std::cout << "\n";

    /*
    * Output Logical Screen Descriptor
    */
    std::cout << "LogicalScreenDescriptor.LogicalScreenWidth:\t\t" << (unsigned int)logicalScreenDescriptor.logicalScreenWidth << "\n";
    std::cout << "LogicalScreenDescriptor.LogicalScreenHeight:\t\t" << (unsigned int)logicalScreenDescriptor.logicalScreenHeight << "\n";
    std::cout << "LogicalScreenDescriptor.GlobalColorTableFlag:\t\t" << (unsigned int)logicalScreenDescriptor.globalColorTableFlag << "\n";
    std::cout << "LogicalScreenDescriptor.ColorResolution:\t\t" << (unsigned int)logicalScreenDescriptor.colorResolution << "\n";
    std::cout << "LogicalScreenDescriptor.SortFlag:\t\t\t" << (unsigned int)logicalScreenDescriptor.sortFlag << "\n";
    std::cout << "LogicalScreenDescriptor.SizeOfGlobalColorTable:\t\t" << (unsigned int)logicalScreenDescriptor.sizeOfGlobalColorTable << "\n";
    std::cout << "LogicalScreenDescriptor.BackgroundColorIndex:\t\t" << (unsigned int)logicalScreenDescriptor.backgroundColorIndex << "\n";
    std::cout << "LogicalScreenDescriptor.PixelAspectRatio:\t\t" << (unsigned int)logicalScreenDescriptor.pixelAspectRatio << "\n";
    std::cout << "\n";

    /*
    * Output Global Color Table
    */
    std::cout << "GlobalColorTable.NumRGBColorsInTable:\t\t\t" << (unsigned int)globalColorTable.globalColorTableVec.size() << "\n";
    std::cout << "\n";

    /*
    * Output Image Descriptor
    */
    std::cout << "ImageDescriptor.ImageSeparator:\t\t\t\t" << (unsigned int)imageDescriptor.imageSeparator << "\n";
    std::cout << "ImageDescriptor.ImageLeftPosition:\t\t\t" << (unsigned int)imageDescriptor.imageLeftPosition << "\n";
    std::cout << "ImageDescriptor.ImageTopPosition:\t\t\t" << (unsigned int)imageDescriptor.imageTopPosition << "\n";
    std::cout << "ImageDescriptor.ImageWidth:\t\t\t\t" << (unsigned int)imageDescriptor.imageWidth << "\n";
    std::cout << "ImageDescriptor.ImageHeight:\t\t\t\t" << (unsigned int)imageDescriptor.imageHeight << "\n";
    std::cout << "ImageDescriptor.LocalColorTableFlag:\t\t\t" << (unsigned int)imageDescriptor.localColorTableFlag << "\n";
    std::cout << "ImageDescriptor.InterlaceFlag:\t\t\t\t" << (unsigned int)imageDescriptor.interlaceFlag << "\n";
    std::cout << "ImageDescriptor.SortFlag:\t\t\t\t" << (unsigned int)imageDescriptor.sortFlag << "\n";
    std::cout << "ImageDescriptor.Reserved:\t\t\t\t" << (unsigned int)imageDescriptor.reserved << "\n";
    std::cout << "ImageDescriptor.SizeOfLocalColorTable:\t\t\t" << (unsigned int)imageDescriptor.sizeOfLocalColorTable << "\n";
    std::cout << "\n";

    /*
    * Output Local Color Table
    */
    std::cout << "LocalColorTable.NumRGBColorsInTable:\t\t\t" << (unsigned int)localColorTable.localColorTableVec.size() << "\n";
    std::cout << "\n";

    /*
    * Output Table Based Image Data
    */
    std::cout << "TableBasedImageData.LZWMinimumCodeSize:\t\t\t" << (unsigned int)tableBasedImageData.lzwMinimumCodeSize << "\n";
    //for (unsigned int imageDataIndex = 0; imageDataIndex < tableBasedImageData.imageData.size(); imageDataIndex++)
    //{
    //    int colorTableIndex = tableBasedImageData.imageData[imageDataIndex];
    //    Color3 correspondingColor = 1 == logicalScreenDescriptor.globalColorTableFlag ?
    //                                globalColorTable.globalColorTableVec[colorTableIndex] :
    //                                localColorTable.localColorTableVec[colorTableIndex];
    //    std::cout << "TableBasedImageData.ImageData[" << imageDataIndex << "]:\t\t\t"
    //              << colorTableIndex << "\tCorresponding color:\t\t"
    //              << correspondingColor.GetRed() << correspondingColor.GetGreen() << correspondingColor.GetBlue() << "\n";
    //}
    std::cout << "\n";

    /*
    * Output Graphic Control Extension
    */
    std::cout << "GraphicControlExtension.ExtensionIntroducer:\t\t" << (unsigned int)graphicControlExtension.extensionIntroducer << "\n";
    std::cout << "GraphicControlExtension.GraphicControlLabel:\t\t" << (unsigned int)graphicControlExtension.graphicControlLabel << "\n";
    std::cout << "GraphicControlExtension.BlockSize:\t\t\t" << (unsigned int)graphicControlExtension.blockSize << "\n";
    std::cout << "GraphicControlExtension.Reserved:\t\t\t" << (unsigned int)graphicControlExtension.reserved << "\n";
    std::cout << "GraphicControlExtension.DisposalMethod:\t\t\t" << (unsigned int)graphicControlExtension.disposalMethod << "\n";
    std::cout << "GraphicControlExtension.UserInputFlag:\t\t\t" << (unsigned int)graphicControlExtension.userInputFlag << "\n";
    std::cout << "GraphicControlExtension.TransparentColorFlag:\t\t" << (unsigned int)graphicControlExtension.transparentColorFlag << "\n";
    std::cout << "GraphicControlExtension.DelayTime:\t\t\t" << (unsigned int)graphicControlExtension.delayTime << "\n";
    std::cout << "GraphicControlExtension.TransparentColorIndex:\t\t" << (unsigned int)graphicControlExtension.transparentColorIndex << "\n";
    std::cout << "GraphicControlExtension.BlockTerminator:\t\t" << (unsigned int)graphicControlExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Comment Extension
    */
    std::cout << "CommentExtension.ExtensionIntroducer:\t\t\t" << (unsigned int)commentExtension.extensionIntroducer << "\n";
    std::cout << "CommentExtension.CommentData:\t\t\t" << commentExtension.commentData << "\n";
    std::cout << "CommentExtension.BlockTerminator:\t\t\t" << (unsigned int)commentExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Plain Text Extension.
    */
    std::cout << "PlainTextExtension.ExtensionIntroducer:\t\t\t" << (unsigned int)plainTextExtension.extensionIntroducer << "\n";
    std::cout << "PlainTextExtension.PlainTextLabel:\t\t\t" << (unsigned int)plainTextExtension.plainTextLabel << "\n";
    std::cout << "PlainTextExtension.BlockSize:\t\t\t\t" << (unsigned int)plainTextExtension.blockSize << "\n";
    std::cout << "PlainTextExtension.TextGridLeftPosition:\t\t" << (unsigned int)plainTextExtension.textGridLeftPosition << "\n";
    std::cout << "PlainTextExtension.TextGridTopPosition:\t\t\t" << (unsigned int)plainTextExtension.textGridTopPosition << "\n";
    std::cout << "PlainTextExtension.TextGridWidth:\t\t\t" << (unsigned int)plainTextExtension.textGridWidth << "\n";
    std::cout << "PlainTextExtension.TextGridHeight:\t\t\t" << (unsigned int)plainTextExtension.textGridHeight << "\n";
    std::cout << "PlainTextExtension.CharacterCellWidth:\t\t\t" << (unsigned int)plainTextExtension.characterCellWidth << "\n";
    std::cout << "PlainTextExtension.CharacterCellHeight:\t\t\t" << (unsigned int)plainTextExtension.characterCellHeight << "\n";
    std::cout << "PlainTextExtension.TextForegroundColorIndex:\t\t" << (unsigned int)plainTextExtension.textForegroundColorIndex << "\n";
    std::cout << "PlainTextExtension.TextBackgroundColorIndex:\t\t" << (unsigned int)plainTextExtension.textBackgroundColorIndex << "\n";
    std::cout << "PlainTextExtension.PlainTextData:\t\t\t" << plainTextExtension.plainTextData << "\n";
    std::cout << "PlainTextExtension.BlockTerminator:\t\t\t" << (unsigned int)plainTextExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Application Extension.
    */
    std::cout << "ApplicationExtension.ExtensionIntroducer:\t\t" << (unsigned int)applicationExtension.extensionIntroducer << "\n";
    std::cout << "ApplicationExtension.ExtensionLabel:\t\t\t" << (unsigned int)applicationExtension.extensionLabel << "\n";
    std::cout << "ApplicationExtension.BlockSize:\t\t\t\t" << (unsigned int)applicationExtension.blockSize << "\n";
    std::cout << "ApplicationExtension.ApplicationIdentifier:\t\t" << (unsigned int)applicationExtension.applicationIdentifier << "\n";
    std::cout << "ApplicationExtension.ApplicationAthenticationCode:\t" << (unsigned int)applicationExtension.applicationAthenticationCode << "\n";
    std::cout << "ApplicationExtension.ApplicationData:\t" << applicationExtension.applicationData << "\n";
    std::cout << "ApplicationExtension.BlockTerminator:\t\t\t" << (unsigned int)applicationExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Trailer.
    */
    std::cout << "Trailer.GIFTrailer:\t\t\t\t\t" << (unsigned int)trailer.gifTrailer << "\n";
    std::cout << "\n";
}

//TODO: Test this method.
std::vector<Color3> GIF::GetActiveColorTable()
{
    //If neither the globalColorTableFlag nor the localColorTableFlag has been set, then use the DEFAULT_COLOR_TABLE.
    if (0 == logicalScreenDescriptor.globalColorTableFlag &&
        0 == imageDescriptor.localColorTableFlag)
    {
        return DEFAULT_COLOR_TABLE;
    }

    return (1 == imageDescriptor.localColorTableFlag) ? 
            localColorTable.localColorTableVec : 
            globalColorTable.globalColorTableVec;                                
}

/*
* Mutators
*/
/*
* TODO:
* Add required GIF version to each section.
* Create a DisplayVariables(...) function. For null fields, output the word "null".
*/
//THIS METHOD IS ONLY FOR TESTING.
//void GIF::LoadAndDisplayFileContents(const std::string& filePath) const
//{
//    /*
//    * Open the file.
//    */
//    std::ifstream file;
//    file.open(filePath, std::ios::in | std::ios::binary);
//
//    if (!file.is_open())
//    {
//        std::cout << "\n\n" << "Error: File did not open successfuly." << "\n\n";
//        return;
//    }
//
//    //Base-16 byte index      Base-16 Byte value
//    std::cout << "Byte #" << "\t" << "Byte value (hexadecimal)" << "\n";
//    int byteNum = 0;
//    byte lastByteRead = NULL;
//    //while (EOF != file.peek())
//    //while (true)
//    while (lastByteRead != GIF::TRAILER_LABEL /*&& (byte)EOF != PeekNextByte(file, true)*/)
//    {
//        byte nextByte = GetNextByte(file, false);
//        lastByteRead = nextByte;
//        std::cout << (byteNum / 16) << "." << (byteNum % 16) << "\t";
//        std::cout << std::hex << byteNum;
//        std::cout << "\t";
//        std::cout << std::hex << (unsigned int)nextByte;
//        std::cout << "\t\t" << std::dec << (int)nextByte;
//        std::cout << "\n";
//        byteNum++;
//    }
//    int nextByte = PeekNextByte(file, false);
//    int x = 5;
//
//    /*
//    * Close the file.
//    */
//    file.close();
//}

//Format taken from https://www.w3.org/Graphics/GIF/spec-gif89a.txt
void GIF::Load(const std::string& filePath)
{
    byteVec = ReadBytesFromGIFFile(filePath);
    ReadGrammarGIFDataStream();


    ///*
    //* Extract the data from the file.
    //*/
    ////Exactly one occurrence.
    //std::cout << "Reading Header." << "\n";
    //header.Read(file);

    ////This decoder follows the specs of GIF version "89a". If the version of this GIF is "87a", this decoder may
    ////have problems.
    ////TODO: Make this decoder backwards compatible (be able to decode GIF "87a"s).
    //if (GIF::VERSION_87a == header.version)
    //{
    //    std::cout << "\n\n" << "Warning: Can't decode GIFs with version \"87a\" at this time." << "\n\n";
    //    system("pause");
    //    exit(0);
    //}

    ////Exactly one occurrence.
    //std::cout << "Reading LogicalScreenDescriptor." << "\n";
    //logicalScreenDescriptor.Read(file);

    ////Zero or one occurrences.
    //if (1 == logicalScreenDescriptor.globalColorTableFlag)
    //{
    //    std::cout << "Reading GlobalColorTable." << "\n";
    //    globalColorTable.Read(file, logicalScreenDescriptor.sizeOfGlobalColorTable);
    //}

    ////Zero or more occurrences of an image within the data stream (the GIF file).
    //unsigned int next8Bits = PeekNext8Bits(file, false);
    ///*
    //* NOTE: This reads 0x21, but it should be 0x2C. Based on reading the hex dump of the GIF in Sublime,
    //*       it appears that the file is 8 bytes behind by this point. Need to investigate why this is.
    //*/
    //std::cout << "Next 8 bits as hex = " << std::hex << "0x" << next8Bits << "\n";
    //while (IsMatchingLabel(BlockName_GraphicControlExtension, PeekNext8Bits(file, true)) ||
    //       IsMatchingLabel(BlockName_ImageDescriptor, PeekNext8Bits(file, false)))
    //{
    //    if (IsMatchingLabel(BlockName_GraphicControlExtension, PeekNext8Bits(file, true)))
    //        graphicControlExtension.Read(file);

    //    //Exactly one occurrence per image.
    //    std::cout << "Reading ImageDescriptor." << "\n";
    //    imageDescriptor.Read(file);

    //    //Zero or one occurrence per image.
    //    if (1 == imageDescriptor.localColorTableFlag)
    //    {
    //        std::cout << "Reading LocalColorTable." << "\n";
    //        localColorTable.Read(file, imageDescriptor.sizeOfLocalColorTable);
    //    }

    //    //Exactly one occurrence per image.
    //    std::cout << "Reading TableBasedImageData." << "\n";
    //    tableBasedImageData.Read(file, imageDescriptor.imageWidth, imageDescriptor.imageHeight);
    //}

    ////Zero or more occurrences.
    //while (IsExtensionIntroducer(PeekNext8Bits(file, true)
    //        && IsMatchingLabel(BlockName_CommentExtension, PeekSecondNext8Bits(file, false))))
    //{
    //    std::cout << "Reading CommentExtension." << "\n";
    //    commentExtension.Read(file);
    //}

    ////Zero or more occurrences.
    //while (IsExtensionIntroducer(PeekNext8Bits(file, true)
    //        && IsMatchingLabel(BlockName_PlainTextExtension, PeekSecondNext8Bits(file, false))))
    //{
    //    std::cout << "Reading PlainTextExtension." << "\n";
    //    plainTextExtension.Read(file);
    //}

    ////Zero or more occurrences.
    //while (IsExtensionIntroducer(PeekNext8Bits(file, true)
    //        && IsMatchingLabel(BlockName_ApplicationExtension, PeekSecondNext8Bits(file, false))))
    //{
    //    std::cout << "Reading ApplicationExtension." << "\n";
    //    applicationExtension.Read(file);
    //}

    ////Exactly one occurrence.
    //std::cout << "Reading Trailer." << "\n";
    //trailer.Read(file);

    /*
    * Close the file.
    */
    //file.close();
}

/*
The Grammar.

Legend:     <>    grammar word
            ::=   defines symbol
            *     zero or more occurrences
            +     one or more occurrences
            |     alternate element
            []    optional element

<GIF Data Stream>           ::= Header <Logical Screen> <Data>* Trailer
<Logical Screen>            ::= Logical Screen Descriptor [Global Color Table]
<Data>                      ::= <Graphic Block> | <Special-Purpose Block>
<Graphic Block>             ::= [Graphic Control Extension] <Graphic-Rendering Block>
<Graphic-Rendering Block>   :: = <Table-Based Image> | Plain Text Extension
<Table-Based Image>         ::= Image Descriptor [Local Color Table] Image Data
<Special-Purpose Block>     ::= Application Extension | Comment Extension
*/
//Always start reading the stream at the beginning, so no offset needed.
void GIF::ReadGrammarGIFDataStream()
{
    int byteVecIndex = header.Read(byteVec, 0);
    byteVecIndex = ReadGrammarLogicalScreen(byteVecIndex);
    while (!IsMatchingLabel(BlockName_Trailer, byteVec[byteVecIndex]))
    {
        byteVecIndex = ReadGrammarData(byteVecIndex);
    }
    byteVecIndex = trailer.Read(byteVec, byteVecIndex);
    //assertTrue(byteVec.size() == byteVecIndex);
}

//<Logical Screen> ::= Logical Screen Descriptor [Global Color Table] 
int GIF::ReadGrammarLogicalScreen(int byteVecIndex)
{
    byteVecIndex = logicalScreenDescriptor.Read(byteVec, byteVecIndex);
    if (1 == logicalScreenDescriptor.globalColorTableFlag)
    {
        byteVecIndex = globalColorTable.Read(byteVec, byteVecIndex, logicalScreenDescriptor.sizeOfGlobalColorTable);
    }
    return byteVecIndex;
}

//<Data> ::= <Graphic Block> | <Special-Purpose Block>
int GIF::ReadGrammarData(int byteVecIndex)
{
    if (IsNextGrammarSpecialPurposeBlock(byteVecIndex))
    {
        byteVecIndex = ReadGrammarSpecialPurposeBlock(byteVecIndex);
    }
    else
    {
        byteVecIndex = ReadGrammarGraphicBlock(byteVecIndex);
    }
    return byteVecIndex;
}

//<Graphic Block> ::= [Graphic Control Extension] <Graphic-Rendering Block>
int GIF::ReadGrammarGraphicBlock(int byteVecIndex)
{
    if (IsExtensionIntroducer(byteVec[byteVecIndex]) &&
        IsMatchingLabel(BlockName_GraphicControlExtension, byteVec[byteVecIndex + 1]))
    {
        byteVecIndex = graphicControlExtension.Read(byteVec, byteVecIndex);
    }
    byteVecIndex = ReadGrammarGraphicRenderingBlock(byteVecIndex);
    return byteVecIndex;
}

//<Graphic-Rendering Block> :: = <Table-Based Image> | Plain Text Extension
int GIF::ReadGrammarGraphicRenderingBlock(int byteVecIndex)
{
    if (IsExtensionIntroducer(byteVec[byteVecIndex]) &&
        IsMatchingLabel(BlockName_PlainTextExtension, byteVec[byteVecIndex + 1]))
    {
        byteVecIndex = plainTextExtension.Read(byteVec, byteVecIndex);
    }
    else
    {
        byteVecIndex = ReadGrammarTableBasedImage(byteVecIndex);
    }
    return byteVecIndex;
}

//<Table-Based Image> ::= Image Descriptor [Local Color Table] Image Data
int GIF::ReadGrammarTableBasedImage(int byteVecIndex)
{
    byteVecIndex = imageDescriptor.Read(byteVec, byteVecIndex);
    if (1 == imageDescriptor.localColorTableFlag)
    {
        byteVecIndex = localColorTable.Read(byteVec, byteVecIndex, imageDescriptor.sizeOfLocalColorTable);
    }
    //byteVecIndex = tableBasedImageData.Bypass(byteVec, byteVecIndex);
    unsigned int imageWidth = GetWidth();
    unsigned int imageHeight = GetHeight();
    byteVecIndex = tableBasedImageData.Read(byteVec, byteVecIndex, 
                                            imageDescriptor.imageLeftPosition, imageDescriptor.imageTopPosition, 
                                            imageWidth, imageHeight, GetActiveColorTable());
    return byteVecIndex;
}

//<Special-Purpose Block> ::= Application Extension | Comment Extension
int GIF::ReadGrammarSpecialPurposeBlock(int byteVecIndex)
{
    if (IsSpecificExtension(ExtensionName_ApplicationExtension, byteVecIndex))
    {
        byteVecIndex = applicationExtension.Read(byteVec, byteVecIndex);
    }
    else
    {
        byteVecIndex = commentExtension.Read(byteVec, byteVecIndex);
    }
    return byteVecIndex;
}

bool GIF::IsNextGrammarSpecialPurposeBlock(int byteVecIndex)
{
    return (IsExtensionIntroducer(byteVec[byteVecIndex]) &&
        (IsMatchingLabel(BlockName_ApplicationExtension, byteVec[byteVecIndex + 1]) ||
        IsMatchingLabel(BlockName_CommentExtension, byteVec[byteVecIndex + 1])));
}


int GIF::Header::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read signature. 3 bytes plus null terminator. Expects "GIF".
    signature.resize(4, NULL);
    for (int i = 0; i < 3; i++)
    {
        signature[i] = byteVec[byteVecIndex];
        byteVecIndex++;
    }
    if ("GIF" != signature)
        std::cout << "Error: Expected the \"GIF\" signature in the header, but found " << signature << " instead.\n";

    //Read version. 3 bytes plus null terminator. Expects "87a" or "89a".
    version.resize(4, NULL);
    for (int i = 0; i < 3; i++)
    {
        version[i] = byteVec[byteVecIndex];
        byteVecIndex++;
    }
    if ("87a" != version && "89a" != version)
        std::cout << "Error: In the header, expected the version to be either 87a or 89a, but got " << version << " instead.\n";

    return byteVecIndex;
}

int GIF::LogicalScreenDescriptor::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read Logical Screen Width. 2 bytes.
    logicalScreenWidth = GetTwoBytesAsLittleEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Logical Screen Height. 1 unsigned int.
    logicalScreenHeight = GetTwoBytesAsLittleEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;

    //Read Packed Fields. 1 byte (char).
    packedFields = byteVec[byteVecIndex];
    byteVecIndex++;
    //<Packed Fields>  =		Global Color Table Flag       1 bit
    globalColorTableFlag = (packedFields & 0x80) >> 7;
    //							Color Resolution              3 bits
    colorResolution = (packedFields & 0x70) >> 4;
    //							Sort Flag                     1 bit
    sortFlag = (packedFields & 0x08) >> 3;
    //							Size of Global Color Table    3 bits
    sizeOfGlobalColorTable = packedFields & 0x07;

    //Read Background Color Index. 1 byte (char).
    backgroundColorIndex = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Pixel Aspect Ratio. 1 byte (char).
    pixelAspectRatio = byteVec[byteVecIndex];
    byteVecIndex++;

    return byteVecIndex;
}

int GIF::GlobalColorTable::Read(std::vector<byte>& byteVec, int byteVecIndex, int sizeOfGlobalColorTable)
{
    std::cout << "Global Color Table will be used." << "\n";
    if (globalColorTableVec.size() > 0)
        globalColorTableVec.clear();

    int numBytesToRead = static_cast<int>(3 * pow(2, (sizeOfGlobalColorTable + 1))); //Assumes 8 bits == 1 byte.
    std::cout << "Num bytes to read for global color table = " << numBytesToRead << "\n";
    for (int byteIndex = 0; byteIndex < numBytesToRead; byteIndex++)
    {
        if (0 == byteIndex % 3)
            globalColorTableVec.push_back(Color3(0, 0, 0));

        byte nextByte = byteVec[byteVecIndex];
        byteVecIndex++;
        std::cout << "Byte index = " << byteIndex << "\t" << "Color component = " << (int)nextByte << "\n";
        float colorComponent = (unsigned int)(nextByte) / (float)255;
        switch (byteIndex % 3)
        {
        case 0: globalColorTableVec[byteIndex / 3].SetRed(colorComponent); break;
        case 1: globalColorTableVec[byteIndex / 3].SetGreen(colorComponent); break;
        case 2: globalColorTableVec[byteIndex / 3].SetBlue(colorComponent); break;
        default: break;
        }
    }

    return byteVecIndex;
}

int GIF::ImageDescriptor::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read Image Separator. 1 byte.
    imageSeparator = byteVec[byteVecIndex];
    byteVecIndex++;

    //Read Image Left Position. 2 bytes.
    imageLeftPosition = GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Image Top Position. 2 bytes.
    imageTopPosition = GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Image Width. 2 bytes.
    GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Image Height. 2 bytes.
    GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;

    //Read Packed Fields. 1 byte.
    packedFields = byteVec[byteVecIndex];
    byteVecIndex++;
    //<Packed Fields> =		Local Color Table Flag        1 Bit
    localColorTableFlag = (packedFields & 0X80) >> 7;
    //						Interlace Flag                1 Bit
    interlaceFlag = (packedFields & 0X40) >> 6;
    //						Sort Flag                     1 Bit
    sortFlag = (packedFields & 0X20) >> 5;
    //						Reserved                      2 Bits
    reserved = (packedFields & 0X18) >> 3;
    //						Size of Local Color Table     3 Bits
    sizeOfLocalColorTable = (packedFields & 0X07);

    return byteVecIndex;
}

int GIF::LocalColorTable::Read(std::vector<byte>& byteVec, int byteVecIndex, int sizeOfLocalColorTable)
{
    std::cout << "Local Color Table will be used." << "\n";
    int numBytesToRead = static_cast<int>(3 * pow(2, (sizeOfLocalColorTable + 1))); //Assumes 8 bits == 1 byte.
    for (int byteIndex = 0; byteIndex < numBytesToRead; byteIndex++)
    {
        if (0 == byteIndex % 3)
            localColorTableVec.push_back(Color3(0, 0, 0));

        byte nextByte = byteVec[byteVecIndex];
        byteVecIndex++;
        std::cout << "Byte index = " << byteIndex << "\t" << "Color component = " << (int)nextByte << "\n";
        float colorComponent = (unsigned int)(nextByte) / (float)255;
        switch (byteIndex % 3)
        {
        case 0: localColorTableVec[byteIndex / 3].SetRed(colorComponent); break;
        case 1: localColorTableVec[byteIndex / 3].SetGreen(colorComponent); break;
        case 2: localColorTableVec[byteIndex / 3].SetBlue(colorComponent); break;
        default: break;
        }
    }

    return byteVecIndex;
}

GIF::TableBasedImageData::Frame::Frame(unsigned int offsetX, unsigned int offsetY, unsigned int width, unsigned int height)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->width = width;
    this->height = height;
}


//Bypasses the bytes associated with the table based image data section, so that I can avoid the lzw complexity
//for now and test whether the other GIF fields are being read properly.
int GIF::TableBasedImageData::Bypass(std::vector<byte>& byteVec, int byteVecIndex)
{
    bool isEndOfLZWData = false;

    while (!isEndOfLZWData)
    {
        byte nextByte = byteVec[byteVecIndex];
        byteVecIndex++;

        if (0x00 == nextByte)
            break;
        
        lzwMinimumCodeSize = nextByte;
        int numBytesOfLZWEncodedImageData = byteVec[byteVecIndex];
        byteVecIndex++;
        for (int byteCount = 0; byteCount < numBytesOfLZWEncodedImageData; byteCount++)
        {
            byteVecIndex++;
        }
        if (0 == numBytesOfLZWEncodedImageData)
            isEndOfLZWData = true;
   }

    return byteVecIndex;
}

/*
* The first byte of TableBasedImageData is the lzwMinimumCodeSize, which is the number of bits to read per pixel. These
* bits are interpreted as an index into the activeColorTable, where a list pixel colors is returned. The lzwCurrentCodeSize
* starts at the lzwMinimumCodeSize, but grows (indicating more bits to read per pixel) as new patterns are stored in the
* codeTable.
*
* The codeTable is initialized to have 2^lzwMinimumCodeSize number of entries, where the value of each entry is its index.
* The (2^lzwMinimumCodeSize + 1) entry is the clearCode, and its value is its index in the codeTable.
*       When the clearCode is encountered, all entries in the codeTable after the (2^lzwMinimumCodeSize + 2) entry should
*       be removed.
*       NOTE: The clearCode can appear anywhere in the LZW bytes, but most encoders will put it as the first byte of a new
*             LZW sub-block. However, because the clearCode *can* be anywhere in an LZW sub-block, you need to check for it
*             before interpreting the next set of lzwCurrentCodeSize bits as a codeTable entry. Note too that the
*             clearCode indicates you read numBitsEncodingClearCode number of bits, while lzwMinimumCodeSize indicates to read 
*             lzwMinimumCodeSize many bits, but these values may be different.
* The (2^lzwMinimumCodeSize + 2) entry is the endOfInformation code, and its value is its index in the codeTable.
*       When the EndOfInformation code is encountered, there are no more LZW bytes to read.
*       NOTE: The EndOfInformation code should be the very last LZW byte to read, which means that if you are expecting to read
*             more LZW bytes (i.e. the first byte of TableBasedImageData told you there would be more to read), then there's
*             an error.
*
* TableBasedImageData has the following format:
*   Byte 0: lzwMinimumCodeSize
*   Byte 1: numBytesToRead (excluding this byte) for the following LZW sub-block.
*   Bytes 2 through (numBytesToRead + 1): LZW bytes.
*       while (numBytesToRead have not all been read yet)
*           a) Check the next numBitsEncodingClearCode and compare that int value to clearCode. If match, re-init codeTable.
*           b) If no match in (a), then starting at the same starting bit offset as in (a), check the next lzwCurrentCodeSize
*               bits. Interpret them as a code.
*                   1a) If the code is already in the codeTable, output the pixel colors derived from that entry.
*                   1b) Let firstSubValue be the first sub-value stored at the code index in codeTable.
*                   1c) Create a new codeTable entry, which has the sub-values {previousCode, firstSubValue}.
*                   ---------------------------------------------------------------------------------------------
*                   2a) Else, let firstSubValue be the first sub-value stored at the previousCode index.
*                   2b) Output the pixels derived from {previousCode, firstSubValue}.
*                   2c) Create a new codeTable entry, which has the sub-values {previousCode, firstSubValue}.
*   Byte numBytesToRead + 2: numBytesToRead (Eventually this will be 0. For this example, it is 0 at this point.)
*   Byte numBytesToRead + 3: endOfInformation code.
*/
int GIF::TableBasedImageData::Read(std::vector<byte>& byteVec, int byteVecIndex, 
                                    unsigned int imageLeftPosition, unsigned int imageTopPosition,
                                    unsigned int imageWidth, unsigned int imageHeight, std::vector<Color3> activeColorTable)
{
    lzwMinimumCodeSize = byteVec[byteVecIndex];
    byteVecIndex++;
    //const int numBitsEncodingClearCode = GetNumBitsEncodingClearCode();
    const int numBitsEncodingClearCode = lzwMinimumCodeSize + 1;
    const int clearCode = (1 << lzwMinimumCodeSize);
    const int endOfInformation = (1 << lzwMinimumCodeSize) + 1;

    std::vector<std::vector<int>> codeTable; //A table containing all sets of indeces that, when encountered for the first time,
                                             //have not been stored in either this table or the activeColorTable before.
    InitCodeTable(codeTable, activeColorTable);

    //Outer loop goes through all LZW sub-blocks (frames).
    int previousByteVecIndex = byteVecIndex;
    while (true)
    {
        std::vector<Frame> frameVec;
        Frame newFrame = Frame(imageLeftPosition, imageTopPosition, imageWidth, imageHeight);
        previousByteVecIndex = byteVecIndex;
        /*byteVecIndex = ReadFrames(frameVec, imageLeftPosition, imageTopPosition, imageWidth, imageHeight, byteVec, byteVecIndex, 
                                  activeColorTable, codeTable, numBitsEncodingClearCode, clearCode, endOfInformation);*/
        byteVecIndex = ReadFrame(newFrame, byteVec, byteVecIndex, activeColorTable, codeTable, numBitsEncodingClearCode, 
                                 clearCode, endOfInformation);
        if (newFrame.pixelColorVec.size() > 0)
        {
            imageData.push_back(newFrame);
        }

        //NOTE: This is kind of a weak way to break out of the infinite while loop. This if statement is weakly
        //      checking that the last LZW sub-block was 0 bytes long (but was really 1 byte because of the initial byte
        //      in a sub-block indicating how many of the following bytes should be read). A 0-byte sub-block will always
        //      terminate LZW sub-blocks.
        if (byteVecIndex == previousByteVecIndex + 1)
        {
            break;
        }
    }

    return byteVecIndex;
}

void GIF::TableBasedImageData::InitCodeTable(std::vector<std::vector<int>>& codeTable,
                                             const std::vector<Color3>& activeColorTable)
{
    int numColorsInFrame = (1 << lzwMinimumCodeSize);
    codeTable.clear();
    codeTable.reserve(numColorsInFrame + 2);
    for (int codeIndex = 0; codeIndex < numColorsInFrame + 2; codeIndex++)
    {
        std::vector<int> codeTableValue;
        codeTableValue.push_back(codeIndex);
        codeTable.push_back(codeTableValue);
    }
}


//If clear code then re-init table
//If last code was a clear code, then...
//  * Output color at the currentCode index
//Else If currentCode exists in table, then...
//  * Output colors at the currentCode index
//  * Add new code to table with value {colors at the previousCode index, first color at the currentCodeIndex}
//Else //If currentCode does not exists in the table, then...
//  * Output {colors at the previousIndex, first color at the previousIndex}
//  * Add new code to table with value {colors at the previousIndex, first color at the previousIndex}
//If currentCode is largest possible code given the lzwCurrentCodeSize, then lzwCurrentCodeSize++
//int GIF::TableBasedImageData::ReadFrames(std::vector<Frame>& frameVec, int imageLeftPosition, int imageTopPosition, 
//                                        int imageWidth, int imageHeight, const std::vector<byte>& byteVec, int byteVecIndex,
//                                        const std::vector<Color3>& activeColorTable, std::vector<std::vector<int>>& codeTable,
//                                        int numBitsEncodingClearCode, int clearCode, int endOfInformation)
//{
//    int previousCode = -1;
//    int currentCode = -1;
//    int lzwCurrentCodeSize = lzwMinimumCodeSize + 1;
//
//    //The first byte of an LZW sub-block is always the number of bytes to read for the sub-block.
//    int numBytesToRead = byteVec[byteVecIndex];
//    byteVecIndex++;
//    std::vector<byte> tempByteVec;
//    while (0 != numBytesToRead)
//    {
//        //Read this LZW sub-block's bytes.
//        tempByteVec.insert(tempByteVec.begin() + tempByteVec.size(), byteVec.begin() + byteVecIndex,
//            byteVec.begin() + byteVecIndex + numBytesToRead);
//        numBytesToRead = byteVec[byteVecIndex];
//        byteVecIndex++;
//    }
//    BitReader bitReader = BitReader(tempByteVec);
//    
//    Frame newFrame = Frame(imageLeftPosition, imageTopPosition, imageWidth, imageHeight);
//    
//    while (!(numBytesToRead == bitReader.GetCurrentByteIndex() ||
//                (bitReader.GetCurrentByteIndex() == numBytesToRead - 1 && 
//                (bitReader.GetCurrentBitIndex() + lzwCurrentCodeSize >= 8 || 
//                    bitReader.GetCurrentBitIndex() + numBitsEncodingClearCode >= 8))))
//    {
//        //Read the next code as if it were clearCode. If it's not clearCode, then re-read the next code as a colorTable index.
//        //int maskShiftForClearCode = sizeof(threeBytes) * 8 - numBitsEncodingClearCode;
//        //int maskShiftForColorTableIndex = sizeof(threeBytes) * 8 - lzwCurrentCodeSize;
//        //currentCode = ((streamChunk << maskShiftForClearCode) >> maskShiftForClearCode);
//        currentCode = bitReader.PeekBitsAsLittleEndian(numBitsEncodingClearCode);
//        if (clearCode == currentCode)
//        {
//            int bitReaderCurrentByte = bitReader.GetCurrentByteIndex();
//            bitReader.GetBitsAsLittleEndian(numBitsEncodingClearCode);
//
//            //previousCode = -1;
//            //currentCode = -1;
//
//            InitCodeTable(codeTable, activeColorTable);
//            lzwCurrentCodeSize = lzwMinimumCodeSize + 1;
//            frameVec.push_back(newFrame);
//            if (newFrame.pixelColorVec.size() > 0)
//            {
//                imageData.push_back(newFrame);
//            }
//            newFrame = Frame(imageLeftPosition, imageTopPosition, imageWidth, imageHeight);
//        }
//        else if (endOfInformation == currentCode)
//        {
//            //This whole method is a test to see if data between frames is continuous, so long as a clear code is not
//            //encountered. Raster data can only be 255 bytes. That 255th byte most likely has leftover bits. Do they carry
//            //over to the beginning of the next raster data block (frame)? If so, then how does the EOI work? Does that
//            //completely end raster data processing, or only the processing of the raster data that is at most 255 bytes?
//            break;
//        }
//        else
//        {
//            previousCode = currentCode;
//            //currentCode = (streamChunk << maskShiftForColorTableIndex) >> maskShiftForColorTableIndex;
//            int bitReaderCurrentByte = bitReader.GetCurrentByteIndex();
//            currentCode = bitReader.GetBitsAsLittleEndian(lzwCurrentCodeSize);
//
//            //If currentCode is largest possible code given the lzwCurrentCodeSize, then lzwCurrentCodeSize++
//            //TODO: Don't allow lzwCurrentCodeSize to surpass 12.
//            if (currentCode >= (1 << lzwCurrentCodeSize))
//            {
//                lzwCurrentCodeSize++;
//            }
//
//            int firstSubValue;
//            if (clearCode == previousCode)
//            {
//                std::vector<Color3> colorsAtCodeTableIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, currentCode,
//                    activeColorTable);
//                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
//                    colorsAtCodeTableIndex.begin(), colorsAtCodeTableIndex.end());
//                continue;
//            }
//            /*
//            * 1a) If the code is already in the codeTable, output the pixel colors derived from that entry.
//            * 1b) Let firstSubValue be the first sub-value stored at the currentCodeIndex.
//            * 1c) Create a new codeTable entry, which has the sub-values { previousCode, firstSubValue }.
//            */
//            //Else If currentCode exists in table, then...
//            //  * Output colors at the currentCode index
//            //  * Add new code to table with value {colors at the previousCode index, first color at the currentCodeIndex}
//            else if ((unsigned int) currentCode < codeTable.size())
//            {
//                //1a
//                std::vector<Color3> colorsAtCodeTableIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, currentCode,
//                                                                                                    activeColorTable);
//                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
//                                                colorsAtCodeTableIndex.begin(), colorsAtCodeTableIndex.end());   
//
//                //1b
//                firstSubValue = codeTable.at(currentCode)[0];
//            }
//
//            /*
//            * 2a) Else, let firstSubValue be the first sub-value stored at the previousCode index.
//            * 2b) Output the pixels derived from{ previousCode, firstSubValue }.
//            * 2c) Create a new codeTable entry, which has the sub-values { previousCode, firstSubValue }.
//            */
//            //Else //If currentCode does not exists in the table, then...
//            //  * Output {colors at the previousIndex, first color at the previousIndex}
//            //  * Add new code to table with value {colors at the previousIndex, first color at the previousIndex}
//            else
//            {
//                //TODO: Debug these line. What is the correct behavior here? If previousCode is 300 but my table only has
//                //      280 entries, then this will crash. Currently, when I add a new entry, I just push_back in the vector.
//                //      But in this example, since previousCode is 300, that means last iteration of this loop currentCode
//                //      was 300, which wasn't in the table, so I created a new entry in the table, but at index 280 (because
//                //      that was the back of the vector for this example), but not 300.
//                //2a
//                firstSubValue = codeTable.at(previousCode)[0];
//
//                ////2b
//                std::vector<Color3> colorsAtPreviousCodeIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, previousCode,
//                                                                                                    activeColorTable);
//                std::vector<Color3> colorsAtFirstSubValueIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, firstSubValue,
//                                                                                                        activeColorTable);
//
//                //firstSubValue = 0;
//                //std::vector<Color3> colorsAtPreviousCodeIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, 0,
//                //    activeColorTable);
//                //std::vector<Color3> colorsAtFirstSubValueIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, firstSubValue,
//                //    activeColorTable);
//
//
//                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
//                    colorsAtPreviousCodeIndex.begin(), colorsAtPreviousCodeIndex.end());
//                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
//                    colorsAtFirstSubValueIndex.begin(), colorsAtFirstSubValueIndex.end());
//            }
//            //1c and 2c
//            std::vector<int> newEntrySubValues;
//            if (-1 == previousCode) { newEntrySubValues = {firstSubValue}; }
//            else { newEntrySubValues = {previousCode, firstSubValue}; }
//            codeTable.push_back(newEntrySubValues);
//        }
//    }
//
//    byteVecIndex += bitReader.GetCurrentByteIndex();
//    return byteVecIndex;
//}






int GIF::TableBasedImageData::ReadFrame(Frame& newFrame, const std::vector<byte>& byteVec, int byteVecIndex,
    const std::vector<Color3>& activeColorTable, std::vector<std::vector<int>>& codeTable,
    int numBitsEncodingClearCode, int clearCode, int endOfInformation)
{
    int previousCode = -1;
    int currentCode = -1;
    int lzwCurrentCodeSize = lzwMinimumCodeSize + 1;

    //The first byte of an LZW sub-block is always the number of bytes to read for the sub-block.
    const int numBytesToRead = byteVec[byteVecIndex];
    byteVecIndex++;

    if (0 == numBytesToRead)
    {
        return byteVecIndex;
    }

    int ifCount = 0;
    int elseCount = 0;
    int insertCount = 0;
    //Read this LZW sub-block's bytes.
    std::vector<byte> tempByteVec = std::vector<byte>(byteVec.begin() + byteVecIndex,
        byteVec.begin() + byteVecIndex + numBytesToRead);
    BitReader bitReader = BitReader(tempByteVec);
    while (!(numBytesToRead == bitReader.GetCurrentByteIndex() ||
        (bitReader.GetCurrentByteIndex() == numBytesToRead - 1 &&
        (bitReader.GetCurrentBitIndex() + lzwCurrentCodeSize >= 8 ||
        bitReader.GetCurrentBitIndex() + numBitsEncodingClearCode >= 8))))
    {
        //Read the next code as if it were clearCode. If it's not clearCode, then re-read the next code as a colorTable index.
        //int maskShiftForClearCode = sizeof(threeBytes) * 8 - numBitsEncodingClearCode;
        //int maskShiftForColorTableIndex = sizeof(threeBytes) * 8 - lzwCurrentCodeSize;
        //currentCode = ((streamChunk << maskShiftForClearCode) >> maskShiftForClearCode);
        currentCode = bitReader.PeekBitsAsLittleEndian(numBitsEncodingClearCode);
        if (clearCode == currentCode)
        {
            ifCount++;

            int bitReaderCurrentByte = bitReader.GetCurrentByteIndex();
            bitReader.GetBitsAsLittleEndian(numBitsEncodingClearCode);

            //previousCode = -1;
            //currentCode = -1;

            InitCodeTable(codeTable, activeColorTable);
            lzwCurrentCodeSize = lzwMinimumCodeSize + 1;
        }
        else if (endOfInformation == currentCode)
        {
            break;
        }
        else
        {
            elseCount++;

            previousCode = currentCode;
            //currentCode = (streamChunk << maskShiftForColorTableIndex) >> maskShiftForColorTableIndex;
            int bitReaderCurrentByte = bitReader.GetCurrentByteIndex();
            currentCode = bitReader.GetBitsAsLittleEndian(lzwCurrentCodeSize);

            //If currentCode is largest possible code given the lzwCurrentCodeSize, then lzwCurrentCodeSize++
            //TODO: Don't allow lzwCurrentCodeSize to surpass 12.
            if (currentCode >= (1 << lzwCurrentCodeSize))
            {
                lzwCurrentCodeSize++;
            }

            int firstSubValue;
            if (clearCode == previousCode)
            {
                std::vector<Color3> colorsAtCodeTableIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, currentCode,
                    activeColorTable);
                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
                    colorsAtCodeTableIndex.begin(), colorsAtCodeTableIndex.end());
                continue;
            }
            /*
            * 1a) If the code is already in the codeTable, output the pixel colors derived from that entry.
            * 1b) Let firstSubValue be the first sub-value stored at the currentCodeIndex.
            * 1c) Create a new codeTable entry, which has the sub-values { previousCode, firstSubValue }.
            */
            //Else If currentCode exists in table, then...
            //  * Output colors at the currentCode index
            //  * Add new code to table with value {colors at the previousCode index, first color at the currentCodeIndex}
            else if ((unsigned int)currentCode < codeTable.size())
            {
                //1a
                std::vector<Color3> colorsAtCodeTableIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, currentCode,
                    activeColorTable);
                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
                    colorsAtCodeTableIndex.begin(), colorsAtCodeTableIndex.end());

                //1b
                //firstSubValue = codeTable.at(currentCode)[0];
                firstSubValue = GetFirstTerminalCode(codeTable, currentCode);
            }

            /*
            * 2a) Else, let firstSubValue be the first sub-value stored at the previousCode index.
            * 2b) Output the pixels derived from{ previousCode, firstSubValue }.
            * 2c) Create a new codeTable entry, which has the sub-values { previousCode, firstSubValue }.
            */
            //Else //If currentCode does not exists in the table, then...
            //  * Output {colors at the previousIndex, first color at the previousIndex}
            //  * Add new code to table with value {colors at the previousIndex, first color at the previousIndex}
            else
            {
                //TODO: Debug these line. What is the correct behavior here? If previousCode is 300 but my table only has
                //      280 entries, then this will crash. Currently, when I add a new entry, I just push_back in the vector.
                //      But in this example, since previousCode is 300, that means last iteration of this loop currentCode
                //      was 300, which wasn't in the table, so I created a new entry in the table, but at index 280 (because
                //      that was the back of the vector for this example), but not 300.
                //2a
                //firstSubValue = codeTable.at(previousCode)[0];
                firstSubValue = GetFirstTerminalCode(codeTable, previousCode);

                ////2b
                std::vector<Color3> colorsAtPreviousCodeIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, previousCode,
                    activeColorTable);
                std::vector<Color3> colorsAtFirstSubValueIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, firstSubValue,
                    activeColorTable);

                //firstSubValue = 0;
                //std::vector<Color3> colorsAtPreviousCodeIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, 0,
                //    activeColorTable);
                //std::vector<Color3> colorsAtFirstSubValueIndex = GetListOfColorsFromCodeTableAtIndex(codeTable, firstSubValue,
                //    activeColorTable);


                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
                    colorsAtPreviousCodeIndex.begin(), colorsAtPreviousCodeIndex.end());
                newFrame.pixelColorVec.insert(newFrame.pixelColorVec.end(),
                    colorsAtFirstSubValueIndex.begin(), colorsAtFirstSubValueIndex.end());
            }
            //1c and 2c
            std::vector<int> newEntrySubValues;
            if (-1 == previousCode) { newEntrySubValues = { firstSubValue }; }
            else { newEntrySubValues = { previousCode, firstSubValue }; }
            codeTable.push_back(newEntrySubValues);
            insertCount++;
        }
    }

    return byteVecIndex + numBytesToRead;
}






std::vector<Color3> GIF::TableBasedImageData::GetListOfColorsFromCodeTableAtIndex(const std::vector<std::vector<int>>& codeTable, 
                                                                                  int index,
                                                                                  const std::vector<Color3>& activeColorTable)
{
    std::vector<Color3> colorVec;
    for (unsigned int subValueIndex = 0; subValueIndex < codeTable.at(index).size(); subValueIndex++)
    {
        //Base case: The sub value maps to one of the first indeces in codeTable, which in turn maps to a value equal to its
        //index. This value is an index into the activeColorTable, which yields a Color3.
        if (codeTable.at(index)[subValueIndex] < (1 << lzwMinimumCodeSize))
        {
            int activeColorTableIndex = codeTable.at(index)[subValueIndex];
            colorVec.push_back(activeColorTable[activeColorTableIndex]);
        }

        //Recursive case
        else
        {
            std::vector<Color3> subValueColorVec = GetListOfColorsFromCodeTableAtIndex(codeTable, 
                                                                                       codeTable.at(index)[subValueIndex],
                                                                                       activeColorTable);
            colorVec.insert(colorVec.begin(), subValueColorVec.begin(), subValueColorVec.end());
        }
    }
    return colorVec;
}

int GIF::TableBasedImageData::GetFirstTerminalCode(const std::vector<std::vector<int>>& codeTable, int index)
{
    int firstTerminalCode;

    //Base case: The sub value maps to one of the first indeces in codeTable, which in turn maps to a value equal to its
    //index. This value is an index into the activeColorTable, which yields a Color3.
    if (codeTable.at(index)[0] < (1 << lzwMinimumCodeSize))
    {
        firstTerminalCode = codeTable.at(index)[0];
    }

    //Recursive case
    else
    {
        firstTerminalCode = GetFirstTerminalCode(codeTable, codeTable.at(index)[0]);
    }
    
    return firstTerminalCode;
}

//void GIF::TableBasedImageData::Read(std::ifstream& file, unsigned int imageWidth, unsigned int imageHeight)
//{
//    //Read LZW Minimum Code Size. 1 byte (char).
//    GetNext8Bits(file, lzwMinimumCodeSize, false);
//
//    /*
//    * Read Image Data.
//    */
//    imageData.resize(imageWidth * imageHeight);
//    std::string buffer = "";
//    int totalImageDataBits = 0;
//    //Extract the compressed bits.
//    for (unsigned int imageDataIndex = 0; imageDataIndex < imageData.capacity(); imageDataIndex++)
//    {
//        totalImageDataBits += lzwMinimumCodeSize;
//        double packedBitsToReadBytesRatio =
//            (totalImageDataBits / (double)(buffer.size() * 8)) - totalImageDataBits / (buffer.size() * 8);
//        if (0 == buffer.size() || packedBitsToReadBytesRatio > 0)
//            buffer.insert(buffer.begin(), GetNext8Bits(file, false));
//    }
//    //Decompress the bits. Bits are read from the buffer going from back to front. Each set of bits of size
//    //lzwMinimumCodeSize represents an integer that acts as an index into either the global or local color table,
//    //and is the color of a bit in the image. 
//    for (unsigned int imageDataIndex = 0; imageDataIndex < imageData.size(); imageDataIndex++)
//    {
//        for (int bitIndex = (int)lzwMinimumCodeSize - 1; bitIndex >= 0; bitIndex--)
//        {
//            unsigned int colorIndex = 0;
//            colorIndex = colorIndex << 1;
//            int bufferIndex = buffer.size() - 1 - imageDataIndex * lzwMinimumCodeSize - bitIndex;
//            if (bufferIndex < 0)
//            {
//                std::cout << "\n\n" << "Error: bufferIndex must be nonnegative, but has a value of " << bufferIndex << "\n\n";
//            }
//            colorIndex = colorIndex | buffer[bufferIndex];
//        }
//    }
//}

int GIF::GraphicControlExtension::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read Extension Introducer. 1 byte (char).
    extensionIntroducer = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Graphic Control Label. 1 byte (char).
    graphicControlLabel = byteVec[byteVecIndex];
    byteVecIndex++;

    //Read Block Size. 1 byte.
    blockSize = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Packed Fields.
    packedFields = byteVec[byteVecIndex];
    byteVecIndex++;
    //<Packed Fields> =			Reserved                      3 Bits
    reserved = (packedFields & 0xE0) >> 5;
    //							Disposal Method               3 Bits
    disposalMethod = (packedFields & 0x1C) >> 2;
    //							User Input Flag               1 Bit
    userInputFlag = (packedFields & 0x02) >> 1;
    //							Transparent Color Flag        1 Bit
    transparentColorFlag = (packedFields & 0x01);

    //Read Delay Time. 1 unsigned int.
    delayTime = GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Transparent Color Index. 1 byte.
    transparentColorIndex = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Block Terminator. 1 byte.
    blockTerminator = byteVec[byteVecIndex];
    byteVecIndex++;

    return byteVecIndex;
}

int GIF::CommentExtension::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read Extension Introducer. Read 1 byte.
    extensionIntroducer = byteVec[byteVecIndex];
    byteVecIndex++;

    //Read Comment Data.
    unsigned int subBlockSize = byteVec[byteVecIndex];
    if (0 != subBlockSize)
    {
        byteVecIndex++;
        for (unsigned int subBlockIndex = 0; subBlockIndex < subBlockSize; subBlockIndex++)
        {
            commentData += byteVec[byteVecIndex];
            byteVecIndex++;
        }
    }

    //Read Block Terminator. Read 1 byte.
    blockTerminator = byteVec[byteVecIndex];
    byteVecIndex++;

    return byteVecIndex;
}

int GIF::PlainTextExtension::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read Extension Introducer. 1 byte.
    extensionIntroducer = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Plain Text Label. 1 byte.
    plainTextLabel = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Block Size. 1 byte.
    blockSize = byteVec[byteVecIndex];
    byteVecIndex++;

    //Read Text Grid Left Position. 1 unsigned int.
    textGridLeftPosition = GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Text Grid Top Position. 1 unsigned int.
    textGridTopPosition = GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Text Grid Width. 1 unsigned int.
    textGridWidth = GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;
    //Read Text Grid Height. 1 unsigned int.
    textGridHeight = GetTwoBytesAsBigEndian(byteVec[byteVecIndex], byteVec[byteVecIndex + 1]);
    byteVecIndex += 2;

    //Read Character Cell Width. 1 byte.
    characterCellWidth = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Character Cell Height. 1 byte.
    characterCellHeight = byteVec[byteVecIndex];
    byteVecIndex++;

    //Read Text Foreground Color Index. 1 byte.
    textForegroundColorIndex = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Text Background Color Index. 1 byte.
    textBackgroundColorIndex = byteVec[byteVecIndex];
    byteVecIndex++;

    //Read Plain Text Data.
    unsigned int subBlockSize = byteVec[byteVecIndex];
    if (0 != subBlockSize)
    {
    byteVecIndex++;
        for (unsigned int subBlockIndex = 0; subBlockIndex < subBlockSize; subBlockIndex++)
        {
            plainTextData += byteVec[byteVecIndex];
            byteVecIndex++;
        }
    }

    //Read Block Terminator. 1 byte.
    blockTerminator = byteVec[byteVecIndex];
    byteVecIndex++;

    return byteVecIndex;
}

int GIF::ApplicationExtension::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read Extension Introducer. 1 byte.
    extensionIntroducer = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Extension Label. 1 byte.
    extensionLabel = byteVec[byteVecIndex];
    byteVecIndex++;
    //Read Block Size. 1 byte.
    blockSize = byteVec[byteVecIndex];
    byteVecIndex++;

    //Read Application Identifier. 8 bytes.
    applicationIdentifier = 0L;
    for (int byteIndex = 0; byteIndex < 8; byteIndex++) //Assumes 1 byte == 8 bits
    {
        byte nextByte = byteVec[byteVecIndex];
        byteVecIndex++;
        applicationIdentifier = applicationIdentifier << 8;
        applicationIdentifier = applicationIdentifier | nextByte;
    }
    //Read ApplicationAthentication Code. 3 bytes.
    applicationAthenticationCode = 0L;
    for (int byteIndex = 0; byteIndex < 3; byteIndex++) //Assumes 1 byte == 8 bits
    {
        byte nextByte = byteVec[byteVecIndex];
        byteVecIndex++;
        applicationAthenticationCode = applicationAthenticationCode << 8;
        applicationAthenticationCode = applicationAthenticationCode | nextByte;
    }

    //Read Application Data.
    unsigned int subBlockSize = byteVec[byteVecIndex];
    if (0 != subBlockSize)
    {
        byteVecIndex++;
        for (unsigned int subBlockIndex = 0; subBlockIndex < subBlockSize; subBlockIndex++)
        {
            applicationData += byteVec[byteVecIndex];
            byteVecIndex++;
        }
    }

    //Read Block Terminator. 1 byte.
    blockTerminator = byteVec[byteVecIndex];
    byteVecIndex++;

    return byteVecIndex;
}

int GIF::Trailer::Read(std::vector<byte>& byteVec, int byteVecIndex)
{
    //Read GIF Trailer. 1 byte.
    gifTrailer = byteVec[byteVecIndex];
    byteVecIndex++;
    return byteVecIndex;
}
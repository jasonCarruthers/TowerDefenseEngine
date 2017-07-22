#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../include/2DGraphics/Image.h"
#include "../../include/2DGraphics/Color.h"
#include "../../include/Window/Pixel.h"


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
    width = 0;
    height = 0;
}

/*
* Accessors
*/
char Image::PeekNext8Bits(std::ifstream& file)
{
    if (!file.is_open())
        return;

    char peekChar = (char) file.peek();
    if (EOF == peekChar)
        std::cout << "\n\n" << "Error: EOF reached! Could not peek next 8 bits." << "\n\n";

    return peekChar;
}

//Gets the 8 bits after the next 8 bits.
char Image::PeekSecondNext8Bits(std::ifstream& file)
{
    char next8Bits = NULL;
    GetNext8Bits(file, next8Bits);
    char secondNext8Bits = PeekNext8Bits(file);
    file.putback(next8Bits);
    return secondNext8Bits;
}

void Image::GetNext8Bits(std::ifstream& file, char& nextChar)
{
    nextChar = NULL;

    if (!file.is_open())
        return;

    file.get(nextChar);
    if (EOF == nextChar)
        std::cout << "\n\n" << "Error: EOF reached! Could not get next 8 bits." << "\n\n";
}

void Image::GetNext16Bits(std::ifstream& file, unsigned int& nextUnsignedInt)
{
    nextUnsignedInt = 0;

    if (!file.is_open())
        return;

    char nextChar;
    GetNext8Bits(file, nextChar);
    nextUnsignedInt = (int)nextChar;
    GetNext8Bits(file, nextChar);
    nextUnsignedInt = nextUnsignedInt << (int)nextChar;
}


/*
* Mutators
*/





/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class GIF
* -------------------------------------------------------------------------------------------------------
*/
/*
* Static constants
*/
const int GIF::EXTENSION_INTRODUCER = 33;               //0x21

const int GIF::IMAGE_DESCRIPTOR_LABEL = 44;             //0x2C
const int GIF::GRAPHIC_CONTROL_EXTENSION_LABEL = 249;   //0xF9
const int GIF::COMMENT_EXTENSION_LABEL = 254;           //0xFE
const int GIF::PLAIN_TEXT_EXTENSION_LABEL = 1;          //0x01
const int GIF::APPLICATION_EXTENSION_LABEL = 255;       //0xFF
const int GIF::TRAILER_LABEL = 59;                      //0x3B

static const std::string VERSION_87a = "87a";
static const std::string VERSION_89a = "89a";

const std::string LOGICAL_SCREEN_DESCRIPTOR_REQUIRED_VERSION = VERSION_87a;
const std::string GLOBAL_COLOR_TABLE_REQUIRED_VERSION = VERSION_87a;
const std::string IMAGE_DESCRIPTOR_REQUIRED_VERSION = VERSION_87a;
const std::string LOCAL_COLOR_TABLE_REQUIRED_VERSION = VERSION_87a;
const std::string GRAPHIC_CONTROL_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string COMMENT_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string PLAIN_TEXT_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string APPLICATION_EXTENSION_REQUIRED_VERSION = VERSION_89a;
const std::string TRAILER_REQUIRED_VERSION = VERSION_87a;

/*
* Constructors
*/
GIF::GIF(const std::string& filePath)
{
    //Some GIFs may not have either a Global Color Table or a Local Color Table. In this case, the specs
    //suggest using the most previously-loaded Global Color Table. They specs recommend black and white being
    //the first two entries, respectively, in this default Global Color Table.
    globalColorTable.globalColorTableVec.push_back(Color3(0, 0, 0));
    globalColorTable.globalColorTableVec.push_back(Color3(1, 1, 1));
    //TODO: Add other colors for the default color table...

    if (!filePath.empty())
        Load(filePath);
    else
        std::cout << "Error: No file path given." << "\n";

}

/*
* Accessors
*/
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

bool GIF::IsExtensionIntroducer(int num) const
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

void GIF::Draw() const
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int componentColorIndex = y * width + x;
            Color3 pixelColor = Color3(imageArr[componentColorIndex],
                imageArr[componentColorIndex + 1],
                imageArr[componentColorIndex + 2]);
            SetPixel(x, y, pixelColor);
        }
    }
    RefreshScreen();
}

void GIF::DisplayVariables() const
{
    /*
    * Output Header
    */
    std::cout << "Header.Signature: \t\t\t" << header.signature << "\n";
    std::cout << "Header.Version:   \t\t\t" << header.version << "\n";
    std::cout << "\n";

    /*
    * Output Logical Screen Descriptor
    */
    std::cout << "LogicalScreenDescriptor.LogicalScreenWidth:\t\t\t" << logicalScreenDescriptor.logicalScreenWidth << "\n";
    std::cout << "LogicalScreenDescriptor.LogicalScreenHeight:\t\t\t" << logicalScreenDescriptor.logicalScreenHeight << "\n";
    std::cout << "LogicalScreenDescriptor.GlobalColorTableFlag:\t\t\t" << logicalScreenDescriptor.globalColorTableFlag << "\n";
    std::cout << "LogicalScreenDescriptor.ColorResolution:\t\t\t" << logicalScreenDescriptor.colorResolution << "\n";
    std::cout << "LogicalScreenDescriptor.SortFlag:\t\t\t" << logicalScreenDescriptor.sortFlag << "\n";
    std::cout << "LogicalScreenDescriptor.SizeOfGlobalColorTable:\t\t\t" << logicalScreenDescriptor.sizeOfGlobalColorTable << "\n";
    std::cout << "LogicalScreenDescriptor.BackgroundColorIndex:\t\t\t" << logicalScreenDescriptor.backgroundColorIndex << "\n";
    std::cout << "LogicalScreenDescriptor.PixelAspectRatio:\t\t\t" << logicalScreenDescriptor.pixelAspectRatio << "\n";
    std::cout << "\n";

    /*
    * Output Global Color Table
    */
    std::cout << "GlobalColorTable.NumRGBColorsInTable:\t\t\t" << globalColorTable.globalColorTableVec.size() << "\n";
    std::cout << "\n";

    /*
    * Output Image Descriptor
    */
    std::cout << "ImageDescriptor.ImageSeparator:\t\t\t" << imageDescriptor.imageSeparator << "\n";
    std::cout << "ImageDescriptor.ImageLeftPosition:\t\t\t" << imageDescriptor.imageLeftPosition << "\n";
    std::cout << "ImageDescriptor.ImageTopPosition:\t\t\t" << imageDescriptor.imageTopPosition << "\n";
    std::cout << "ImageDescriptor.ImageWidth:\t\t\t" << imageDescriptor.imageWidth << "\n";
    std::cout << "ImageDescriptor.ImageHeight:\t\t\t" << imageDescriptor.imageHeight << "\n";
    std::cout << "ImageDescriptor.LocalColorTableFlag:\t\t\t" << imageDescriptor.localColorTableFlag << "\n";
    std::cout << "ImageDescriptor.InterlaceFlag:\t\t\t" << imageDescriptor.interlaceFlag << "\n";
    std::cout << "ImageDescriptor.SortFlag:\t\t\t" << imageDescriptor.sortFlag << "\n";
    std::cout << "ImageDescriptor.Reserved:\t\t\t" << imageDescriptor.reserved << "\n";
    std::cout << "ImageDescriptor.SizeOfLocalColorTable:\t\t\t" << imageDescriptor.sizeOfLocalColorTable << "\n";
    std::cout << "\n";

    /*
    * Output Local Color Table
    */
    std::cout << "LocalColorTable.NumRGBColorsInTable:\t\t\t" << localColorTable.localColorTableVec.size() << "\n";
    std::cout << "\n";

    /*
    * Output Table Based Image Data
    */
    std::cout << "TableBasedImageData.LZWMinimumCodeSize:\t\t\t" << tableBasedImageData.lzwMinimumCodeSize << "\n";
    //TODO: Output Image Data.
    std::cout << "\n";

    /*
    * Output Graphic Control Extension
    */
    std::cout << "GraphicControlExtension.ExtensionIntroducer:\t\t\t" << graphicControlExtension.extensionIntroducer << "\n";
    std::cout << "GraphicControlExtension.GraphicControlLable:\t\t\t" << graphicControlExtension.graphicControlLabel << "\n";
    std::cout << "GraphicControlExtension.BlcokSize:\t\t\t" << graphicControlExtension.blockSize << "\n";
    std::cout << "GraphicControlExtension.Reserved:\t\t\t" << graphicControlExtension.reserved << "\n";
    std::cout << "GraphicControlExtension.DisposalMethod:\t\t\t" << graphicControlExtension.disposalMethod << "\n";
    std::cout << "GraphicControlExtension.UserInputFlag:\t\t\t" << graphicControlExtension.userInputFlag << "\n";
    std::cout << "GraphicControlExtension.TransparentColorFlag:\t\t\t" << graphicControlExtension.transparentColorFlag << "\n";
    std::cout << "GraphicControlExtension.DelayTime:\t\t\t" << graphicControlExtension.delayTime << "\n";
    std::cout << "GraphicControlExtension.TransparentColorIndex:\t\t\t" << graphicControlExtension.transparentColorIndex << "\n";
    std::cout << "GraphicControlExtension.BlockTerminator:\t\t\t" << graphicControlExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Comment Extension
    */
    std::cout << "CommentExtension.ExtensionIntroducer:\t\t\t" << commentExtension.extensionIntroducer << "\n";
    //TODO: Output Comment Data.
    //Read Block Terminator. Read 1 byte.
    std::cout << "CommentExtension.BlockTerminator:\t\t\t" << commentExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Plain Text Extension.
    */
    std::cout << "PlainTextExtension.ExtensionIntroducer:\t\t\t" << plainTextExtension.extensionIntroducer << "\n";
    std::cout << "PlainTextExtension.PlainTextLabel:\t\t\t" << plainTextExtension.plainTextLabel << "\n";
    std::cout << "PlainTextExtension.BlockSize:\t\t\t" << plainTextExtension.blockSize << "\n";
    std::cout << "PlainTextExtension.TextGridLeftPosition:\t\t\t" << plainTextExtension.textGridLeftPosition << "\n";
    std::cout << "PlainTextExtension.TextGridTopPosition:\t\t\t" << plainTextExtension.textGridTopPosition << "\n";
    std::cout << "PlainTextExtension.TextGridWidth:\t\t\t" << plainTextExtension.textGridWidth << "\n";
    std::cout << "PlainTextExtension.TextGridHeight:\t\t\t" << plainTextExtension.textGridHeight << "\n";
    std::cout << "PlainTextExtension.CharacterCellWidth:\t\t\t" << plainTextExtension.characterCellWidth << "\n";
    std::cout << "PlainTextExtension.CharacterCellHeight:\t\t\t" << plainTextExtension.characterCellHeight << "\n";
    std::cout << "PlainTextExtension.TextForegroundColorIndex:\t\t\t" << plainTextExtension.textForegroundColorIndex << "\n";
    std::cout << "PlainTextExtension.TextBackgroundColorIndex:\t\t\t" << plainTextExtension.textBackgroundColorIndex << "\n";
    std::cout << "PlainTextExtension.PlainTextData:\t\t\t" << plainTextExtension.plainTextData << "\n";
    std::cout << "PlainTextExtension.BlockTerminator:\t\t\t" << plainTextExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Application Extension.
    */
    std::cout << "ApplicationExtension.ExtensionIntroducer:\t\t\t" << applicationExtension.extensionIntroducer << "\n";
    std::cout << "ApplicationExtension.ExtensionLabel:\t\t\t" << applicationExtension.extensionLabel << "\n";
    std::cout << "ApplicationExtension.BlockSize:\t\t\t" << applicationExtension.blockSize << "\n";
    std::cout << "ApplicationExtension.ApplicationIdentifier:\t\t\t" << applicationExtension.applicationIdentifier << "\n";
    std::cout << "ApplicationExtension.ApplicationAthenticationCode:\t\t\t" << applicationExtension.applicationAthenticationCode << "\n";
    std::cout << "ApplicationExtension.ApplicationData:\t\t\t" << applicationExtension.applicationData << "\n";
    std::cout << "ApplicationExtension.BlockTerminator:\t\t\t" << applicationExtension.blockTerminator << "\n";
    std::cout << "\n";

    /*
    * Output Trailer.
    */
    std::cout << "Trailer.GIFTrailer:\t\t\t" << trailer.gifTrailer << "\n";
    std::cout << "\n";
}

void GIF::LoadAndDisplayFileContents(const std::string& filePath) const
{
    //TODO: Display file contents here.
    //Base-10 byte value    Base-16 byte value      Byte value
}

/*
* Mutators
*/
/*
* TODO:
* Add required GIF version to each section.
* Create a DisplayVariables(...) function. For null fields, output the word "null".
*/
//Format taken from https://www.w3.org/Graphics/GIF/spec-gif89a.txt
void GIF::Load(const std::string& filePath)
{
    /*
    * Open the file.
    */
    std::ifstream file;
    file.open(filePath, std::ifstream::in);

    /*
    * Extract the data from the file.
    */
    //Exactly one occurrence.
    header.Read(file);
    
    //This decoder follows the specs of GIF version "89a". If the version of this GIF is "87a", this decoder may
    //have problems.
    //TODO: Make this decoder backwards compatible (be able to decode GIF "87a"s).
    if (GIF::VERSION_87a == header.version)
    {
        std::cout << "\n\n" << "Warning: Can't decode GIFs with version \"87a\" at this time." << "\n\n";
        system("pause");
        exit(0);
    }

    //Exactly one occurrence.
    logicalScreenDescriptor.Read(file);

    //Zero or one occurrences.
    if (1 == logicalScreenDescriptor.globalColorTableFlag)
        globalColorTable.Read(file, logicalScreenDescriptor.sizeOfGlobalColorTable);

    //Zero or more occurrences of an image within the data stream (the GIF file).
    while(IsMatchingLabel(BlockName_ImageDescriptor, PeekNext8Bits(file)))
    {
        //Exactly one occurrence per image.
        imageDescriptor.Read(file);

        //Zero or one occurrence per image.
        if (1 == imageDescriptor.localColorTableFlag)
            localColorTable.Read(file, imageDescriptor.sizeOfLocalColorTable);

        //Exactly one occurrence per image.
        tableBasedImageData.Read(file);
    }

    //Zero or more occurrences.
    while (IsExtensionIntroducer(PeekNext8Bits(file) 
            && IsMatchingLabel(BlockName_GraphicControlExtension, PeekSecondNext8Bits(file))))
        graphicControlExtension.Read(file);

    //Zero or more occurrences.
    while (IsExtensionIntroducer(PeekNext8Bits(file)
            && IsMatchingLabel(BlockName_CommentExtension, PeekSecondNext8Bits(file))))
        commentExtension.Read(file);

    //Zero or more occurrences.
    while (IsExtensionIntroducer(PeekNext8Bits(file)
            && IsMatchingLabel(BlockName_PlainTextExtension, PeekSecondNext8Bits(file))))
        plainTextExtension.Read(file);

    //Zero or more occurrences.
    while (IsExtensionIntroducer(PeekNext8Bits(file)
            && IsMatchingLabel(BlockName_ApplicationExtension, PeekSecondNext8Bits(file))))
        applicationExtension.Read(file);

    //Exactly one occurrence.
    trailer.Read(file);

    /*
    * Close the file.
    */
    file.close();
}

void GIF::Header::Read(std::ifstream& file)
{
    //Read signature. 3 bytes (char). Expects "GIF".
    for (int i = 0; i < 3; i++)
        GetNext8Bits(file, signature[i]);
    if ("GIF" != signature)
        std::cout << "Error: Expected the \"GIF\" signature in the header, but found " << signature << " instead.\n";

    //Read version. 3 bytes (char). Expects "87a" or "89a".
    for (int i = 0; i < 3; i++)
        GetNext8Bits(file, version[i]);
    if ("87a" != version && "89a" != version)
        std::cout << "Error: In the header, expected the version to be either 87a or 89a, but got " << version << " instead.\n";
}

void GIF::LogicalScreenDescriptor::Read(std::ifstream& file)
{
    //Read Logical Screen Width. 1 unsigned int.
    GetNext16Bits(file, logicalScreenWidth);
    //Read Logical Screen Height. 1 unsigned int.
    GetNext16Bits(file, logicalScreenHeight);

    //Read Packed Fields. 1 byte (char).
    GetNext8Bits(file, packedFields);
    //<Packed Fields>  =		Global Color Table Flag       1 bit
    globalColorTableFlag = (packedFields & 0x80) >> 7;
    //							Color Resolution              3 bits
    colorResolution = (packedFields & 0x70) >> 4;
    //							Sort Flag                     1 bit
    sortFlag = (packedFields & 0x08) >> 3;
    //							Size of Global Color Table    3 bits
    sizeOfGlobalColorTable = packedFields & 0x07;

    //Read Background Color Index. 1 byte (char).
    GetNext8Bits(file, backgroundColorIndex);
    //Read Pixel Aspect Ratio. 1 byte (char).
    GetNext8Bits(file, pixelAspectRatio);
}

void GIF::GlobalColorTable::Read(std::ifstream& file, int sizeOfGlobalColorTable)
{
    std::cout << "Global Color Table will be used." << "\n";
    int numBytesToRead = static_cast<int>(3 * pow(2, (sizeOfGlobalColorTable + 1))); //Assumes 8 bits == 1 byte.
    for (int byteIndex = 0; byteIndex < numBytesToRead; byteIndex++)
    {
        if (0 == byteIndex % 3)
            globalColorTableVec.push_back(Color3(0, 0, 0));

        char nextColor;
        GetNext8Bits(file, nextColor);
        switch (byteIndex % 3)
        {
        case 0: globalColorTableVec[byteIndex / 3].SetRed(static_cast<unsigned char>(nextColor)); break;
        case 1: globalColorTableVec[byteIndex / 3].SetGreen(static_cast<unsigned char>(nextColor)); break;
        case 2: globalColorTableVec[byteIndex / 3].SetBlue(static_cast<unsigned char>(nextColor)); break;
        default: break;
        }
    }
}

void GIF::ImageDescriptor::Read(std::ifstream& file)
{
    //Read Image Separator. 1 byte (char).
    GetNext8Bits(file, imageSeparator);

    //Read Image Left Position. 1 unsigned int.
    GetNext16Bits(file, imageLeftPosition);
    //Read Image Top Position. 1 unsigned int.
    GetNext16Bits(file, imageTopPosition);
    //Read Image Width. 1 unsigned int.
    GetNext16Bits(file, imageWidth);
    //Read Image Height. 1 unsigned int.
    GetNext16Bits(file, imageHeight);

    //Read Packed Fields. 1 byte (char).
    GetNext8Bits(file, packedFields);
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
}

void GIF::LocalColorTable::Read(std::ifstream& file, int sizeOfLocalColorTable)
{
    std::cout << "Local Color Table will be used." << "\n";
    int numBytesToRead = static_cast<int>(3 * pow(2, (sizeOfLocalColorTable + 1))); //Assumes 8 bits == 1 byte.
    for (int byteIndex = 0; byteIndex < numBytesToRead; byteIndex++)
    {
        if (0 == byteIndex % 3)
            localColorTableVec.push_back(Color3(0, 0, 0));

        char nextColor;
        GetNext8Bits(file, nextColor);
        switch (byteIndex % 3)
        {
        case 0: localColorTableVec[byteIndex / 3].SetRed(static_cast<unsigned char>(nextColor)); break;
        case 1: localColorTableVec[byteIndex / 3].SetGreen(static_cast<unsigned char>(nextColor)); break;
        case 2: localColorTableVec[byteIndex / 3].SetBlue(static_cast<unsigned char>(nextColor)); break;
        default: break;
        }
    }
}

void GIF::TableBasedImageData::Read(std::ifstream& file)
{
    //Read LZW Minimum Code Size. 1 byte (char).
    GetNext8Bits(file, lzwMinimumCodeSize);

    //TODO: Read Image Data.
}

void GIF::GraphicControlExtension::Read(std::ifstream& file)
{
    //Read Extension Introducer. 1 byte (char).
    GetNext8Bits(file, extensionIntroducer);
    //Read Graphic Control Label. 1 byte (char).
    GetNext8Bits(file, graphicControlLabel);

    //Read Block Size. 1 byte.
    GetNext8Bits(file, blockSize);
    //Read Packed Fields.
    GetNext8Bits(file, packedFields);
    //<Packed Fields> =			Reserved                      3 Bits
    reserved = (packedFields & 0xE0) >> 5;
    //							Disposal Method               3 Bits
    disposalMethod = (packedFields & 0x1C) >> 2;
    //							User Input Flag               1 Bit
    userInputFlag = (packedFields & 0x02) >> 1;
    //							Transparent Color Flag        1 Bit
    transparentColorFlag = (packedFields & 0x01);

    //Read Delay Time. 1 unsigned int.
    GetNext16Bits(file, delayTime);
    //Read Transparent Color Index. 1 byte.
    GetNext8Bits(file, transparentColorIndex);
    //Read Block Terminator. 1 byte.
    GetNext8Bits(file, blockTerminator);
}

void GIF::CommentExtension::Read(std::ifstream& file)
{
    //Read Extension Introducer. Read 1 byte.
    GetNext8Bits(file, extensionIntroducer);

    //TODO: Read Comment Data.

    //Read Block Terminator. Read 1 byte.
    GetNext8Bits(file, blockTerminator);
}

void GIF::PlainTextExtension::Read(std::ifstream& file)
{
    //Read Extension Introducer. 1 byte.
    GetNext8Bits(file, extensionIntroducer);
    //Read Plain Text Label. 1 byte.
    GetNext8Bits(file, plainTextLabel);
    //Read Block Size. 1 byte.
    GetNext8Bits(file, blockSize);

    //Read Text Grid Left Position. 1 unsigned int.
    GetNext16Bits(file, textGridLeftPosition);
    //Read Text Grid Top Position. 1 unsigned int.
    GetNext16Bits(file, textGridTopPosition);
    //Read Text Grid Width. 1 unsigned int.
    GetNext16Bits(file, textGridWidth);
    //Read Text Grid Height. 1 unsigned int.
    GetNext16Bits(file, textGridHeight);

    //Read Character Cell Width. 1 byte.
    GetNext8Bits(file, characterCellWidth);
    //Read Character Cell Height. 1 byte.
    GetNext8Bits(file, characterCellHeight);

    //Read Text Foreground Color Index. 1 byte.
    GetNext8Bits(file, textForegroundColorIndex);
    //Read Text Background Color Index. 1 byte.
    GetNext8Bits(file, textBackgroundColorIndex);

    //TODO: Read Plain Text Data.

    //Read Block Terminator. 1 byte.
    GetNext8Bits(file, blockTerminator);
}

void GIF::ApplicationExtension::Read(std::ifstream& file)
{
    //Read Extension Introducer. 1 byte.
    GetNext8Bits(file, extensionIntroducer);
    //Read Extension Label. 1 byte.
    GetNext8Bits(file, extensionLabel);
    //Read Block Size. 1 byte.
    GetNext8Bits(file, blockSize);

    //Read Application Identifier. 8 bytes.
    applicationIdentifier = 0L;
    for (int byteIndex = 0; byteIndex < 8; byteIndex++) //Assumes 1 byte == 8 bits
    {
        char next8Bits;
        GetNext8Bits(file, next8Bits);
        applicationIdentifier << 8;
        applicationIdentifier = applicationIdentifier | next8Bits;
    }
    //Read ApplicationAthentication Code. 3 bytes.
    applicationAthenticationCode = 0L;
    for (int byteIndex = 0; byteIndex < 3; byteIndex++) //Assumes 1 byte == 8 bits
    {
        char next8Bits;
        GetNext8Bits(file, next8Bits);
        applicationAthenticationCode << 8;
        applicationAthenticationCode = applicationAthenticationCode | next8Bits;
    }

    //TODO: Read Application Data.

    //Read Block Terminator. 1 byte.
    GetNext8Bits(file, blockTerminator);
}

void GIF::Trailer::Read(std::ifstream& file)
{
    //Read GIF Trailer. 1 byte.
    GetNext8Bits(file, gifTrailer);
}
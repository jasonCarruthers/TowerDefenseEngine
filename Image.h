#ifndef IMAGE_HFILE
#define IMAGE_HFILE

#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "../../PrimitiveTypedefs.h"
#include "../2DGraphics/Color.h"





/*
* Global function prototypes.
*/
char BaseTenDigitToASCII(int num);
std::string IntToStringBinary(int num);
int StringBinaryToInt(const std::string& stringBinary);




class Image
{
public:
	/*Constructors*/
	Image();

	/*Accessors*/
    public: virtual int GetWidth() const = 0;
    public: virtual int GetHeight() const = 0;
    //DEPRECATED: static byte PeekNextByte(std::ifstream& file, bool isSigned);
    //DEPRECATED: static byte PeekSecondToNextByte(std::ifstream& file, bool isSigned); //Gets the 8 bits after the next 8 bits.
	//DEPRECATED: static void GetNextByte(std::ifstream& file, char& nextChar, bool isSigned);
    //DEPRECATED: static byte GetNextByte(std::ifstream& file, bool isSigned);
    static byte GetNextByte(std::ifstream& file);
    //DEPRECATED: static void GetNextTwoBytes(std::ifstream& file, unsigned int& nextUnsignedInt, bool isSigned);
    //DEPRECATED: static twoBytes GetNextTwoBytes(std::ifstream& file, bool isSigned);
    //DEPRECATED: static twoBytes GetNextTwoBytesInLittleEndian(std::ifstream& file, bool isSigned);
    static twoBytes GetTwoBytesAsLittleEndian(byte firstByte, byte secondByte);
    static twoBytes GetTwoBytesAsBigEndian(byte firstByte, byte secondByte);

	/*Mutators*/
	//void LoadPPM(const std::string& filePath);
	//void LoadBMP(const std::string& filePath);
	//void LoadJPEG(const std::string& filePath);
	//void LoadPNG(const std::string& filePath);

protected:
	float* imageArr;
};


class GIF : public Image
{
public:
    enum BlockName
    {
        BlockName_Header,
        BlockName_LogicalScreenDescriptor,
        BlockName_GlobalColorTable,
        BlockName_ImageDescriptor,
        BlockName_LocalColorTable,
        //BlockName_TableBasedImageData, //Considered a sub-block, not a block, by the GIF specs.
        BlockName_GraphicControlExtension,
        BlockName_CommentExtension,
        BlockName_PlainTextExtension,
        BlockName_ApplicationExtension,
        BlockName_Trailer,
    };

    enum ExtensionName
    {
        ExtensionName_GraphicControlExtension,
        ExtensionName_CommentExtension,
        ExtensionName_PlainTextExtension,
        ExtensionName_ApplicationExtension,
    };
public:
    /*Static constants*/
    static const std::vector<Color3> DEFAULT_COLOR_TABLE; //To be used if no global or local color table is provided by the file.

    static const byte EXTENSION_INTRODUCER;

    static const byte IMAGE_DESCRIPTOR_LABEL;
    static const byte GRAPHIC_CONTROL_EXTENSION_LABEL;
    static const byte COMMENT_EXTENSION_LABEL;
    static const byte PLAIN_TEXT_EXTENSION_LABEL;
    static const byte APPLICATION_EXTENSION_LABEL;
    static const byte TRAILER_LABEL;

    static const std::string VERSION_87a;
    static const std::string VERSION_89a;

    static const std::string LOGICAL_SCREEN_DESCRIPTOR_REQUIRED_VERSION;
    static const std::string GLOBAL_COLOR_TABLE_REQUIRED_VERSION;
    static const std::string IMAGE_DESCRIPTOR_REQUIRED_VERSION;
    static const std::string LOCAL_COLOR_TABLE_REQUIRED_VERSION;
    static const std::string GRAPHIC_CONTROL_EXTENSION_REQUIRED_VERSION;
    static const std::string COMMENT_EXTENSION_REQUIRED_VERSION;
    static const std::string PLAIN_TEXT_EXTENSION_REQUIRED_VERSION;
    static const std::string APPLICATION_EXTENSION_REQUIRED_VERSION;
    static const std::string TRAILER_REQUIRED_VERSION;

	/*Constructors*/
	GIF(const std::string& filePath);

	/*Accessors*/
    int GetWidth() const;
    int GetHeight() const;
    static std::vector<byte> ReadBytesFromGIFFile(const std::string& filePath);
    std::string GetBlockNameRequiredVersion(BlockName blockName) const;
    bool IsVersionCompatible(BlockName blockName, const std::string version) const;
    BlockName GetBlockNameFromExtensionName(ExtensionName extensionName);
    bool IsSpecificExtension(ExtensionName extensionName, int byteVecIndex);
    bool IsExtensionIntroducer(byte num) const;
    bool IsMatchingLabel(BlockName blockName, int label) const;
	void Draw() const;
	void DisplayVariables() const;
	//FOR TESTING: void LoadAndDisplayFileContents(const std::string& filePath) const;
    std::vector<Color3> GetActiveColorTable();

	/*Mutators*/
	void Load(const std::string& filePath);
    void ReadGrammarGIFDataStream(); //Always start reading the stream at the beginning, so no offset needed.
    int ReadGrammarLogicalScreen(int byteVecIndex);
    int ReadGrammarData(int byteVecIndex);
    int ReadGrammarGraphicBlock(int byteVecIndex);
    int ReadGrammarGraphicRenderingBlock(int byteVecIndex);
    int ReadGrammarTableBasedImage(int byteVecIndex);
    int ReadGrammarSpecialPurposeBlock(int byteVecIndex);
    int ReadExtension(int byteVecIndex);
    bool IsNextGrammarSpecialPurposeBlock(int byteVecIndex); 
	//void ReadHeader();
	//void ReadLogicalScreenDescriptor();
	//void ReadGlobalColorTable();
	//void ReadImageDescriptor();
	//void ReadLocalColorTable();
	//void ReadTableBasedImageData();
	//void ReadGraphicControlExtension();
	//void ReadCommentExtension();
	//void ReadPlainTextExtension();
	//void ReadApplicationExtension();
	//void ReadTrailer();
	
public:
	class Header
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
		std::string signature;
		std::string version;
	};
	class LogicalScreenDescriptor
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
        twoBytes logicalScreenWidth;
        twoBytes logicalScreenHeight;
		byte packedFields;
        byte globalColorTableFlag;
        byte colorResolution;
        byte sortFlag;
        byte sizeOfGlobalColorTable;
        byte backgroundColorIndex;
        byte pixelAspectRatio;
	};
	class GlobalColorTable
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex, int sizeOfGlobalColorTable);
		std::vector<Color3> globalColorTableVec;
	};
	class ImageDescriptor
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
        byte imageSeparator;
		twoBytes imageLeftPosition;
        twoBytes imageTopPosition;
        twoBytes imageWidth;
        twoBytes imageHeight;
		byte packedFields;
        byte localColorTableFlag;
        byte interlaceFlag;
        byte sortFlag;
        byte reserved; //Reserved fields are always zero.
        byte sizeOfLocalColorTable;
	};
	class LocalColorTable
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex, int sizeOfLocalColorTable);
		std::vector<Color3> localColorTableVec;
	};
	class TableBasedImageData
	{
    public:
        class Frame
        {
        public:
            Frame(unsigned int offsetX, unsigned int offsetY, unsigned int width, unsigned int height);
        public:
            unsigned int offsetX; //Relative to left of screen. Positive x moves to the right.
            unsigned int offsetY; //Relative to top of screen. Positive y moves down.
            unsigned int width;
            unsigned int height;
            std::vector<Color3> pixelColorVec; //The size of this vec should be equal to width * height.
        };

        //Bypasses the bytes associated with the table based image data section, so that I can avoid the lzw complexity
        //for now and test whether the other GIF fields are being read properly.
        public: int Bypass(std::vector<byte>& byteVec, int byteVecIndex);
        public: int Read(std::vector<byte>& byteVec, int byteVecIndex, 
                         unsigned int imageLeftPosition, unsigned int imageTopPosition,
                         unsigned int imageWidth, unsigned int imageHeight, std::vector<Color3> activeColorTable);
        private: void InitCodeTable(std::vector<std::vector<int>>& codeTable, const std::vector<Color3>& activeColorTable);
        /*private: int ReadFrames(std::vector<Frame>& frameVec, int imageLeftPosition, int imageTopPosition, int imageWidth, 
                                int imageHeight, const std::vector<byte>& byteVec, int byteVecIndex,
                                const std::vector<Color3>& activeColorTable, std::vector<std::vector<int>>& codeTable,
                                int numBitsEncodingClearCode, int clearCode, int endOfInformation);*/
        private: int ReadFrame(Frame& newFrame, const std::vector<byte>& byteVec, int byteVecIndex,
                               const std::vector<Color3>& activeColorTable, std::vector<std::vector<int>>& codeTable,
                               int numBitsEncodingClearCode, int clearCode, int endOfInformation);
        private: std::vector<Color3> GetListOfColorsFromCodeTableAtIndex(const std::vector<std::vector<int>>& codeTable,
                                                                         int index,
                                                                         const std::vector<Color3>& activeColorTable);
        private: int GetFirstTerminalCode(const std::vector<std::vector<int>>& codeTable, int index);
        public: byte lzwMinimumCodeSize;
        public: std::vector<Frame> imageData;
	};
	class GraphicControlExtension
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
		byte extensionIntroducer;
		byte graphicControlLabel;
        byte blockSize;
        byte packedFields;
        byte reserved; //Reserved fields are always zero.
		byte disposalMethod;
		byte userInputFlag;
		byte transparentColorFlag;
		twoBytes delayTime;
		byte transparentColorIndex;
		byte blockTerminator;
	};
	class CommentExtension
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
        byte extensionIntroducer;
		std::string commentData; //The first byte is how many bytes of comment data there is,
                                 //excluding that first byte and the block terminator byte.
        byte blockTerminator;
	};
	class PlainTextExtension
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
        byte extensionIntroducer;
        byte plainTextLabel;
        byte blockSize;
		twoBytes textGridLeftPosition;
		twoBytes textGridTopPosition;
        twoBytes textGridWidth;
        twoBytes textGridHeight;
        byte characterCellWidth;
        byte characterCellHeight;
        byte textForegroundColorIndex;
        byte textBackgroundColorIndex;
		std::string plainTextData;  //The first byte is how many bytes of plain text data there is,
                                    //excluding that first byte and the block terminator byte.
        byte blockTerminator;
	};
	class ApplicationExtension
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
        byte extensionIntroducer;
        byte extensionLabel;
        byte blockSize;
		long long applicationIdentifier; //8 bytes
		long applicationAthenticationCode; //3 bytes
        std::string applicationData; //The first byte is how many bytes of application data there is,
                                     //excluding that first byte and the block terminator byte.
        byte blockTerminator;
	};
	class Trailer
	{
	public:
        int Read(std::vector<byte>& byteVec, int byteVecIndex);
        byte gifTrailer;
	};
private:
    std::vector<byte> byteVec;
	Header header;
	LogicalScreenDescriptor logicalScreenDescriptor;
	GlobalColorTable globalColorTable;
	ImageDescriptor imageDescriptor;
	LocalColorTable localColorTable;
	TableBasedImageData tableBasedImageData;
	GraphicControlExtension graphicControlExtension;
	CommentExtension commentExtension;
	PlainTextExtension plainTextExtension;
	ApplicationExtension applicationExtension;
	Trailer trailer;
};




#endif /*IMAGE_HFILE*/
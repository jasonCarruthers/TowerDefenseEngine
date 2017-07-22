#ifndef IMAGE_HFILE
#define IMAGE_HFILE

#include <fstream>
#include <string>
#include "../2DGraphics/Color.h"

class Image
{
public:
	/*Constructors*/
	Image();

	/*Accessors*/
    static char PeekNext8Bits(std::ifstream& file);
    static char PeekSecondNext8Bits(std::ifstream& file); //Gets the 8 bits after the next 8 bits.
	static void GetNext8Bits(std::ifstream& file, char& nextChar);
	static void GetNext16Bits(std::ifstream& file, unsigned int& nextUnsignedInt);

	/*Mutators*/
	//void LoadPPM(const std::string& filePath);
	//void LoadBMP(const std::string& filePath);
	//void LoadJPEG(const std::string& filePath);
	//void LoadPNG(const std::string& filePath);

protected:
	float* imageArr;
	int width;
	int height;
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
        //BlockName_TableBasedImageData, //Not considered a block by the GIF specs.
        BlockName_GraphicControlExtension,
        BlockName_CommentExtension,
        BlockName_PlainTextExtension,
        BlockName_ApplicationExtension,
        BlockName_Trailer,
    };
public:
    /*Static constants*/
    static const int EXTENSION_INTRODUCER;

    static const int IMAGE_DESCRIPTOR_LABEL;
    static const int GRAPHIC_CONTROL_EXTENSION_LABEL;
    static const int COMMENT_EXTENSION_LABEL;
    static const int PLAIN_TEXT_EXTENSION_LABEL;
    static const int APPLICATION_EXTENSION_LABEL;
    static const int TRAILER_LABEL;

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
	GIF(const std::string& filePath = "");

	/*Accessors*/
    std::string GetBlockNameRequiredVersion(BlockName blockName) const;
    bool IsVersionCompatible(BlockName blockName, const std::string version) const;
    bool IsExtensionIntroducer(int num) const;
    bool IsMatchingLabel(BlockName blockName, int label) const;
	void Draw() const;
	void DisplayVariables() const;
	void LoadAndDisplayFileContents(const std::string& filePath) const;

	/*Mutators*/
	void Load(const std::string& filePath);
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
	
private:
	class Header
	{
	public:
		void Read(std::ifstream& file);
		std::string signature;
		std::string version;
	};
	class LogicalScreenDescriptor
	{
	public:
		void Read(std::ifstream& file);
		unsigned int logicalScreenWidth;
		unsigned int logicalScreenHeight;
		char packedFields;
		bool globalColorTableFlag;
		int colorResolution;
		bool sortFlag;
		int sizeOfGlobalColorTable;
		char backgroundColorIndex;
		char pixelAspectRatio;
	};
	class GlobalColorTable
	{
	public:
		void Read(std::ifstream& file, int sizeOfGlobalColorTable);
		std::vector<Color3> globalColorTableVec;
	};
	class ImageDescriptor
	{
	public:
		void Read(std::ifstream& file);
		char imageSeparator;
		unsigned int imageLeftPosition;
		unsigned int imageTopPosition;
		unsigned int imageWidth;
		unsigned int imageHeight;
		char packedFields;
		bool localColorTableFlag;
		bool interlaceFlag;
		bool sortFlag;
		int reserved; //Reserved fields are always zero.
		int sizeOfLocalColorTable;
	};
	class LocalColorTable
	{
	public:
		void Read(std::ifstream& file, int sizeOfLocalColorTable);
		std::vector<Color3> localColorTableVec;
	};
	class TableBasedImageData
	{
	public:
		void Read(std::ifstream& file);
		char lzwMinimumCodeSize;
		imageData;
	};
	class GraphicControlExtension
	{
	public:
		void Read(std::ifstream& file);
		char extensionIntroducer;
		char graphicControlLabel;
		char blockSize;
		char packedFields;
		int reserved; //Reserved fields are always zero.
		int disposalMethod;
		bool userInputFlag;
		bool transparentColorFlag;
		unsigned int delayTime;
		char transparentColorIndex;
		char blockTerminator;
	};
	class CommentExtension
	{
	public:
		void Read(std::ifstream& file);
		char extensionIntroducer;
		commentData
		char blockTerminator;
	};
	class PlainTextExtension
	{
	public:
		void Read(std::ifstream& file);
		char extensionIntroducer;
		char plainTextLabel;
		char blockSize;
		unsigned int textGridLeftPosition;
		unsigned int textGridTopPosition;
		unsigned int textGridWidth;
		unsigned int textGridHeight;
		char characterCellWidth;
		char characterCellHeight;
		char textForegroundColorIndex;
		char textBackgroundColorIndex;
		plainTextData;
		char blockTerminator;
	};
	class ApplicationExtension
	{
	public:
		void Read(std::ifstream& file);
		char extensionIntroducer;
		char extensionLabel;
		char blockSize;
		long long applicationIdentifier;
		long applicationAthenticationCode;
		applicationData;
		char blockTerminator;
	};
	class Trailer
	{
	public:
		void Read(std::ifstream& file);
		char gifTrailer;
	};
private:
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
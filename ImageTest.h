#ifndef HFILE_IMAGE_TEST
#define HFILE_IMAGE_TEST


/*
* Global function prototyes
*/
void CreateTestGIF_2x1White();
void WriteTestGIFToFile(const std::string& fileContents);
std::ifstream OpenTestFile();
//void RunUnitTests();
void TestReadingHeader();
void TestReadingLogicalScreenDescriptor();
void TestReadingGlobalColorTable();
void TestReadingImageDescriptor();
void TestReadingTableBasedImageData();
void TestReadingTrailer();


/*
* Global variables
*/
extern const std::string FILE_PATH;


#endif /*HFILE_IMAGE_TEST*/
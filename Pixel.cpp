#include "../../include/2DGraphics/Color.h"
#include "../../include/Window/Utilities.h"
#include "../../include/Window/Pixel.h"


/*
* Global variable2s
*
* NOTE: const global variables declared with extern in a .h file need to be set in a single .cpp
*		 file, but will still be visible to other .cpp files. If a global variable declared const
*		 has the extern keyword modifier, it can't be intialized in the .h file.
*
* NOTE: It appears any global variables declared with extern in a .h file need to be set in a single .cpp
*		 file, but will still be visible to other .cpp files. If any global variable
*		 has the extern keyword modifier, it can't be intialized in the .h file and must be
*		 declared in a single .cpp file.
*/
float *pixelBuffer;


void SetPixel(int x, int y, const Color3 &color)
{
	if (x < 0 || x >= (int)WINDOW_WIDTH || y < 0 || y >= (int)WINDOW_HEIGHT)
	{
		//Error handling
	}

	int offset = x * 3 + y * WINDOW_WIDTH * 3;
	pixelBuffer[offset + 0] = color.GetRed();
	pixelBuffer[offset + 1] = color.GetGreen();
	pixelBuffer[offset + 2] = color.GetBlue();
}


void RefreshScreen()
{
	delete[] pixelBuffer;
	pixelBuffer = new float[WINDOW_WIDTH * WINDOW_HEIGHT * 3];
}


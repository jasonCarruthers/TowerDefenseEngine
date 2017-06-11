#include "../../include/Window/Utilities.h"



/*
* Global variables
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
const unsigned int WINDOW_WIDTH = 1200;
const unsigned int WINDOW_HEIGHT = 600;
const unsigned int MAGIC_GARBAGE = -999;
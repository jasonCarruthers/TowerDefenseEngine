#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "../include/Utilities/MyMath.h"
#include "../include/2DGraphics/Line.h"
#include "../include/Main.h"
#include "../include/General.h"





/*
 * Global functions
 */

unsigned int StringToUInt(const std::string &str)
{
	unsigned int retVal = 0;
	unsigned int weight = 0;

	for (unsigned int i = str.size() - 1; i >= 0; i--)
	{
		retVal += ((int)str[i] - 48) * weight;
		weight += 10;
	}

	return retVal;
}

std::string UIntToString(unsigned int num)
{
	std::string retVal = "";

	do
	{
		retVal.insert(retVal.begin(), (char)((num % 10) + 48));
		num /= 10;
	} while (num > 0);

	return retVal;
}

std::string FloatToString(float num)
{
	std::string retVal = "";

	/*If the float is negative, insert a negative sign into the string retVal. Then
	  make the float positive for the rest of the calculations*/
	if (num < 0)
	{
		retVal = "-";
		num *= -1;
	}

	/*Insert the portion of the float > 0 into the string retVal*/
	unsigned int numAsUInt = (unsigned int)num;
	retVal += UIntToString(numAsUInt);

	/*Remove the portion of the float > 0, leaving only the decimal.
	  Also, insert a decimal point into the string retVal*/
	num -= numAsUInt;
	retVal += ".";

	/*Insert the decimal portion of the float into the string retVal, with a max
	  of 2 decimal places*/
	unsigned int count = 0;
	do
	{
		num *= 10;
		retVal += (char)((int)num + 48);
		num -= (int)num;

		count++;
	} while (count < 2 && num != 0);

	return retVal;
}


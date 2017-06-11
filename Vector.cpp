#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "../../include/Utilities/Vector.h"




/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Vector4F
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructor(s)
*/
Vector4F::Vector4F(float newX, float newY, float newZ, float newW)
{
	mArr[Vector4F::X] = newX;
	mArr[Vector4F::Y] = newY;
	mArr[Vector4F::Z] = newZ;
	mArr[Vector4F::W] = newW;
}

/*
* Accessors
*/
float Vector4F::GetX() const
{
	return mArr[Vector4F::X];
}

float Vector4F::GetY() const
{
	return mArr[Vector4F::Y];
}

float Vector4F::GetZ() const
{
	return mArr[Vector4F::Z];
}

float Vector4F::GetW() const
{
	return mArr[Vector4F::W];
}


/*
* Mutators
*/
void Vector4F::Set(const Vector4F &newCoord)
{
	mArr[Vector4F::X] = newCoord.mArr[Vector4F::X];
	mArr[Vector4F::Y] = newCoord.mArr[Vector4F::Y];
	mArr[Vector4F::Z] = newCoord.mArr[Vector4F::Z];
	mArr[Vector4F::W] = newCoord.mArr[Vector4F::W];
}

void Vector4F::Set(float newX, float newY, float newZ, float newW)
{
	mArr[Vector4F::X] = newX;
	mArr[Vector4F::Y] = newY;
	mArr[Vector4F::Z] = newZ;
	mArr[Vector4F::W] = newW;
}

void Vector4F::SetX(float newX)
{
	mArr[Vector4F::X] = newX;
}

void Vector4F::SetY(float newY)
{
	mArr[Vector4F::Y] = newY;
}

void Vector4F::SetZ(float newZ)
{
	mArr[Vector4F::Z] = newZ;
}

void Vector4F::SetW(float newW)
{
	mArr[Vector4F::W] = newW;
}


/*
* Overloaded operators
*/
float &Vector4F::operator[](int index)
{
	if (index < 0 || index >= (int)Num__Elements)
		return mArr[X]; /*If index is out of bounds, return the first element by default.*/
	return mArr[index];
}
const float &Vector4F::operator[](int index) const
{
	if (index < 0 || index >= (int)Num__Elements)
		return mArr[X]; /*If index is out of bounds, return the first element by default.*/
	return mArr[index];
}

bool operator==(const Vector4F &coord1, const Vector4F &coord2)
{
	return (coord1.GetX() == coord2.GetX() &&
		coord1.GetY() == coord2.GetY() &&
		coord1.GetZ() == coord2.GetZ() &&
		coord1.GetW() == coord2.GetW());
}

Vector4F operator*(const Vector4F &left, const Vector4F &right)
{
	return Vector4F(left[Vector4F::X] * right[Vector4F::X],
		left[Vector4F::Y] * right[Vector4F::Y],
		left[Vector4F::Z] * right[Vector4F::Z],
		left[Vector4F::W] * right[Vector4F::W]);
}

Vector4F operator*(const Vector4F &left, float multiplier)
{
	return Vector4F(left[Vector4F::X] * multiplier,
		left[Vector4F::Y] * multiplier,
		left[Vector4F::Z] * multiplier,
		left[Vector4F::W] * multiplier);
}

Vector4F operator*(float multiplier, const Vector4F &right)
{
	return Vector4F(right[Vector4F::X] * multiplier,
		right[Vector4F::Y] * multiplier,
		right[Vector4F::Z] * multiplier,
		right[Vector4F::W] * multiplier);
}

Vector4F operator+(const Vector4F &left, const Vector4F &right)
{
	return Vector4F(left[Vector4F::X] + right[Vector4F::X],
		left[Vector4F::Y] + right[Vector4F::Y],
		left[Vector4F::Z] + right[Vector4F::Z],
		left[Vector4F::W] + right[Vector4F::W]);
}

Vector4F operator+(const Vector4F &left, float deltaSum)
{
	return Vector4F(left[Vector4F::X] + deltaSum,
		left[Vector4F::Y] + deltaSum,
		left[Vector4F::Z] + deltaSum,
		left[Vector4F::W] + deltaSum);
}

void operator+=(Vector4F &left, const Vector4F &right)
{
	left = left + right;
}

void operator+=(Vector4F &left, float deltaSum)
{
	left = left + deltaSum;
}

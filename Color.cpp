#include <iostream>
#include "../../include/Utilities/Logger.h"
#include "../../include/Utilities/MyMath.h"
#include "../../include/2DGraphics/Color.h"


/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Color3
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructors
*/
Color3::Color3(float red, float green, float blue)
{
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
}


/*
* Accessors
*/
float Color3::GetRed() const
{
	return mRed;
}
float Color3::GetGreen() const
{
	return mGreen;
}
float Color3::GetBlue() const
{
	return mBlue;
}


/*
* Mutators
*/
void Color3::Set(const Color3& color)
{
	SetRed(color.GetRed());
	SetGreen(color.GetGreen());
	SetBlue(color.GetBlue());
}
void Color3::Set(float newRed, float newGreen, float newBlue)
{
	SetRed(newRed);
	SetGreen(newGreen);
	SetBlue(newBlue);
}
void Color3::SetRed(float newRed)
{
	newRed = (newRed < 0.0f) ? 0.0f : newRed;
	newRed = (newRed > 1.0f) ? 1.0f : newRed;
	mRed = newRed;
}
void Color3::SetGreen(float newGreen)
{
	newGreen = (newGreen < 0.0f) ? 0.0f : newGreen;
	newGreen = (newGreen > 1.0f) ? 1.0f : newGreen;
	mGreen = newGreen;
}
void Color3::SetBlue(float newBlue)
{
	newBlue = (newBlue < 0.0f) ? 0.0f : newBlue;
	newBlue = (newBlue > 1.0f) ? 1.0f : newBlue;
	mBlue = newBlue;
}


/*
* Overloaded operators
*/
void Color3::operator=(const Color3& right)
{
	Set(right.GetRed(), right.GetGreen(), right.GetBlue());
}

bool operator==(const Color3 &left, const Color3 &right)
{
	return (	left.GetRed() == right.GetRed() &&
				left.GetGreen() == right.GetGreen() &&
				left.GetBlue() == right.GetBlue()	);
}
bool operator!= (const Color3 &left, const Color3 &right)
{
	return !(left == right);
}
Color3 operator*(const Color3 &left, const Color3 &right)
{
	Color3 *ret = new Color3();
	ret->SetRed(left.GetRed() * right.GetRed());
	ret->SetGreen(left.GetGreen() * right.GetGreen());
	ret->SetBlue(left.GetBlue() * right.GetBlue());
	return *ret;
}
Color3 operator*(const Color3 &left, float multiplier)
{
	Color3 *ret = new Color3();
	ret->SetRed(left.GetRed() * multiplier);
	ret->SetGreen(left.GetGreen() * multiplier);
	ret->SetBlue(left.GetBlue() * multiplier);
	return *ret;
}
Color3 operator*(float multiplier, const Color3 &right)
{
	return right * multiplier;
}
Color3 operator/(const Color3 &left, float divisor)
{
	if (IsEffectivelyZero(divisor))
	{
		Logger::GetInstance().Log("Divide by zero.");
		abort();
	}

	Color3 *ret = new Color3();
	ret->SetRed(left.GetRed() / divisor);
	ret->SetGreen(left.GetGreen() / divisor);
	ret->SetBlue(left.GetBlue() / divisor);
	return *ret;
}
Color3 operator/(float divisor, const Color3 &right)
{
	return right / divisor;
}
Color3 operator+(const Color3 &left, const Color3 &right)
{
	Color3 *ret = new Color3();
	ret->SetRed(left.GetRed() + right.GetRed());
	ret->SetGreen(left.GetGreen() + right.GetGreen());
	ret->SetBlue(left.GetBlue() + right.GetBlue());
	return *ret;
}
void operator+=(Color3 &left, const Color3 &right)
{
	left = left + right;
}





/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Color3
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructors
*/
Color4::Color4(float red, float green, float blue, float alpha) : Color3(red, green, blue)
{
	SetAlpha(alpha);
}

/*
* Accessors
*/
float Color4::GetAlpha() const
{
	return mAlpha;
}
Color3 Color4::GetColor3() const
{
	return Color3(GetRed(), GetGreen(), GetBlue());
}

/*
* Mutators
*/
void Color4::Set(const Color4 &color)
{
	Set(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}
void Color4::Set(float newRed, float newGreen, float newBlue, float newAlpha)
{
	Color3::Set(newRed, newGreen, newBlue);
	SetAlpha(newAlpha);
}
void Color4::SetAlpha(float newAlpha)
{
	newAlpha = (newAlpha < 0.0f) ? 0.0f : newAlpha;
	newAlpha = (newAlpha > 1.0f) ? 1.0f : newAlpha;
	mAlpha = newAlpha;
}




Color4 GetRandomColor()
{
	float r = (rand() % 256) / 255.0f;
	float g = (rand() % 256) / 255.0f;
	float b = (rand() % 256) / 255.0f;
	float a = (rand() % 256) / 255.0f;
	return Color4(r, g, b, a);
}


/*Returns a non-yellow, non-dark color.*/
Color4 GetRandomBrightColor()
{
	Color4 retColor;
	do
	{
		retColor = GetRandomColor();
	} while ((retColor.GetRed() >= 0.8f && retColor.GetGreen() >= 0.8f) ||
		(retColor.GetRed() <= 0.5f && retColor.GetGreen() <= 0.5f && retColor.GetBlue() <= 0.5f));

	return retColor;
}

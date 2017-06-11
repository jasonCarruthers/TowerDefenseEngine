#include <iostream>
#include <vector>
#include "../../include/General.h"
#include "../../include/Utilities/Vector.h"
#include "../../include/2DGraphics/Color.h"
#include "../../include/Utilities/MyMath.h"
#include "../../include/Window/Utilities.h"
#include "../../include/2DGraphics/Line.h"



/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Ray
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructor(s)
*/
Ray3D::Ray3D(const Vector3F &newOrigin, const Vector3F &newDirection)
{
	mOrigin.Set(newOrigin);
	mDirection.Set(newDirection);
}

/*
* Accessors
*/
Vector3F Ray3D::GetOrigin() const
{
	return mOrigin;
}

Vector3F Ray3D::GetDirection() const
{
	return mDirection;
}

/*
* Mutators
*/
void Ray3D::SetOrigin(const Vector3F &newOrigin)
{
	mOrigin.Set(newOrigin);
}

void Ray3D::SetDirection(const Vector3F &newDirection)
{
	mDirection.Set(newDirection);
}

void Ray3D::NormalizeDirection()
{
	mDirection.Normalize();
}
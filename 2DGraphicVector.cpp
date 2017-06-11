#include "../../include/Utilities/MyMath.h"
#include "../../include/2DGraphics/Color.h"
#include "../../include/Utilities/Vector.h"
#include "../../include/2DGraphics/Line.h"
#include "../../include/2DGraphics/2DGraphicVector.h"




/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class GraphicVector2D
* -------------------------------------------------------------------------------------------------------
*/
/*
* Initialization of static const member variables.
*/
const unsigned int GraphicVector2D::ARROW_HEAD_FIN_MAGNITUDE = 10;
const float GraphicVector2D::ARROW_HEAD_FIN_ROTATION = 45.0f; /*In degrees*/

/*
* Constructor(s)
*/
GraphicVector2D::GraphicVector2D(const Vector2F &newTail, const Vector2F &newHead)
{
	mTail = new Vector2F(newTail.GetX(), newTail.GetY());
	mHead = new Vector2F(newHead.GetX(), newHead.GetY());
}

GraphicVector2D::GraphicVector2D(const Vector2I &newTail, const Vector2I &newHead, const Color3 &newColor)
{
	mTail = new Vector2F((float)newTail.GetX(), (float)newTail.GetY());
	mHead = new Vector2F((float)newHead.GetX(), (float)newHead.GetY());
	mColor.Set(newColor);
}

/*
* Accessors
*/
Vector2F GraphicVector2D::GetHead() const
{
	return *mHead;
}

Vector2F GraphicVector2D::GetTail() const
{
	return *mTail;
}

Color3 GraphicVector2D::GetColor() const
{
	return mColor;
}

float GraphicVector2D::GetMagnitude() const
{
	return sqrtf(MyPow((float)(mHead->GetX() - mTail->GetX()), 2) + MyPow((float)(mHead->GetY() - mTail->GetY()), 2));
}

/*Increasing theta in the counter-clockwise direction.*/
float GraphicVector2D::GetDirectionInDegrees() const
{
	float theta = (GetDirectionInRadians() * 180.0f / MyPI());
	return theta;
}

/*Increasing theta in the counter-clockwise direction.*/
float GraphicVector2D::GetDirectionInRadians() const
{
	if (mHead->GetX() - mTail->GetX() == 0)
		return (mHead->GetY() - mTail->GetY() >= 0) ? MyPI() / 2.0f : -MyPI() / 2.0f;

	float theta = atanf((float)(mHead->GetY() - mTail->GetY()) / (float)(mHead->GetX() - mTail->GetX()));
	theta = (theta == 0 && mHead->GetX() - mTail->GetX() < 0) ? MyPI() : theta;

	/*atanf only returns a value between -pi and pi, so check to see if we should add
	pi to the return value.*/
	if (theta != MyPI() && mHead->GetX() <= mTail->GetX())
		theta += MyPI();

	return theta;
}

/*Keeps the tail fixed and adjusts the head position so that the magnitude is 1.*/
GraphicVector2D GraphicVector2D::GetNormalized() const
{
	GraphicVector2D *retGraphicVector2D = new GraphicVector2D(Vector2F(0.0f, 0.0f), *mHead);
	retGraphicVector2D->SetHead(Vector2F(MyPow(cos(GetDirectionInRadians()), 1), MyPow(sin(GetDirectionInRadians()), 1)));

	return *retGraphicVector2D;
}

void GraphicVector2D::Draw() const
{
	Draw(mColor);
}

void GraphicVector2D::Draw(const Color3 &overrideColor) const
{
	Line mainBody = Line(Vector2I((int)mTail->GetX(), (int)mTail->GetY()), Vector2I((int)mHead->GetX(), (int)mHead->GetY()), mColor);

	float leftFinTheta = GetDirectionInRadians() + MyPI() + ARROW_HEAD_FIN_ROTATION * MyPI() / 180.0f;
	float rightFinTheta = GetDirectionInRadians() + MyPI() - ARROW_HEAD_FIN_ROTATION * MyPI() / 180.0f;

	Line leftFin = Line(Vector2I((int)mHead->GetX(), (int)mHead->GetY()),
		Vector2I((int)(mHead->GetX() + ARROW_HEAD_FIN_MAGNITUDE * cos(leftFinTheta)),
		(int)(mHead->GetY() + ARROW_HEAD_FIN_MAGNITUDE * sin(leftFinTheta))),
		mColor);
	Line rightFin = Line(Vector2I((int)mHead->GetX(), (int)mHead->GetY()),
		Vector2I((int)(mHead->GetX() + ARROW_HEAD_FIN_MAGNITUDE * cos(rightFinTheta)),
		(int)(mHead->GetY() + ARROW_HEAD_FIN_MAGNITUDE * sin(rightFinTheta))),
		mColor);

	mainBody.Draw(overrideColor);
	leftFin.Draw(overrideColor);
	rightFin.Draw(overrideColor);
}

/*
* Mutators
*/
void GraphicVector2D::SetHead(const Vector2F &newHead)
{
	Vector2F *temp = new Vector2F(newHead.GetX(), newHead.GetY());

	mHead->SetX(temp->GetX());
	mHead->SetY(temp->GetY());
}

void GraphicVector2D::SetTail(const Vector2F &newTail)
{
	Vector2F *temp = new Vector2F(newTail.GetX(), newTail.GetY());

	mTail->SetX(temp->GetX());
	mTail->SetY(temp->GetY());
}

/*Rotates the head about the tail by newRotation degrees. Magnitude is preserved.*/
void GraphicVector2D::SetDirectionInDegrees(float newRotation)
{
	float magnitude = GetMagnitude();
	float thetaInRadians = newRotation * MyPI() / 180.0f;
	float dx = magnitude * cos(thetaInRadians);
	float dy = magnitude * sin(thetaInRadians);
	mHead->SetX(mTail->GetX() + dx);
	mHead->SetY(mTail->GetY() + dy);
}

void GraphicVector2D::SetColor(const Color3 &newColor)
{
	mColor.Set(newColor);
}

void GraphicVector2D::Normalize()
{
	GraphicVector2D temp = GetNormalized();
	SetHead(temp.GetHead());
}

/*Clear pixels from pixelBuffer.*/
void GraphicVector2D::Clear()
{
	Draw(Color3(0.0f, 0.0f, 0.0f));
}

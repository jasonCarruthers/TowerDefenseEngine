#ifndef HFILE_2D_GRAPHIC_VECTOR
#define HFILE_2D_GRAPHIC_VECTOR

#include "../../include/Utilities/Vector.h"
#include "../../include/2DGraphics/Color.h"



/*A cartesian vector in 2D space with an arrow head depicting the head of the vector.*/
class GraphicVector2D
{
public:
	static const unsigned int ARROW_HEAD_FIN_MAGNITUDE;
	static const float ARROW_HEAD_FIN_ROTATION; /*In degrees*/
public:
	/*
	* Constructor(s)
	*/
	GraphicVector2D(const Vector2F &newTail = Vector2F(0, 0), const Vector2F &newHead = Vector2F(0, 0));
	GraphicVector2D(const Vector2I &newTail, const Vector2I &newHead, const Color3 &newColor);

	/*
	* Accessors
	*/
	Vector2F GetTail() const;
	Vector2F GetHead() const;
	Color3 GetColor() const;
	float GetMagnitude() const;
	float GetDirectionInDegrees() const; /*Increasing theta in the counter-clockwise direction.*/
	float GetDirectionInRadians() const; /*Increasing theta in the counter-clockwise direction.*/
	GraphicVector2D GetNormalized() const;
	void Draw() const;
	void Draw(const Color3 &overrideColor) const;

	/*
	* Mutators
	*/
	void SetTail(const Vector2F &newTail);
	void SetHead(const Vector2F &newHead);
	void SetDirectionInDegrees(float newRotation); /*Rotates the head about the tail by newRotation degrees.
												   Magnitude is preserved.*/
	void SetColor(const Color3 &newColor);
	void Normalize();
	void Clear(); /*Clear pixels from pixelBuffer.*/

private:
	Vector2F *mHead; /*The end of the directed vector.*/
	Vector2F *mTail; /*The beginning of the directed vector.*/
	Color3 mColor;
};



#endif /*HFILE_2D_GRAPHIC_VECTOR*/
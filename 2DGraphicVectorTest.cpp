#include "../../include/Utilities/Vector.h"
#include "../../include/Utilities/MyMath.h"
#include "../../include/Main.h"
#include "../../include/2DGraphics/2DGraphicVector.h"



/*
* Global functions
*/
void TestGraphicVector2D()
{
	GraphicVector2D test;
	test.SetTail(Vector2F(500, 400));
	const unsigned int MAGNITUDE = 50;

	for (int i = 0; i < 360; i++)
	{
		test.SetHead(Vector2F(test.GetTail().GetX() + MAGNITUDE * cos(i * MyPI() / 180.0f),
			test.GetTail().GetY() + MAGNITUDE * sin(i * MyPI() / 180.0f)));
		test.Draw();
		Display();
		test.Clear();
	}
}
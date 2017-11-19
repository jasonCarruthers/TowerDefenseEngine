/*
* Programmer: Jason Carruthers
*/
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "../include/Utilities/MyMath.h"
#include "../include/General.h"
#include "../include/2DGraphics/Circle.h"
#include "../include/2DGraphics/Rectangle.h"
#include "../include/UI/UI.h"
#include "../include/Camera/Camera.h"
#include "../include/Utilities/Vector.h"
#include "../include/2DGraphics/Color.h"
#include "../include/Window/Pixel.h"
#include "../include/Window/Utilities.h"
#include "../include/2DGraphics/Image.h"
#include "../include/UserInput/UserInput.h"
#include "../include/Main.h"
#include "../ImageTest.h"
#include "../BitReaderTestRunner.h"







/*
* Functions
*/
void TestRectangleIntersection()
{
	MyRectangle rect1 = MyRectangle(Vector2I(100, 100), Vector2I(100, 100), GetRandomColor().GetColor3());
	MyRectangle rect2 = MyRectangle(Vector2I(150, 200), Vector2I(50, 50), GetRandomColor().GetColor3());

	if (rect1.ContainsRect(rect2))
		int x = 5;
}

void ColorizeScreen()
{
	for (int y = 0; y < (int)WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < (int)WINDOW_WIDTH; x++)
		{
			SetPixel(x, y, GetRandomBrightColor().GetColor3());
		}
	}
}

int main(int argc, char *argv[])
{
	/*Seed the random number generator*/
	srand(static_cast<int>(time(0)));


	glutInit(&argc, argv);

	InitWindow();
	RefreshScreen();
	//ColorizeScreen();

	glutDisplayFunc(Display);
	glutReshapeFunc(ReshapeWindow);
	glutKeyboardFunc(KeyboardInput);
	glutMouseFunc(MouseInput);
	glutPassiveMotionFunc(PassiveMouseMove);
	glutMotionFunc(NonpassiveMouseMove);

    BitReaderTestRunner::RunTests();
    //RunUnitTests();
    //CreateTestGIF_2x1White();
    GIF testGIF = GIF("image/FourColorsOnWhite_8x16.gif");
    //testGIF.LoadAndDisplayFileContents("image/BlackAndWhite.gif");
    //testGIF.Load("image/Rotating_earth_large.gif");
    std::cout << "\n\n\n";
    testGIF.DisplayVariables();
    testGIF.Draw();

	glutMainLoop();
	return 0;
}

void InitWindow()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	int mainWindow = glutCreateWindow("Tower Defense Engine");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	/*Stuff to display goes here*/
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, pixelBuffer);
	/*End stuff to display*/
	
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

void ReshapeWindow(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	glClear(GL_COLOR_BUFFER_BIT);
}

void KeyboardInput(unsigned char key, int mouseX, int mouseY)
{
	HandleKeyboardInput(key, mouseX, mouseY);

	glutPostRedisplay();
}

void MouseInput(int button, int action, int mouseX, int mouseY)
{
	HandleMouseInput(button, action, mouseX, mouseY);
}

void PassiveMouseMove(int mouseX, int mouseY)
{
	//HandlePassiveMouseMove(mouseX, mouseY);
}

void NonpassiveMouseMove(int mouseX, int mouseY)
{
	//HandleNonpassiveMouseMove(mouseX, mouseY);
}
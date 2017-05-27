#include "../include/Main.h"
#include "../include/General.h"
#include "../include/UserInput.h"
#include "../include/UI.h"
#include "../include/Camera.h"


float cameraXZRotationAboutWorldOrigin = 45.0f; /*In degrees.*/
float xzDistFromWorldOrigin;
const unsigned int deltaTheta = 10;


/*
* Global functions
*/
void HandleKeyboardInput(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 'W': 
	case 'w':
		break;
	case 'S': 
	case 's':
		break;
	case 'A':
	case 'a':
		break;
	case 'D':
	case 'd':
		break;
	case 'E':
	case 'e':
		break;
	case 'R': 
	case 'r':
		break;
	default:
		break;
	}
}

void HandleMouseInput(int button, int action, int mouseX, int mouseY)
{
	/*Pass along mouse info for updating checkboxes.*/
	checkboxHandler->MonitorCheckboxes(mouseX, mouseY, button, action);

	/*Pass along mouse info for updating sliders.*/
	sliderHandler->MonitorSliders(mouseX, mouseY, button, action);

	/*Pass along mouse info for updating buttons.*/
	buttonHandler->MonitorButtons(mouseX, mouseY, button, action);
}

void HandlePassiveMouseMove(int mouseX, int mouseY)
{
	/*Pass along mouse info for updating checkboxes*/
	checkboxHandler->MonitorCheckboxes(mouseX, mouseY, MAGIC_GARBAGE, MAGIC_GARBAGE);

	/*Pass along mouse info for updating buttons*/
	buttonHandler->MonitorButtons(mouseX, mouseY, MAGIC_GARBAGE, MAGIC_GARBAGE);
}

void HandleNonpassiveMouseMove(int mouseX, int mouseY)
{
	/*Pass along mouse info for updating checkboxes.*/
	checkboxHandler->MonitorCheckboxes(mouseX, mouseY, MAGIC_GARBAGE, MAGIC_GARBAGE);

	/*Pass along mouse info for updating sliders.*/
	sliderHandler->MonitorSliders(mouseX, mouseY, MAGIC_GARBAGE, MAGIC_GARBAGE);

	/*Pass along mouse info for updating buttons.*/
	buttonHandler->MonitorButtons(mouseX, mouseY, MAGIC_GARBAGE, MAGIC_GARBAGE);
}
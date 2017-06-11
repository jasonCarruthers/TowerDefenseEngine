#include "../../include/Main.h"
#include "../../include/General.h"
#include "../../include/2DGraphics/Line.h"
#include "../../include/Utilities/MyMath.h"
#include "../../include/Utilities/Vector.h"
#include "../../include/Camera/Camera.h"




/*
* Global variables
*/
Camera *camera;





/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Camera
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructor(s)
*/
Camera::Camera(const Vector2F &newPosition)
{
	SetPosition(newPosition);
}

/*
* Accessors
*/
Vector2F Camera::GetPosition() const
{
	return mPosition;
}

/*
* Mutators
*/
void Camera::SetPosition(const Vector2F &newPosition)
{
	mPosition.Set(newPosition);
}




/*
* Global functions
*/
void InitCamera()
{
	camera = new Camera();
}



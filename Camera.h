#ifndef HFILE_CAMERA
#define HFILE_CAMERA




class Camera
{
public:
	/*
	* Constructor(s)
	*/
	Camera(const Vector2F &newPosition = Vector2F(100, 100));

	/*
	* Accessors
	*/
	Vector2F GetPosition() const;

	/*
	* Mutators
	*/
	void SetPosition(const Vector2F &newPosition);

private:
	Vector2F mPosition;
};



/*
* Global function prototypes
*/
void InitCamera();


/*
* Global variables
*/
extern Camera *camera;




#endif /*HFILE_CAMERA*/
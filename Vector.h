#ifndef HFILE_VECTOR
#define HFILE_VECTOR


#include <string>


/*
* Classes
*/
class Vector2I
{
public:
	enum VectorElements
	{
		X,
		Y,
		Num__Elements,
	};
public:
	//Constructors
	Vector2I(int x = 0, int y = 0)
	{
		mArr[X] = x;
		mArr[Y] = y;
	}

	//Accessors
	int GetX() const
	{
		return mArr[X];
	}
	int GetY() const
	{
		return mArr[Y];
	}

	//Mutators
	void SetX(int newX)
	{
		mArr[X] = newX;
	}
	void SetY(int newY)
	{
		mArr[Y] = newY;
	}

	//Overloaded operators
	int &operator[](int index)
	{
		if (index < 0 || index >= (int)Num__Elements)
			return mArr[X]; //If index is out of bounds, return the first element by default.
		return mArr[index];
	}
	const int &operator[](int index) const
	{
		if (index < 0 || index >= (int)Num__Elements)
			return mArr[X]; //If index is out of bounds, return the first element by default.
		return mArr[index];
	}
	friend bool operator== (const Vector2I &pair1, const Vector2I &pair2)
	{
		return (pair1.GetX() == pair2.GetX() && pair1.GetY() == pair2.GetY());
	}
	friend Vector2I operator+(const Vector2I &left, const Vector2I &right)
	{
		return Vector2I(left[X] + right[X], left[Y] + right[Y]);
	}
	friend Vector2I operator-(const Vector2I &left, const Vector2I &right)
	{
		return Vector2I(left[X] - right[X], left[Y] - right[Y]);
	}
	friend Vector2I operator*(const Vector2I &left, const Vector2I &right)
	{
		return Vector2I(left[X] * right[X], left[Y] * right[Y]);
	}
	friend Vector2I operator*(const Vector2I &myVec, float multiplier)
	{
		return Vector2I((int)(myVec[X] * multiplier), (int)(myVec[Y] * multiplier));
	}
	friend Vector2I operator*(float multiplier, const Vector2I &myVec)
	{
		return Vector2I((int)(myVec[X] * multiplier), (int)(myVec[Y] * multiplier));
	}

protected:
	int mArr[Num__Elements];
};


class Vector3I
{
public:
	enum VectorElements
	{
		X,
		Y,
		Z,
		Num__Elements,
	};
public:
	//Constructors
	Vector3I(int x = 0, int y = 0, int z = 0)
	{
		mArr[X] = x;
		mArr[Y] = y;
		mArr[Z] = z;
	}

	//Accessors
	int GetX() const
	{
		return mArr[X];
	}
	int GetY() const
	{
		return mArr[Y];
	}
	int GetZ() const
	{
		return mArr[Z];
	}

	//Mutators
	void SetX(int newX)
	{
		mArr[X] = newX;
	}
	void SetY(int newY)
	{
		mArr[Y] = newY;
	}
	void SetZ(int newZ)
	{
		mArr[Z] = newZ;
	}

	//Overloaded operators
	int &operator[](int index)
	{
		if (index < 0 || index >= (int)Num__Elements)
			return mArr[X]; //If index is out of bounds, return the first element by default.
		return mArr[index];
	}
	const int &operator[](int index) const
	{
		if (index < 0 || index >= (int)Num__Elements)
			return mArr[X]; //If index is out of bounds, return the first element by default.
		return mArr[index];
	}
	friend bool operator== (const Vector3I &coord1, const Vector3I &coord2)
	{
		return (coord1.GetX() == coord2.GetX() && coord1.GetY() == coord2.GetY() && coord1.GetZ() == coord2.GetZ());
	}

protected:
	int mArr[Num__Elements];
};


class Vector2F
{
public:
	//Constructors
	Vector2F(float x = 0, float y = 0)
	{
		mX = x;
		mY = y;
	}

	//Accessors
	float GetX() const
	{
		return mX;
	}
	float GetY() const
	{
		return mY;
	}

	//Mutators
	void SetX(float newX)
	{
		mX = newX;
	}
	void SetY(float newY)
	{
		mY = newY;
	}
	void Set(const Vector2F& newVec)
	{
		mX = newVec.mX;
		mY = newVec.mY;
	}

	//Overloaded operators
	friend bool operator== (const Vector2F &pair1, const Vector2F &pair2)
	{
		return (pair1.GetX() == pair2.GetX() && pair1.GetY() == pair2.GetY());
	}
	friend Vector2F operator+(const Vector2F &left, const Vector2F &right)
	{
		return Vector2F(left.GetX() + right.GetX(), left.GetY() + right.GetY());
	}
	friend Vector2F operator*(const Vector2F &left, const Vector2F &right)
	{
		return Vector2F(left.GetX() * right.GetX(), left.GetY() * right.GetY());
	}
	friend Vector2F operator*(const Vector2F &myVec, float multiplier)
	{
		return Vector2F(myVec.GetX() * multiplier, myVec.GetY() * multiplier);
	}
	friend Vector2F operator*(float multiplier, const Vector2F &myVec)
	{
		return Vector2F(myVec.GetX() * multiplier, myVec.GetY() * multiplier);
	}

protected:
	float mX;
	float mY;
};


class Vector3F
{
public:
	enum VectorElements
	{
		X,
		Y,
		Z,
		Num__Elements,
	};
public:
	//Constructors
	Vector3F(float x = 0, float y = 0, float z = 0)
	{
		mArr[X] = x;
		mArr[Y] = y;
		mArr[Z] = z;
	}

	//Accessors
	float GetX() const
	{
		return mArr[X];
	}
	float GetY() const
	{
		return mArr[Y];
	}
	float GetZ() const
	{
		return mArr[Z];
	}

	//Mutators
	void Set(const Vector3F &newCoord)
	{
		mArr[X] = newCoord.mArr[X];
		mArr[Y] = newCoord.mArr[Y];
		mArr[Z] = newCoord.mArr[Z];
	}
	void Set(float newX, float newY, float newZ)
	{
		mArr[X] = newX;
		mArr[Y] = newY;
		mArr[Z] = newZ;
	}
	void SetX(float newX)
	{
		mArr[X] = newX;
	}
	void SetY(float newY)
	{
		mArr[Y] = newY;
	}
	void SetZ(float newZ)
	{
		mArr[Z] = newZ;
	}
	void Normalize()
	{
		/*Calculate magnitude.*/
		float magnitude = sqrt(mArr[X] * mArr[X] + mArr[Y] * mArr[Y] + mArr[Z] * mArr[Z]);

		/*Normalize each component.*/
		for (unsigned int i = 0; i < (unsigned int)Num__Elements; i++)
			mArr[i] /= magnitude;
	}

	//Overloaded operators
	float &operator[](int index)
	{
		if (index < 0 || index >= (int)Num__Elements)
			return mArr[X]; //If index is out of bounds, return the first element by default.
		return mArr[index];
	}
	const float &operator[](int index) const
	{
		if (index < 0 || index >= (int)Num__Elements)
			return mArr[X]; //If index is out of bounds, return the first element by default.
		return mArr[index];
	}
	friend bool operator== (const Vector3F &coord1, const Vector3F &coord2)
	{
		return (coord1.GetX() == coord2.GetX() && coord1.GetY() == coord2.GetY() && coord1.GetZ() == coord2.GetZ());
	}
	friend Vector3F operator-(const Vector3F &left, const Vector3F &right)
	{
		return Vector3F(left.mArr[X] - right.mArr[X], left.mArr[Y] - right.mArr[Y], left.mArr[Z] - right.mArr[Z]);
	}
	friend Vector3F operator+(const Vector3F &left, const Vector3F &right)
	{
		return Vector3F(left.mArr[X] + right.mArr[X], left.mArr[Y] + right.mArr[Y], left.mArr[Z] + right.mArr[Z]);
	}
	friend float operator*(const Vector3F &left, const Vector3F &right)
	{
		/*This is the dot product of left and right.*/
		return left.mArr[X] * right.mArr[X] + left.mArr[Y] * right.mArr[Y] + left.mArr[Z] * right.mArr[Z];
	}
	friend Vector3F operator*(const Vector3F &left, float multiplier)
	{
		/*This is the dot product of left and right.*/
		return Vector3F(left.mArr[X] * multiplier, left.mArr[Y] * multiplier, left.mArr[Z] * multiplier);
	}
	friend Vector3F operator*(float multiplier, const Vector3F &right)
	{
		/*This is the dot product of left and right.*/
		return Vector3F(right.mArr[X] * multiplier, right.mArr[Y] * multiplier, right.mArr[Z] * multiplier);
	}

protected:
	float mArr[Num__Elements];
};

class Vector4F
{
public:
	enum VectorElements
	{
		X,
		Y,
		Z,
		W,
		Num__Elements,
	};
public:
	/*
	* Constructor(s)
	*/
	Vector4F(float newX = 0.0f, float newY = 0.0f, float newZ = 0.0f, float newW = 0.0f);

	/*
	* Accessors
	*/
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetW() const;

	/*
	* Mutators
	*/
	void Set(const Vector4F &newCoord);
	void Set(float newX, float newY, float newZ, float newW);
	void SetX(float newX);
	void SetY(float newY);
	void SetZ(float newZ);
	void SetW(float newW);

	/*
	* Overloaded operators
	*/
	float &operator[](int index);
	const float &operator[](int index) const;
	friend bool operator==(const Vector4F &coord1, const Vector4F &coord2);
	friend Vector4F operator*(const Vector4F &left, const Vector4F &right);
	friend Vector4F operator*(const Vector4F &left, float multiplier);
	friend Vector4F operator*(float multiplier, const Vector4F &right);
	friend Vector4F operator+(const Vector4F &left, const Vector4F &right);
	friend Vector4F operator+(const Vector4F &left, float deltaSum);
	friend void operator+=(Vector4F &left, const Vector4F &right);
	friend void operator+=(Vector4F &left, float deltaSum);

protected:
	float mArr[Num__Elements];
};


/*Generic 2D Vector class*/
template <typename T>
class Vector2	/*2D Vector of Objects*/
{
public:
	enum VectorElements
	{
		X,
		Y,
		Num__Elements,
	};
public:
	/*Constructor(s)*/
	Vector2();
	Vector2(const T &first, const T &second);

	/*The "Big 3"*/
	Vector2(const Vector2 &copyObject); //Copy constructor
	void operator= (const Vector2 &equalObject); //Operator overloader
	~Vector2();

	/*Accessors*/
	T GetX() const;
	T GetY() const;

	/*Mutators*/
	void SetX(T newX);
	void SetY(T newY);

	/*Overloaded operators*/
	T &operator[](int index);
	const T &operator[](int index) const;
	/*friend bool operator==(const Vector2 &vec1, const Vector2 &vec2);*/

protected:
	T *mArr;
};

/*Generic 2D Vector implementation*/
template <typename T>
Vector2<T>::Vector2()
{
	mArr = new T[Num__Elements];
	std::cout << "Uninitialized Vector2<T> object!" << "\n";
}

template <typename T>
Vector2<T>::Vector2(const T &first, const T &second)
{
	mArr = new T[Num__Elements];
	mArr[X] = first;
	mArr[Y] = second;
}

template <typename T>
Vector2<T>::Vector2(const Vector2 &copyObject) //Copy constructor
{
	mArr = new T[Num__Elements];
	*mArr = *(copyObject[X]);
}

template <typename T>
void Vector2<T>::operator=(const Vector2 &equalObject) //Operator overloader
{
	delete[] mArr;

	mArr = new T[Num__Elements];
	*mArr = copyObject[X];
}

template <typename T>
Vector2<T>::~Vector2()
{
	delete[] mArr;
}

template <typename T>
T Vector2<T>::GetX() const
{
	return mArr[X];
}

template <typename T>
T Vector2<T>::GetY() const
{
	return mArr[Y];
}

template <typename T>
void Vector2<T>::SetX(T newX)
{
	mArr[X] = newX;
}

template <typename T>
void Vector2<T>::SetY(T newY)
{
	mArr[Y] = newY;
}

template <typename T>
T &Vector2<T>::operator[](int index)
{
	if (index < 0 || index >= (int)Num__Elements)
		return mArr[X]; //If index is out of bounds, return the first element by default.
	return mArr[index];
}

template <typename T>
const T &Vector2<T>::operator[](int index) const
{
	if (index < 0 || index >= (int)Num__Elements)
		return mArr[X]; //If index is out of bounds, return the first element by default.
	return mArr[index];
}

/*
template <typename T>
bool Vector2<T>::operator==(const Vector2 &vec1, const Vector2 &vec2)
{
return (vec1.GetX() == vec2.GetX() && vec1.GetY() == vec2.GetY());
}
*/





/*
* Global function prototypes
*/
void TestGraphicVector2D();
unsigned int StringToUInt(const std::string &str);
std::string UIntToString(unsigned int num);
std::string FloatToString(float num);
void RefreshScreen();

/*
* Global variables
*/





#endif /*HFILE_GENERAL*/
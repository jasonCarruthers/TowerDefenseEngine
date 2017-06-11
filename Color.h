#ifndef HFILE_COLOR
#define HFILE_COLOR


/*
* Classes
*/
class Color3
{
public:
	//Constructors
	Color3(float red = 1.0f, float green = 1.0f, float blue = 1.0f);

	//Accessors
	float GetRed() const;
	float GetGreen() const;
	float GetBlue() const;

	//Mutators
	void Set(const Color3& color);
	void Set(float newRed, float newGreen, float newBlue);
	void SetRed(float newRed);
	void SetGreen(float newGreen);
	void SetBlue(float newBlue);

	//Overloaded operators
	void operator=(const Color3& right);
	friend bool operator== (const Color3 &left, const Color3 &right);
	friend bool operator!= (const Color3 &left, const Color3 &right);
	friend Color3 operator*(const Color3 &left, const Color3 &right);
	friend Color3 operator*(const Color3 &left, float multiplier);
	friend Color3 operator*(float multiplier, const Color3 &right);
	friend Color3 operator/(const Color3 &left, float divisor);
	friend Color3 operator/(float divisor, const Color3 &right);
	friend Color3 operator+(const Color3 &left, const Color3 &right);
	friend void operator+=(Color3 &left, const Color3 &right);

protected:
	float mRed;
	float mGreen;
	float mBlue;
};


//Color4 is like Color3 but has an alpha value
class Color4 : public Color3
{
public:
	//Constructors
	Color4(float red = 1.0f, float green = 1.0f, float blue = 1.0f, float alpha = 1.0f);

	//Accessors
	float GetAlpha() const;
	Color3 GetColor3() const;

	//Mutators
	void Set(const Color4 &color);
	void Set(float newRed, float newGreen, float newBlue, float newAlpha);
	void SetAlpha(float newAlpha);


protected:
	float mAlpha;
};




extern Color4 GetRandomColor();
extern Color4 GetRandomBrightColor();



#endif /*HFILE_COLOR*/
#include <ctime>
#include "../../include/Utilities/Timer.h"



/*
* -------------------------------------------------------------------------------------------------------
* Implementation of class Timer
* -------------------------------------------------------------------------------------------------------
*/
/*
* Constructor(s)
*/
Timer::Timer(float newDuration, float newElapsedTime, float newStartTime)
{
	mDuration = newDuration;
	mElapsedTime = newElapsedTime;
	mStartTime = newStartTime;
}

/*
* Accessors
*/
float Timer::GetDuration() const
{
	return mDuration;
}

float Timer::GetElapsedTime() const
{
	return mElapsedTime;
}

float Timer::GetStartTime() const
{
	return mStartTime;
}

/*
* Mutators
*/
void Timer::SetDuration(float newDuration)
{
	mDuration = newDuration;
}

void Timer::SetElapsedTime(float newElapsedTime)
{
	mElapsedTime = newElapsedTime;
}

void Timer::SetStartTime(float newStartTime)
{
	mStartTime = newStartTime;
}

/*Reset elapsed time and set start time to current time*/
void Timer::Reset()
{
	mStartTime = (float)clock();
	mElapsedTime = 0.0f;
}

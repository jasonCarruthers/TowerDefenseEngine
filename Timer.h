#ifndef HFILE_TIMER
#define HFILE_TIMER



class Timer
{
public:
	/*
	* Constructor(s)
	*/
	Timer(float newDuration = 1.0f, float newElapsedTime = 0.0f, float newStartTime = 0.0f);

	/*
	* Accessors
	*/
	float GetDuration() const;
	float GetElapsedTime() const;
	float GetStartTime() const;

	/*
	* Mutators
	*/
	void SetDuration(float newDuration);
	void SetElapsedTime(float newElapsedTime);
	void SetStartTime(float newStartTime);
	void Reset();
private:
	float mDuration; /*How long to set the timer for*/
	float mElapsedTime; /*How much time has passed*/
	float mStartTime; /*What time the timer started ticking down*/
};


#endif /*HFILE_TIMER*/
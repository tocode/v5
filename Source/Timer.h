#ifndef TIMER_H
#define TIMER_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

class Timer
{
public:
	Timer()
	{
		start = -1;
		finish = -1;
	}
	void Start()
	{
		start = clock();
	}
	void Finish()
	{
		finish = clock();
	}
	float Duration()
	{
		if (start!=-1 && finish!=-1)
			return float(finish-start)/CLOCKS_PER_SEC;
		else
			return -1;
	}
private:
	clock_t start;
	clock_t finish;
};




#endif
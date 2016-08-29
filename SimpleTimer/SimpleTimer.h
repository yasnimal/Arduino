/**@file SimpleTimer.h
 * Simple Timer Library
 * @author Y.D.N
 * @version 1.0 29/08/2016
*/

#ifndef SimpleTimer_h
#define SimpleTimer_h

#include "Arduino.h"

class SimpleTimer
{
	public:
	SimpleTimer();
	void start();
	void stop();
	void setInterval(unsigned long interval);
	bool isReady();
	bool getRunStatus();
	
	
	private:
	unsigned long _timerValue;
	unsigned long _timerInterval;
	bool _runStatus = false;
	
};
#endif


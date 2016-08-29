/**@file SimpleTimer.cpp
 * \mainpage
 * Simple Timer Library
 * @author Y.D.N
 * @version 1.0 29/08/2016
*/

#include "Arduino.h"
#include "SimpleTimer.h"

/**
* Constructor
* 
*/
SimpleTimer::SimpleTimer(){};

/**
* Get the runStatus value
* @return run status
*/
bool SimpleTimer::getRunStatus(){
	return _runStatus;
}

/**
* Start the timer
* 
*/
void SimpleTimer::start()
{
	if(!_runStatus){
		_runStatus = true;
		_timerValue = millis();
	}	
}

/**
* Stop the timer
* 
*/
void SimpleTimer::stop()
{
	_runStatus = false;
}

/**
* Set time interval 
* @param interval Time interval
*/
void SimpleTimer::setInterval(unsigned long interval)
{
	_timerInterval = interval;
}

/**
* Check timer for predefined interval
* @return Whether timer has occured.
*/
bool SimpleTimer::isReady()
{
	if(_runStatus)
	{
		if(millis() - _timerValue > _timerInterval){
			_timerValue = millis();
			return true;
		}
	}
	
	return false;
}
/**@file LineCamera.h
 * Line Camera Library
 * @author Y.D.N
 * @version 1.0 19/08/2016
*/
 
#ifndef LineCamera_h
#define LineCamera_h

#include "Arduino.h"

class LineCamera
{
	public:
	const int BG_BLACK = 0;
	const int BG_WHITE = 1;
	
	LineCamera(int clockPin, int syncPin, int dataPin);
	void capture();
	int* getCameraValue();
	int getEdgePos();
	int getExposure();
	void setExposure(int expos);
	void setEdgeThreshold(int edgeThreshold);
	int getEdgeThreshold();
	void setBackground(int background);
	int getBackground();

	
	private:
	int _clockPin;
	int _syncPin;
	int _dataPin;
	int _expos;
	int _lightVal[128];
	int _background;
	int _edgeThreshold;

};

#endif
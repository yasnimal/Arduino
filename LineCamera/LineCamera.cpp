/**@file LineCamera.cpp
 * \mainpage
 * Line Camera Library
 * @author Y.D.N
 * @version 1.0 19/08/2016
*/

#include "Arduino.h"
#include "LineCamera.h"

/**
 * Constructor
 * @param clockPin Clock Pin of the line camera
 * @param syncPin Sync Pin of the line camera
 * @param dataPin Analog Pin of the line camera
 *
*/
LineCamera::LineCamera(int clockPin, int syncPin, int dataPin)
{
	pinMode(clockPin,OUTPUT);
	pinMode(syncPin,OUTPUT);
	pinMode(dataPin,INPUT);
	
	_clockPin = clockPin;
	_syncPin = syncPin;
	_dataPin = dataPin;
	
	//default values
	_expos = 500;
	_background = BG_WHITE;
	_edgeThreshold = 50;
	
}

/**
* Get exposure value
* @return exposure value
*/
int LineCamera::getExposure()
{
	return _expos;
}

/**
* Set Exposure level of the camera
* @param expos Exposure of the camera in micro Seconds
*/
void LineCamera::setExposure(int expos){
	_expos = expos;
}

/**
* Set edge threshold level to reject noises.
* @param edgeThreshold Edge Threshold.
*/
void LineCamera::setEdgeThreshold(int edgeThreshold)
{
	_edgeThreshold = edgeThreshold;
	
}

/**
* Get edge threshold
* @return edge threshold 
*/
int LineCamera::getEdgeThreshold()
{
	return _edgeThreshold;
	
}

/**
* Set Background colour
* @param background Background can be BG_WHITE or BG_BLACK
*/
void LineCamera::setBackground(int background){
	_background = background;
}

/**
* Get Background colour
* @return background Background can be BG_WHITE or BG_BLACK
*/
int LineCamera::getBackground(){
	return _background;
}

/**
* Capture image from camera and save in an array
* 
*/
void LineCamera::capture()
{
//clock out garbage
  digitalWrite(_clockPin, LOW);
  digitalWrite(_syncPin, HIGH);
  digitalWrite(_clockPin, HIGH);
  digitalWrite(_syncPin, LOW);
  digitalWrite(_clockPin, LOW);
  
  for (int j = 0; j < 128; j++)
  {
    digitalWrite(_clockPin, HIGH);
    digitalWrite(_clockPin, LOW);
  }
  
  //scan start
  delayMicroseconds(_expos);
  digitalWrite(_syncPin, HIGH);
  digitalWrite(_clockPin, HIGH);
  digitalWrite(_syncPin, LOW);
  
  digitalWrite(_clockPin, LOW);
  for (int j = 0; j < 128; j++)
  {
    delayMicroseconds(10);
    _lightVal[j] = analogRead(_dataPin);
    digitalWrite(_clockPin, HIGH);
    digitalWrite(_clockPin, LOW);
  }
	
}

/**
* Get saved camera data array
* @return data array
*/
int* LineCamera::getCameraValue(){
	return _lightVal;
}


/**
 * Calculate fabric edge position.
 * 0 - 126 range, 0 for no edge.
 * if max edge is greater than edge_threshold get edge value.
 * @return edge value
 */
 
int LineCamera::getEdgePos()
{
  int posVal;
  float temp[127];
  int index = 0;
  float minVal = 1023;
  float maxVal = 0;

  if (_background == BG_BLACK) { // background is black
    for (int i = 0; i < 127; i++) {
      temp[i] = _lightVal[i + 1] - _lightVal[i]; //take the difference between each pixel value

      if (temp[i] < minVal) {
        index = i;
        minVal = temp[i];
      }
    }
    if (abs(minVal) < _edgeThreshold) index = 0;
	

  } else if (_background == BG_WHITE) { // background is white (default)
    for (int i = 0; i < 127; i++) {
      temp[i] = _lightVal[i + 1] - _lightVal[i]; //take the difference between each pixel value

      if (temp[i] > maxVal) {
        index = i;
        maxVal = temp[i];
      }
    }
    if (maxVal < _edgeThreshold) index = 0;
	
	if (_lightVal[126] < 256){ //fully covered object on white background
		index = 126;
	}
  }

  posVal = index;

  return posVal;
	
}
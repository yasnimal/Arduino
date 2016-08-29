#include <LineCamera.h>

const int syncPin = 31;  //camera SI pin, can not change
const int clockPin = 30; //camera clk pin, can not change
const int dataPin = 0; // must be in range 0 to 5  , analog pin,

const int expos = 500;

LineCamera cam(clockPin, syncPin, dataPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  cam.setExposure(expos);
  cam.setBackground(cam.BG_WHITE);

}

void loop() {
  // put your main code here, to run repeatedly:
  cam.capture(); 
  int pos = cam.getEdgePos();
  
  Serial.println(pos);
  delay(10);
  
}

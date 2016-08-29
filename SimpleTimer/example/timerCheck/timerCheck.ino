#include <SimpleTimer.h>

SimpleTimer WorkTimer;
SimpleTimer FastTimer;

void setup() {
  Serial.begin(115200);
  WorkTimer.setInterval(5000);
  FastTimer.setInterval(500);
  WorkTimer.start();
  FastTimer.start();
}

void loop() {

  if (WorkTimer.isReady()) {
    Serial.print("Work:");
    Serial.println(millis());
  }

  if (FastTimer.isReady()) {
    Serial.print("Fast:");
    Serial.println(millis());
  }

}

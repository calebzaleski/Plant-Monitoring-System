//Project Libraries
#include "wifi.h"
#include "config.h"


void Waterpump3_5s() {
  digitalWrite(pumpPin, LOW);
  digitalWrite(pumpPin, HIGH);
  delay(3500); // 3.5 second

}
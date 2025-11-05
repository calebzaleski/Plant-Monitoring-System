#ifndef picosensor_h
#define picosensor_h

#include "Arduino.h"

class PlantMonitor {
  public:
    PlantMonitor(HardwareSerial& serial) : _sensor(serial) {}
    
    void begin() {
      _sensor.begin(9600);
    }
    
    int getWater() {
      _sensor.print("w");
      while (_sensor.available() && _sensor.read() != '=') {};
      return _sensor.parseInt();
    }
    
    float getTemp() {
      _sensor.print("t");
      while (_sensor.available() && _sensor.read() != '=') {};
      return _sensor.parseFloat();
    }
    
    float getHumidity() {
      _sensor.print("h");
      while (_sensor.available() && _sensor.read() != '=') {};
      return _sensor.parseFloat();
    }
    
    void ledOn() {
      _sensor.print("L");
    }
    
    void ledOff() {
      _sensor.print("l");
    }
    
  private:
    HardwareSerial& _sensor;
};

#endif
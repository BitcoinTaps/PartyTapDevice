#ifndef _I2CExtender_H_
#define _I2CExtender_H_

#include <Arduino.h>
#include <Wire.h>

#define SERVO_ANGLE  0x20
#define SERVO_ATTACH 0x21
#define SERVO_PING   0x22
#define SERVO_DETACH 0x23
#define RELAY_ATTACH 0x24
#define RELAY_DETACH 0x25
#define RELAY_HIGH   0x26
#define RELAY_LOW    0x27

class I2CExtender {
  private:
    int _servoPin;
    int _relayPin;
    int _address;
    TwoWire *_wire;    

    bool sendCommand(int cmd, int arg);
    bool sendCommand(int cmd);
  public:
    I2CExtender(TwoWire *wire,int address);
    
    bool begin();

    // servo operations
    bool servoWrite(int i);
    bool servoAttach(int pin); // attaches servo
    bool servoDetach(); // detaches servo

    // relay operations
    bool relayAttach(int pin); // attaches relay
    bool relayDetach(); // attaches relay
    bool relayHigh(); 
    bool relayLow();
};

#endif
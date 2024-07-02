#ifndef _I2CServo_H_
#define _I2CServo_H_

#include <Arduino.h>
#include <Wire.h>

#define SERVO_ANGLE  0x20
#define SERVO_ATTACH 0x21
#define SERVO_PING   0x22
#define SERVO_DETACH 0x23
#define SERVO_RELAY  0x24

class I2CServo {
  private:
    int _pin;
    int _address;
    TwoWire *_wire;    
    bool sendCommand(int cmd, int arg, int len);
    bool sendCommand(int cmd);
  public:
    I2CServo(TwoWire *wire,int address);
    
    bool begin();
    bool write(int i);
    bool attach(int pin);
    bool relay(int pin);
    bool detach();
};

#endif
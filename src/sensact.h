#ifndef SENSACT_H
#define SENSACT_H

#include <ESP32Servo.h>


class Sensact {
    private:
        // Local devicess
        Servo *tap_servo = NULL;        
        int relayPin = 0;

    public:
        // Create Sensact in a specific control mode
        Sensact();

        // initialize a regular servo
        bool initServo(int pin);

        // initialize a regular relay
        bool initRelay(int pin);

        // write data to servo
        void writeServo(int deg);

        // write data to relay
        void relayHigh();
        void relayLow();
};



#endif
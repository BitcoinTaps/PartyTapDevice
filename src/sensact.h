#ifndef SENSACT_H
#define SENSACT_H

// sensors and actuators
#include <I2CServo.h>
#include <Adafruit_PN532_NTAG424.h>
#include <Wire.h>
#include <ESP32Servo.h>

#define SENSACT_NFC_CB_UNAVAILABLE  0
#define SENSACT_NFC_CB_NOREAD       1
#define SENSACT_NFC_CB_INCOMPATIBLE 2
#define SENSACT_NFC_CB_NO_NTAG424   3
#define SENSACT_NFC_CB_NO_BYTES     4
#define SENSACT_NFC_CB_READ_SUCCESS 5
#define SENSACT_NFC_CB_NO_LNURLW    6
#define SENSACT_NFC_CB_NTAG424      7
#define SENSACT_NFC_CB_READING    8

class Sensact {
    private:
        int _sda = -1;
        int _scl = -1;
        int _bus = -1;
        TwoWire *_wire = NULL;
        
        // Tap servo is either I2C or regular
        I2CServo *i2c_tap_servo = NULL;
        Servo *tap_servo = NULL;

        // NFC device is through I2C
        Adafruit_PN532 *pn532 = NULL;
        uint8_t nfcbuffer[512];


        // scan if an I2C address is alive
        bool scanI2CAddress(int address);
    public:
        // Create with I2C support
        Sensact(int sda, int scl, int bus);

        // Create without I2C support
        Sensact();

        // Initialize 
        bool init();

        // initialize an I2C servo
        bool initServo(int address, int pin);

        // return true when servo is available
        bool isServoAvailable();

        // return true when NFC is available
        bool isNFCAvailable();
        
        // read an NFC card
        bool readNFC(int timeout,void (*cb)(int),void (*result)(int,const char *));

        // initialize a regular servo
        bool initServo(int pin);

        // write data to servo
        void writeServo(int deg);

        // initialize a PN532 NFC sensor
        bool initNFC();

};



#endif
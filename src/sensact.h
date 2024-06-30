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
        int _relay_pin = 0;

        // NFC device is through I2C
        Adafruit_PN532 *pn532 = NULL;
        uint8_t nfcbuffer[512];


        // scan if an I2C address is alive
        bool scanI2CAddress(int address);
    public:
        // Create Sensact in a specific control mode
        Sensact();

        // init I2C bus
        bool initI2C(int sda, int scl, int bus);

        // initialize an I2C servo
        bool initI2CServo(int address, int pin);

        // initialize a regular servo
        bool initServo(int pin);

        // initialize an I2C relay
        bool initI2CRelay(int address, int pin);

        // initialize a regular relay
        bool initRelay(int pin);

        // write data to servo
        void writeI2CServo(int deg);

        // write data to servo
        void writeServo(int deg);

        // write data to I2C relay
        void writeI2CRelay(int i);

        // write data to relay
        void writeRelay(int i);

        // read an NFC card
        bool readNFC(int timeout,void (*cb)(int),void (*result)(int,const char *));

        // initialize a PN532 NFC sensor
        bool initNFC();

        // returns true if NFC is available
        bool isNFCAvailable();

};



#endif
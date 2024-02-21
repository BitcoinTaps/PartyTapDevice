#include "sensact.h"

Sensact::Sensact() {
    this->_wire = NULL;
}

Sensact::Sensact(int sda, int scl, int bus) {
    this->_bus = bus;
    this->_scl = scl;
    this->_sda = sda;

    this->_wire = new TwoWire(bus);
}

bool Sensact::init() {    
    if ( this->_wire == NULL ) {
        Serial.println("[Sensact] Initialized without I2C support");
        return true;
    }

    if (this->_wire->begin(TAP_I2C_SDA, TAP_I2C_SCL) ) {
        Serial.println("[Sensact] Succesfully initialized I2C bus");
        return true;
    } else {
        Serial.println("[Sensact] Failure initializing I2C bus");
        return false;
    }
}

bool Sensact::initServo(int pin) {
    if ( this->i2c_tap_servo != NULL ) {
        Serial.println("[Sensact] Servo already initialized on I2C bus");
        return false;
    }

    if ( this->tap_servo != NULL ) {
        Serial.println("[Sensact] Servo already initialized");
        return false;
    }

    this->tap_servo = new Servo();

    if ( this->tap_servo->attach(pin) == 0 ) {
        Serial.println("[Sensact] Servo attached");
        return true;
    } 
    
    // destroy tap servo and return
    delete this->tap_servo;
    this->tap_servo = NULL;
    Serial.println("[Sensact] Servo attach failure");
    return false;
}

bool Sensact::scanI2CAddress(int address) {
    if ( this->_wire == NULL ) {
        Serial.println("[Sensact] I2C bus not initialized");
        return false;
    }

    this->_wire->beginTransmission(address);
    delay(2);
    int error = this->_wire->endTransmission();
    switch ( error ) {
        case 0:
            Serial.println("[Sensact] device detected on bus");
            return true;
        case 2:
            Serial.println("[Sensact] device not detected on bus");
            return false;
        default:
            Serial.println("[Sensact] I2C bus error");
            return false;
    }
}

bool Sensact::initServo(int address, int pin) {
    if ( this->i2c_tap_servo != NULL ) {
        Serial.println("[Sensact] servo already initialized");
        return false;
    }

    if ( ! this->scanI2CAddress(address) ) {
        Serial.println("[Sensact] tap servo not found on bus");
        return false;
    }
    
    this->i2c_tap_servo = new I2CServo(this->_wire,address);
    
    if ( this->i2c_tap_servo->attach(pin) ) {
        Serial.println("[Sensact] servo attached");
        return true;
    }

    // on failure, delete servo
    Serial.println("[Sensact] Failed to initialize tap servo on I2C");
    delete this->i2c_tap_servo;
    this->i2c_tap_servo = NULL;
    return false;
}    


bool Sensact::initNFC() {
    if ( this->pn532 != NULL ) {
        Serial.println("[Sensact] NFC already initialized");
        return false;
    }

    if ( ! this->scanI2CAddress(PN532_I2C_ADDRESS) ) {
        Serial.println("[Sensact] PN532 not found on bus");
        return false;
    }


    this->pn532 = new Adafruit_PN532(-1,-1,this->_wire);
    if ( ! this->pn532->begin() ) {
        Serial.println("[Sensact] Begin PN532 returned an error");

        delete this->pn532;
        this->pn532 = NULL;

        return false;
    }

    uint32_t versiondata = this->pn532->getFirmwareVersion();
    if (!versiondata) {
        Serial.println("[Sensact] Failed to get version data");

        delete this->pn532;
        this->pn532 = NULL;

        return false;
    }

    Serial.println("[Sensact] detected PN53x");

        // // Got ok data, print it out!
        // Serial.print("Found chip PN53x");
        // Serial.println((versiondata >> 24) & 0xFF, HEX);
        // Serial.print("Firmware ver. ");
        // Serial.print((versiondata >> 16) & 0xFF, DEC);
        // Serial.print('.');
        // Serial.println((versiondata >> 8) & 0xFF, DEC);

    if ( ! this->pn532->SAMConfig() ) {
        Serial.println("[Sensact] SAMConfig failed on PN53x");

        delete this->pn532;
        this->pn532 = NULL;

        return false;

    }
    return true;
}

void Sensact::writeServo(int deg) {
    if ( this->i2c_tap_servo ) {
        this->i2c_tap_servo->write(deg);
    } else if ( this->tap_servo ) {
        this->tap_servo->write(deg);
    } else {
        Serial.println("[Sensact] no servo available for writing");
    }
}

bool Sensact::isServoAvailable() {
    if ( this->i2c_tap_servo ) {
        return true;
    }
    if ( this->tap_servo ) {
        return true;
    }
    return false;    
}

bool Sensact::isNFCAvailable() {
    if ( this->pn532 ) {
        return true;
    }
    return false;
}
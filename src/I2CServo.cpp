#include <I2CServo.h>
#include <Arduino.h>
#include <Wire.h>

I2CServo::I2CServo(TwoWire *wire, int address) {
    this->_wire = wire;    
    this->_address = address;   
    this->_debug = true;
}

bool I2CServo::begin() {    
    this->_wire->beginTransmission(this->_address);
    delay(2);
    int error = this->_wire->endTransmission();
    if ( error == 0 ) {
        return true;
    } else {
        Serial.printf("Servo error %d for address %d\n",error,this->_address);
    }
    return false;
}

bool I2CServo::sendCommand(int cmd, int arg, int len) {
    int error = this->_wire->endTransmission(); 
    if ( error == 0 ) {
        this->_wire->beginTransmission(this->_address);
        this->_wire->write(cmd);
        if ( len > 0 ) {
            this->_wire->write(arg); 
        }
        error = this->_wire->endTransmission(); 
        if ( error == 0 ) {
            if ( this->_debug ) {
                Serial.printf("Succesfully wrote command %d to I2c bus\n",cmd);
            }
            return true;
        }
        Serial.printf("I2C error %d\n",error);
    } else {
        Serial.printf("Could not start transmission %d\n",error);
    }
    return false;
}

bool I2CServo::sendCommand(int cmd) {
    return this->sendCommand(SERVO_DETACH,0,0);
}


bool I2CServo::write(int angle) {
    return this->sendCommand(SERVO_ANGLE,angle,1);
}

bool I2CServo::attach(int pin) {
    this->_pin = pin;
    return this->sendCommand(SERVO_PIN,pin,1);
}

bool I2CServo::detach() {
    return this->sendCommand(SERVO_DETACH);
}

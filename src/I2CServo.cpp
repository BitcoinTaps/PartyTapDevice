#include <I2CServo.h>
#include <Arduino.h>
#include <Wire.h>



I2CServo::I2CServo(TwoWire *wire, int address) {
    this->_wire = wire;    
    this->_address = address;   
}

bool I2CServo::begin() {    
    this->_wire->beginTransmission(this->_address);
    delay(2);
    int error = this->_wire->endTransmission();
    if ( error == 0 ) {
        return true;
#ifdef DEBUG
    } else { 
        Serial.printf("Servo error %d for address %d\n",error,this->_address);
#endif
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
#ifdef DEBUG
            Serial.printf("Succesfully wrote command %d to I2c bus\n",cmd);
#endif
            return true;
        }
#ifdef DEBUG        
        Serial.printf("I2C error %d\n",error);
    } else {
        Serial.printf("Could not start transmission %d\n",error);
#endif
    }
    return false;
}

bool I2CServo::sendCommand(int cmd) {
    return this->sendCommand(SERVO_DETACH,0,0);
}


bool I2CServo::write(int i) {
    return this->sendCommand(SERVO_ANGLE,i,1);
}

bool I2CServo::attach(int pin) {
    this->_pin = pin;
    bool result = this->sendCommand(SERVO_ATTACH,pin,1);
#ifdef DEBUG
    Serial.printf("[I2CServo] attach result = %d\n",result);
#endif
    return result;
}

bool I2CServo::relay(int pin) {
    this->_pin = pin;
    bool result = this->sendCommand(SERVO_RELAY,pin,1);
#ifdef DEBUG
    Serial.printf("[I2CServo] attach result = %d\n",result);
#endif
    return result;
}


bool I2CServo::detach() {
    return this->sendCommand(SERVO_DETACH);
}

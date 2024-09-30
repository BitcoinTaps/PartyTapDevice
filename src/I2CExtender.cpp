#include <I2CExtender.h>
#include <Arduino.h>
#include <Wire.h>



I2CExtender::I2CExtender(TwoWire *wire, int address) {
    this->_wire = wire;    
    this->_address = address;   
}

bool I2CExtender::begin() {
    this->_wire->beginTransmission(this->_address);
    delay(2);
    int error = this->_wire->endTransmission();
    if ( error == 0 ) {
        return true;
#ifdef DEBUG
    } else { 
        Serial.printf("I2CExtender error %d for address %d\n",error,this->_address);
#endif
    }
    return false;
}

bool I2CExtender::sendCommand(int cmd, int arg) {
#ifdef DEBUG
    Serial.printf("[I2CExtender::sendCommand] cmd = %d, arg = %d\n",cmd,arg);
#endif    
    int error = this->_wire->endTransmission(); 
#ifdef DEBUG
    Serial.printf("[I2CExtender::sendCommand] endTransmission result = %d\n",error);
#endif


    error = 0;
    if ( error == 0 ) {
#ifdef DEBUG
    Serial.println("[I2CExtender::sendCommand] starting transmission");        
#endif
        this->_wire->beginTransmission(this->_address);
        this->_wire->write(cmd);
        this->_wire->write(arg); 
        error = this->_wire->endTransmission(); 
        if ( error == 0 ) {
#ifdef DEBUG
            Serial.printf("[I2CExtender::sendCommand] Succesfully sent command\n");
#endif
            return true;
        }
#ifdef DEBUG        
        Serial.printf("[I2CExtender:sendCommand] I2C error %d\n",error);
    } else {
        Serial.printf("[I2CExtender::sendCommand] Could not start transmission %d\n",error);
#endif
    }
    return false;
}

bool I2CExtender::sendCommand(int cmd) {
    return this->sendCommand(cmd,0);
}


bool I2CExtender::servoWrite(int i) {
    return this->sendCommand(SERVO_ANGLE,i);
}

bool I2CExtender::servoAttach(int pin) {
    this->_servoPin = pin;
    bool result = this->sendCommand(SERVO_ATTACH,pin);
#ifdef DEBUG
    Serial.printf("[I2CExtender::servoAttach] result = %d\n",result);
#endif
    return result;
}

bool I2CExtender::relayAttach(int pin) {
    this->_relayPin = pin;
    bool result = this->sendCommand(RELAY_ATTACH,this->_relayPin);
#ifdef DEBUG
    Serial.printf("[I2CExtender::relayAttach] result = %d\n",result);
#endif
    return result;
}

bool I2CExtender::relayDetach() {
    bool result = this->sendCommand(RELAY_DETACH);
#ifdef DEBUG
    Serial.printf("[I2CExtender::relayDetach] result = %d\n",result);
#endif
    return result;
}

bool I2CExtender::relayHigh() {
    bool result = this->sendCommand(RELAY_HIGH);
#ifdef DEBUG
    Serial.printf("[I2CExtender::relayHigh] result = %d\n",result);
#endif
    return result;
}

bool I2CExtender::relayLow() {
    bool result = this->sendCommand(RELAY_LOW);
#ifdef DEBUG
    Serial.printf("[I2CExtender::relayLow] result = %d\n",result);
#endif
    return result;
}

bool I2CExtender::servoDetach() {
    return this->sendCommand(SERVO_DETACH);
}

#include "sensact.h"

Sensact::Sensact() {
}


bool Sensact::initServo(int pin) {
#ifdef DEBUG
        Serial.printf("[Sensact::initServo] pin = %d\n",pin);
#endif 
    if ( this->tap_servo != NULL ) {
        return false;
    }

    this->tap_servo = new Servo();

    this->tap_servo->attach(pin);
#ifdef DEBUG
    Serial.println("[Sensact] Servo attached");
#endif 
    return true;
}

bool Sensact::initRelay(int pin) {
#ifdef DEBUG
    Serial.println("[Sensact::initRelay]");
#endif 
    this->relayPin = pin;

    pinMode(this->relayPin,OUTPUT);
    return true;
}

void Sensact::relayHigh() {
#ifdef DEBUG
    Serial.println("[Sensact::relayHIGH]");
#endif 
    digitalWrite(this->relayPin,HIGH);
}

void Sensact::relayLow() {
#ifdef DEBUG
    Serial.println("[Sensact::relayLow]");
#endif 
    digitalWrite(this->relayPin,LOW);
}

void Sensact::writeServo(int deg) {
#ifdef DEBUG
    Serial.printf("[Sensact::writeServo] deg = %d\n",deg);
#endif
    if ( this->tap_servo ) {
        this->tap_servo->write(deg);
#ifdef DEBUG
    } else {
        Serial.println("[Sensact::writeServo] no servo available for writing");
#endif
    }
}

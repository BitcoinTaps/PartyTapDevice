#include "sensact.h"

Sensact::Sensact() {
    this->_wire = NULL;
}

bool Sensact::initI2C(int sda, int scl, int bus) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2C]");
#endif 
    this->_wire = new TwoWire(bus);
    //this->_wire->setClock(400000);

    if (this->_wire->begin(TAP_I2C_SDA, TAP_I2C_SCL) ) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2C] Succesfully initialized I2C bus");
#endif 
        return true;
    } else {
#ifdef DEBUG
        Serial.println("[Sensact::initI2C] Failure initializing I2C bus");
#endif 
        return false;
    }

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


bool Sensact::scanI2CAddress(int address) {
#ifdef DEBUG
        Serial.printf("[Sensact::scanI2CAddress] address = %d\n",address);
#endif 
    if ( this->_wire == NULL ) {
#ifdef DEBUG
        Serial.println("[Sensact::scanI2CAddress] I2C bus not initialized");
#endif
        return false;
    }

    this->_wire->beginTransmission(address);
    delay(2);
    int error = this->_wire->endTransmission();
    switch ( error ) {
        case 0:
#ifdef DEBUG
            Serial.printf("[Sensact::scanI2CAddress] device detected on bus at %d\n",address);
#endif
            return true;
        case 2:
#ifdef DEBUG
            Serial.println("[Sensact::scanI2CAddress] device not detected on bus");
#endif
            return false;
        default:
#ifdef DEBUG
            Serial.println("[Sensact::scanI2CAddress] I2C bus error");
#endif
            return false;
    }
}

bool Sensact::initI2CExtender(int address) {
    if ( this->extender != NULL ) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2CExtender] extender already present");
#endif
        return false;
    }

    if ( ! this->scanI2CAddress(address) ) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2CExtender] extender not found");
#endif
        return false;
    } else {
#ifdef DEBUG
        Serial.println("[Sensact::initI2CExtender] extender found");
#endif
    }
    
    this->extender= new I2CExtender(this->_wire,address);
    return true;
}


bool Sensact::initI2CRelay(int pin) {
    if ( this->extender == NULL ) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2CExtender] extender not present");
#endif
        return false;
    }

    
    // start in relay mode
    if ( this->extender->relayAttach(pin) ) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2CRelay] relay attached");
#endif
        return true;
    }

    // on failure, delete servo
#ifdef DEBUG
    Serial.println("[Sensact::initI2CRelay] Failed to initialize relay");
#endif
    return false;
}

bool Sensact::initI2CServo(int pin) {
#ifdef DEBUG
        Serial.printf("[Sensact::initI2CServo] pin = %d\n",pin);
#endif 
    if ( this->extender == NULL ) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2CServo] extender not available");
#endif
        return false;
    }

    
    if ( this->extender->servoAttach(pin) ) {
#ifdef DEBUG
        Serial.println("[Sensact::initI2CServo] servo attached");
#endif
        return true;
    }

//    // on failure, delete servo
#ifdef DEBUG
    Serial.println("[Sensact::initI2CServo] Failed to initialize tap servo on I2C");
#endif
    return false;
}    


bool Sensact::initNFC() {
    if ( this->pn532 != NULL ) {
#ifdef DEBUG
        Serial.println("[Sensact] NFC already initialized");
#endif
        return false;
    }

    if ( ! this->scanI2CAddress(PN532_I2C_ADDRESS) ) {
#ifdef DEBUG
        Serial.println("[Sensact] PN532 not found on bus");
#endif
        return false;
    }

    this->pn532 = new Adafruit_PN532(-1,-1,this->_wire);
    if ( ! this->pn532->begin() ) {
#ifdef DEBUG
        Serial.println("[Sensact] Begin PN532 returned an error");
#endif

        delete this->pn532;
        this->pn532 = NULL;

        return false;
    }

    uint32_t versiondata = this->pn532->getFirmwareVersion();
    if (!versiondata) {
#ifdef DEBUG
        Serial.println("[Sensact] Failed to get version data");
#endif

        delete this->pn532;
        this->pn532 = NULL;

        return false;
    }

#ifdef DEBUG
    Serial.println("[Sensact] detected PN53x");
#endif

        // // Got ok data, print it out!
        // Serial.print("Found chip PN53x");
        // Serial.println((versiondata >> 24) & 0xFF, HEX);
        // Serial.print("Firmware ver. ");
        // Serial.print((versiondata >> 16) & 0xFF, DEC);
        // Serial.print('.');
        // Serial.println((versiondata >> 8) & 0xFF, DEC);

    if ( ! this->pn532->SAMConfig() ) {
#ifdef DEBUG
        Serial.println("[Sensact] SAMConfig failed on PN53x");
#endif

        delete this->pn532;
        this->pn532 = NULL;

        return false;

    }
    return true;
}

void Sensact::relayI2CHigh() {
#ifdef DEBUG
    Serial.printf("[Sensact::relayI2CHigh]\n");
#endif    
    if ( this->extender != NULL ) {
        this->extender->relayHigh();
#ifdef DEBUG
    } else {
        Serial.println("[Sensact::relayI2CHigh] relay not available");
#endif
    }
}

void Sensact::relayI2CLow() {
#ifdef DEBUG
    Serial.printf("[Sensact::relayI2CLow]\n");
#endif    
    if ( this->extender != NULL ) {
        this->extender->relayLow();
#ifdef DEBUG
    } else {
        Serial.println("[Sensact::relayI2CLow] relay not available");
#endif
    }
}



void Sensact::writeI2CServo(int deg) {
#ifdef DEBUG
    Serial.printf("[Sensact::writeI2CServo] deg = %d\n",deg);
#endif    
    if ( this->extender != NULL  ) {
        this->extender->servoWrite(deg);
#ifdef DEBUG
    } else {
        Serial.println("[Sensact::writeI2CServo] no servo available for writing");
#endif
    }
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

bool Sensact::readNFC(int timeout,void (*cb)(int), void (*result)(int,const char *)) {
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; 
    uint8_t uidLength;
    uint8_t success = 0;
    
    if ( ! this->pn532 ) {
        cb(SENSACT_NFC_CB_UNAVAILABLE);
        return false;
    }


    if ( timeout > 0 ) {
        success = this->pn532->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, timeout);
    } else {
        success = this->pn532->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    }



    if ( ! success ) {
        return false;
    }



    if ((uidLength != 7) && (uidLength != 4)) {
        cb(SENSACT_NFC_CB_INCOMPATIBLE);
        return false;
    }   

    if (!this->pn532->ntag424_isNTAG424()) {
        cb(SENSACT_NFC_CB_NO_NTAG424);
        return false;
    }

    cb(SENSACT_NFC_CB_READING);

    uint8_t bytesread = this->pn532->ntag424_ISOReadFile(this->nfcbuffer,sizeof(this->nfcbuffer));
    this->nfcbuffer[bytesread] = 0;
#ifdef DEBUG
    Serial.printf("Bytes read = %d\n",bytesread);
#endif 
 
 
    if ( bytesread == 0 ) {
        cb(SENSACT_NFC_CB_NO_BYTES);
        return false;
    }

    cb(SENSACT_NFC_CB_READING);


    if ( strncmp("lnurlw://",(char *)(this->nfcbuffer),9) != 0 ) {
#ifdef DEBUG
        Serial.println("this is not an LNURLW");
#endif
        cb(SENSACT_NFC_CB_NO_LNURLW);
        return false;
    }
 
#ifdef DEBUG
    Serial.println((char *)(this->nfcbuffer));
#endif 
    cb(SENSACT_NFC_CB_READ_SUCCESS);    
    result(bytesread,(const char *)this->nfcbuffer);
    return true;
 
}

bool Sensact::isNFCAvailable() {
    if ( this->pn532 ) {
        return true;
    }
    return false;
}
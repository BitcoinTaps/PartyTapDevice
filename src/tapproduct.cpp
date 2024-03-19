#include <tapproduct.h>

TapProduct::TapProduct() {

}

void TapProduct::setCurrency(const char *s) {
    this->currency = s;
}

const char *TapProduct::getCurrency() {
    return this->currency.c_str();
}

void TapProduct::setAmount(float f) {
    this->amount = f;
}

float TapProduct::getAmount() {
    return this->amount;
}

void TapProduct::setLabel(const char *s) {
    this->label = s;
}

void TapProduct::initPayString() {
    char charValue[30];
    if ( strcmp(this->currency.c_str(),"sat") == 0 ) { 
        snprintf_P(charValue,sizeof(charValue),PSTR("PAY %.0f %s"),this->amount,this->currency);    
    } else {
        snprintf_P(charValue,sizeof(charValue),PSTR("PAY %.2f %s"),this->amount,this->currency);
    }
    this->paystr = charValue;
}

void TapProduct::setSwitchID(const char *s) {
    this->switchid = s;
}

void TapProduct::setTapDuration(int i) {
    this->tapduration = i;
}

const char *TapProduct::getLabel() {
    return this->label.c_str();
}

const char *TapProduct::getPayString() {
    return this->paystr.c_str();
}

const char *TapProduct::getSwitchID() {
    return this->switchid.c_str();
}

int TapProduct::getTapDuration() {
    return this->tapduration;
}
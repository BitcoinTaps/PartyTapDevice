#include <tapproduct.h>

TapProduct::TapProduct() {

}

void TapProduct::setLabel(const char *s) {
    this->label = s;
}

void TapProduct::setPayString(const char *s) {
    this->paystr = s;
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
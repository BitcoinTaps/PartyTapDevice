#ifndef TAPPRODUCT_H
#define TAPPRODUCT_H

#include <Arduino.h>

class TapProduct {
    private:
        String switchid;
        String label;
        String paystr;
        int tapduration;
    public:
        TapProduct();

        void setSwitchID(const char *s);
        void setLabel(const char *s);
        void setPayString(const char *s);
        void setTapDuration(int i);

        const char *getSwitchID();
        const char *getLabel();
        const char *getPayString();
        int getTapDuration();

};

#endif
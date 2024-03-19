#ifndef TAPPRODUCT_H
#define TAPPRODUCT_H

#include <Arduino.h>

class TapProduct {
    private:
        String switchid;
        String label;
        String paystr;
        String currency;
        int tapduration;
        float amount;
    public:
        TapProduct();

        void setSwitchID(const char *s);
        void setLabel(const char *s);
        void initPayString();
        void setTapDuration(int i);
        void setCurrency(const char *s);
        void setAmount(float f);

        const char *getSwitchID();
        const char *getLabel();
        const char *getPayString();
        int getTapDuration();
        const char *getCurrency();
        float getAmount();

};

#endif
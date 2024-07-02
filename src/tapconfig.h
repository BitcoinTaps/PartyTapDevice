#ifndef TAPCONFIG_H
#define TAPCONFIG_H

#include <Arduino.h>

#define PAYMENT_MODE_ONLINE  0
#define PAYMENT_MODE_OFFLINE 1
#define PAYMENT_MODE_AUTO    2

#define CONTROL_MODE_NONE  0
#define CONTROL_MODE_SERVO_TIME 1
#define CONTROL_MODE_RELAY_TIME 2
#define CONTROL_MODE_I2C_SERVO_TIME 3
#define CONTROL_MODE_I2C_RELAY_TIME 4
#define CONTROL_MODE_I2C_SERVO_TICKS 5
#define CONTROL_MODE_I2C_RELAY_TICKS 6

class TapConfig {
    private:
        String wifi_ssid;
        String wifi_pwd;
        int servo_close;
        int servo_open;
        String lnbitshost;
        String deviceid;
        String pin;
        int tap_duration;
        int paymentMode;
        int controlMode;
        int backlight;
    public:
        TapConfig();

        bool load();
        bool save();

        void setWiFiSSID(const char *);
        void setWiFiPWD(const char *);
        void setServoClose(int i);
        void setServoOpen(int i);
        void setLNbitsHost(const char *s);
        void setDeviceID(const char *s);
        void setPIN(const char *s);
        void setTapDuration(int i);
        void setPaymentMode(int i);
        void setBacklight(int i);

        const char *getWiFiSSID();
        const char *getWiFiPWD();
        int getServoOpen();
        int getServoClose();
        int getBacklight();
        const char *getLNbitsHost();
        const char *getDeviceID();
        const char *getPIN();    
        int getTapDuration();
        int getPaymentMode();

        int getControlMode();
        void setControlMode(int i);
};

#endif
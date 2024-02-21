#ifndef TAPCONFIG_H
#define TAPCONFIG_H

#include <Arduino.h>

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

        const char *getWiFiSSID();
        const char *getWiFiPWD();
        int getServoOpen();
        int getServoClose();
        const char *getLNbitsHost();
        const char *getDeviceID();
        const char *getPIN();    
        int getTapDuration();
};

#endif
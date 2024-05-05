#ifndef TAPCONFIG_H
#define TAPCONFIG_H

#include <Arduino.h>

#define MODE_ONLINE  0
#define MODE_OFFLINE 1
#define MODE_AUTO    2

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
        int operatingmode;
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
        void setOperatingMode(int i);
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
        int getOperatingMode();
};

#endif
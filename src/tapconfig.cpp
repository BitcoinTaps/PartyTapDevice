#include <tapconfig.h>

#include <LittleFS.h>
#include <ArduinoJson.h>

// defines for the config file
#define PARTYTAP_CFG_SSID "ssid"
#define PARTYTAP_CFG_WIFIPASS "wifipassword"
#define PARTYTAP_CFG_SERVO_CLOSE "servoclose"
#define PARTYTAP_CFG_SERVO_OPEN "servoopen"
#define PARTYTAP_CFG_LNBITSHOST "lnbitshost"
#define PARTYTAP_CFG_DEVICEID "deviceid"
#define PARTYTAP_CFG_PIN "pin"
#define PARTYTAP_CFG_TAP_DURATAION "duration"
#define PARTYTAP_CFG_MODE "mode"

TapConfig::TapConfig() {
    this->pin = String(CONFIG_PIN);
    this->lnbitshost = "lnbits.bitcointaps.com";
    this->deviceid = "";
    this->servo_close = 90;
    this->servo_open = 90;
    this->wifi_ssid = "";
    this->wifi_pwd = "";
    this->tap_duration = 5000;
    this->operatingmode = MODE_ONLINE;
}

bool TapConfig::load() {
    File file = LittleFS.open("/config.json", "r");
    if (!file) {
        return false;
    }

    String content = file.readString();
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, content);
    file.close();

    if ( error.code() !=  DeserializationError::Ok ) {
        return false;
    }

    JsonArray arr = doc.as<JsonArray>();
    for (JsonObject obj: arr) {
        String name = obj["name"];

        if ( name == PARTYTAP_CFG_SSID ) {
          this->wifi_ssid = obj["value"].as<const char *>();
        } else if ( name == PARTYTAP_CFG_WIFIPASS ) {
          this->wifi_pwd = obj["value"].as<const char *>();
        } else if ( name == PARTYTAP_CFG_SERVO_CLOSE ) {
          this->servo_close = obj["value"].as<int>();
        } else if ( name == PARTYTAP_CFG_SERVO_OPEN ) {
          this->servo_open = obj["value"].as<int>();
        } else if ( name == PARTYTAP_CFG_LNBITSHOST ) {
          this->lnbitshost = obj["value"].as<const char *>();    
        } else if (name == PARTYTAP_CFG_PIN ) {
          this->pin = obj["value"].as<const char *>();
        } else if ( name == PARTYTAP_CFG_DEVICEID ) {
          this->deviceid = obj["value"].as<const char *>();
        } else if ( name == PARTYTAP_CFG_TAP_DURATAION ) {
            this->tap_duration = obj["value"].as<int>();
        } else if ( name == PARTYTAP_CFG_MODE ) {
            this->operatingmode = obj["value"].as<int>();
        }
      }

      return true;
}

bool TapConfig::save() {
    File file = LittleFS.open("/config.json", "w");
    if (!file) {
        return false;
    }

    DynamicJsonDocument doc(2048);
    doc[0]["name"] = PARTYTAP_CFG_SSID;
    doc[0]["value"] = this->wifi_ssid;    
    doc[1]["name"] = PARTYTAP_CFG_WIFIPASS;
    doc[1]["value"]= this->wifi_pwd;
    doc[2]["name"] = PARTYTAP_CFG_SERVO_CLOSE;
    doc[2]["value"] = this->servo_close;
    doc[3]["name"] = PARTYTAP_CFG_SERVO_OPEN;
    doc[3]["value"] = this->servo_open;
    doc[4]["name"] = PARTYTAP_CFG_LNBITSHOST;
    doc[4]["value"] = this->lnbitshost;
    doc[5]["name"] = PARTYTAP_CFG_PIN;
    doc[5]["value"] = this->pin;
    doc[6]["name"] = PARTYTAP_CFG_DEVICEID;
    doc[6]["value"] = this->deviceid;
    doc[7]["name"] = PARTYTAP_CFG_TAP_DURATAION;
    doc[7]["value"] = this->tap_duration;
    doc[8]["name"] = PARTYTAP_CFG_MODE;
    doc[8]["value"] = this->operatingmode;

    String output = "";
    serializeJson(doc, output);
    serializeJson(doc, file);
    file.close();

    return true;
}

void TapConfig::setWiFiSSID(const char *s) {
    this->wifi_ssid = s;
}

void TapConfig::setWiFiPWD(const char *s) {
    this->wifi_pwd = s;
}

void TapConfig::setDeviceID(const char *s) {
    this->deviceid = s;
}

void TapConfig::setLNbitsHost(const char *s) {
    this->lnbitshost = s;
}

void TapConfig::setPIN(const char *s) {
    this->pin = s;
}

void TapConfig::setServoOpen(int i) {
    this->servo_open = i;
}

void TapConfig::setServoClose(int i) {
    this->servo_close = i;
}

void TapConfig::setTapDuration(int i) {
    this->tap_duration = i;
}

const char *TapConfig::getWiFiSSID() {
    return this->wifi_ssid.c_str();
}

const char *TapConfig::getWiFiPWD() {
    return this->wifi_pwd.c_str();
}

const char *TapConfig::getDeviceID() {
    return this->deviceid.c_str();
}

const char *TapConfig::getLNbitsHost() {
    return this->lnbitshost.c_str();
}

const char *TapConfig::getPIN() {
    return this->pin.c_str();
}

int TapConfig::getServoOpen() {
    return this->servo_open;
}

int TapConfig::getServoClose() {
    return this->servo_close;
}

int TapConfig::getTapDuration() {
    return this->tap_duration;
}

void TapConfig::setOperatingMode(int i) {
    this->operatingmode = i;
}

int TapConfig::getOperatingMode() {
    return this->operatingmode;
}

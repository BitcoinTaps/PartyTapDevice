#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include "partytap.h"
#include "ui.h"
#include <ESP32Servo.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <TaskScheduler.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include <mutex>

std::recursive_mutex lvgl_mutex;

// config variables
int config_servo_close = 90;
int config_servo_open = 90;
String config_wifi_ssid = "";
String config_wifi_pwd = "";
int config_tap_duration = 5000;
String config_pin = String(CONFIG_PIN);
String config_lnbitshost = "";
String config_deviceid = "";
String config_wspath = "";

// the switches data
#define PARTYTAP_CFG_MAX_SWITCHES 3
int config_numswitches = 0;
String config_switchid[PARTYTAP_CFG_MAX_SWITCHES];
String config_label[PARTYTAP_CFG_MAX_SWITCHES];
String config_paystr[PARTYTAP_CFG_MAX_SWITCHES];
int config_duration[PARTYTAP_CFG_MAX_SWITCHES];

/// WebSocket Mutex
WebSocketsClient webSocket;
Servo servo;
bool bDoUpdate = false;
bool bDoReconnect = false;

// data related to a payment
int selectedItem = 0;  // the index of the selected button
String payment_request = "";  // the payment request
String payment_hash = ""; // the payment hash
String paymentStateURL = ""; // the URL to retrieve state of the payment
int tap_duration = 0;  // the duration of the tap


// task functions
void notifyOrderFulfilled();
void notifyOrderReceived();
void checkWiFi();
void checkUpdate();
void hidePanelMainMessage();
void expireInvoice();
void updateBeerTapProgress();
void loop0(void *parameters);

// task scheduler
Scheduler taskScheduler;
Task checkWiFiTask(TASK_SECOND, TASK_FOREVER, &checkWiFi);
Task hidePanelMainMessageTask(TASK_IMMEDIATE, TASK_ONCE, &hidePanelMainMessage);
Task expireInvoiceTask(TASK_IMMEDIATE, TASK_ONCE, &expireInvoice);
Task backToAboutPageTask(TASK_IMMEDIATE, TASK_ONCE, &backToAboutPage);
Task beerTapProgressTask(TASK_IMMEDIATE, TAPPROGRESS_STEPS, &updateBeerTapProgress);
Task checkUpdateTask(TASK_SECOND, TASK_FOREVER, &checkUpdate);


// defines for the config file
#define PARTYTAP_CFG_SSID "ssid"
#define PARTYTAP_CFG_WIFIPASS "wifipassword"
#define PARTYTAP_CFG_SERVO_CLOSE "servoclose"
#define PARTYTAP_CFG_SERVO_OPEN "servoopen"
#define PARTYTAP_CFG_LNBITSHOST "lnbitshost"
#define PARTYTAP_CFG_DEVICEID "deviceid"
#define PARTYTAP_CFG_PIN "pin"

void update_finished() {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_label_set_text(ui_LabelAboutMessage, PSTR("RESTARTING"));
}

void update_progress(int cur, int total) {
  char message[25];
  snprintf_P(message, sizeof(message), PSTR("UPDATE PROGRESS %d%%"), 100 * cur / total);
  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelAboutMessage, message);
  }
}

void update_error(int err) {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_label_set_text(ui_LabelAboutMessage, PSTR("UPDATE FAILURE"));
}

void doUpdate() {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);

  // disable buttons and move message panel so that it does not cover the logo
  lv_obj_set_y(ui_PanelAboutMessage, 120);
  lv_label_set_text(ui_LabelAboutMessage, PSTR("UPDATING FIRMWARE"));
  lv_obj_clear_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_LabelAboutStatus,LV_OBJ_FLAG_HIDDEN);
  lv_disp_load_scr(ui_ScreenAbout);	  
  

  bDoUpdate = true;
}

void checkUpdate() {
  if ( ! bDoUpdate ) {
    return;
  }

  webSocket.disableHeartbeat();
  webSocket.disconnect();

  WiFiClientSecure client;
  client.setInsecure();
  client.setTimeout(12000);


  httpUpdate.onEnd(update_finished);
  httpUpdate.onProgress(update_progress);
  httpUpdate.onError(update_error);

  t_httpUpdate_return ret = httpUpdate.update(client, config_lnbitshost, 443, "/partytap/static/firmware/ESP32_3248S035C/firmware.bin");
  
  // switch (ret) {
  //   case HTTP_UPDATE_FAILED:
  //       Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
  //       break;
  //     case HTTP_UPDATE_NO_UPDATES:
  //       Serial.println("HTTP_UPDATE_NO_UPDATES");
  //       break;

  //     case HTTP_UPDATE_OK:
  //       Serial.println("HTTP_UPDATE_OK");
  //       break;
  //   }
}

void beerClose() {
  servo.write(config_servo_close);
}

void beerOpen() {
  servo.write(config_servo_open);
}

void connectPartyTap(const char *ssid,const char *pwd, const char *deviceid,const char *lnbitshost) {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  config_wifi_ssid = String(ssid);
  config_wifi_pwd = String(pwd);
  config_deviceid = String(deviceid);
  config_lnbitshost = String(lnbitshost);

  saveConfig();

  bDoReconnect = true;
}

void saveTuning(int32_t servoClosed, int32_t servoOpen, int32_t tapDuration) {
  config_servo_close = servoClosed;
  config_servo_open = servoOpen;
  config_tap_duration = tapDuration;
  saveConfig();
}

void updatePIN(const char *pin) {
  config_pin = String(pin);
  saveConfig();
}

  
bool checkPIN(const char *pin) {
  if ( pin == NULL ) {
    return false;
  }
  if ( String(pin).equals(config_pin) ) {
    return true;
  }
  return false;
}

void notifyOrderReceived()
{
  String wsmessage = "{\"event\":\"acknowledged\",\"payment_hash\":\"";
  wsmessage += payment_hash;
  wsmessage += "\"}";
  webSocket.sendTXT(wsmessage);  
}

void notifyOrderFulfilled()
{
  String wsmessage = "{\"event\":\"fulfilled\",\"payment_hash\":\"";
  wsmessage += payment_hash;
  wsmessage += "\"}";
  webSocket.sendTXT(wsmessage);  
}

void toConfigPage()
{
  expireInvoiceTask.disable();

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_obj_add_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    lv_disp_load_scr(ui_ScreenPin);	  
  }
}

void backToAboutPage()
{
  expireInvoiceTask.disable();

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_obj_add_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    lv_disp_load_scr(ui_ScreenAbout);	  
  }
}

// update the slider of the progress bar while tapping
void updateBeerTapProgress()
{
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_bar_set_value(ui_BarBierProgress,beerTapProgressTask.getRunCounter(), LV_ANIM_OFF);

  if (beerTapProgressTask.isLastIteration() ) {
    beerClose();
    notifyOrderFulfilled();
    lv_obj_add_flag(ui_BarBierProgress,LV_OBJ_FLAG_HIDDEN);
    backToAboutPageTask.restartDelayed(TASK_SECOND * 3);
  }
} 

void beerScreen()
{
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_obj_add_flag(ui_BarBierProgress,LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui_ButtonBierStart,LV_OBJ_FLAG_HIDDEN);
  lv_bar_set_value(ui_BarBierProgress,0,LV_ANIM_OFF);
	lv_disp_load_scr(ui_ScreenBierFlowing);	
}

void beerStart()
{
  notifyOrderReceived();
  beerTapProgressTask.setInterval(tap_duration / TAPPROGRESS_STEPS);
  beerTapProgressTask.restart();

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_bar_set_value(ui_BarBierProgress,0, LV_ANIM_OFF);
    lv_obj_add_flag(ui_ButtonBierStart,LV_OBJ_FLAG_HIDDEN);
	  lv_obj_clear_flag(ui_BarBierProgress,LV_OBJ_FLAG_HIDDEN);
  }
	beerOpen();    
}

void freeBeerClicked()
{
  tap_duration = config_tap_duration;
  beerScreen();
}

void setUIStatus(String shortMsg, String longMsg, bool bDisplayQRCode = false) {
  static String prevLongMsg = "";

  if ( prevLongMsg.equals(longMsg) ) {
    return;
  } 
  prevLongMsg = longMsg;

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelAboutStatus,shortMsg.c_str());
    lv_label_set_text(ui_LabelConfigStatus,longMsg.c_str());
  }
}

void make_lnurlw_withdraw(String lnurlw) {
  String wsmessage = "{\"event\":\"lnurlw\",\"payment_request\":\""; 
  wsmessage += payment_request;
  wsmessage += "\",\"lnurlw\":\"";
  wsmessage += lnurlw;
  wsmessage += "\"}";
  webSocket.sendTXT(wsmessage);  
}

void hidePanelAboutMessage()
{
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_obj_add_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
}

void hidePanelMainMessage()
{
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_obj_add_flag(ui_PanelMainMessage,LV_OBJ_FLAG_HIDDEN);
}

void expireInvoice()
{ 
  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_obj_add_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    lv_disp_load_scr(ui_ScreenAbout);	  
  }

  expireInvoiceTask.disable();
  payment_hash = "";
  payment_request = "";  
}

void showInvoice(DynamicJsonDocument *doc)
{
  payment_request = (*doc)["pr"].as<String>();
  payment_hash = (*doc)["payment_hash"].as<String>();

  // Start countdown to expire invoice
  expireInvoiceTask.restartDelayed(TASK_SECOND * 60);

  // Update UI
  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_obj_add_flag(ui_PanelMainMessage,LV_OBJ_FLAG_HIDDEN);
    lv_qrcode_update(ui_QrcodeLnurl, payment_request.c_str(), payment_request.length());
    lv_obj_clear_flag(ui_QrcodeLnurl,LV_OBJ_FLAG_HIDDEN);
    lv_disp_load_scr(ui_ScreenMain);	
    lv_label_set_text(ui_LabelHeaderMain,config_paystr[selectedItem].c_str());
  }
}

// called from LVGL thread
void wantBierClicked(int item) {
  if ( config_numswitches == 0 ) {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_disp_load_scr(ui_ScreenPin);	
    return;
  }

  // reset all parameters
  selectedItem = item;
  payment_hash = "";
  payment_request = "";
  // set tap duration to default
  tap_duration = config_duration[selectedItem];

  // send request to create invoice
  if ( ! webSocket.isConnected() ) {
    return;
  }

  String wsmessage = "{\"event\":\"createinvoice\",\"switch_id\":\"";
  wsmessage += config_switchid[item];
  wsmessage += "\"}";

  if ( webSocket.sendTXT(wsmessage) ) {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelAboutMessage, "CREATING INVOICE");
    lv_obj_clear_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
  }
}


void myDelay(uint32_t ms) {
  delay(ms);
}

void loadConfig() {
  File file = LittleFS.open("/config.json", "r");
  if (file) {

    String content = file.readString();
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, content);
    file.close();

    if ( error.code() ==  DeserializationError::Ok ) {

      JsonArray arr = doc.as<JsonArray>();
      for (JsonObject obj: arr) {
        String name = obj["name"];
        String value = obj["value"];

        if ( name == PARTYTAP_CFG_SSID ) {
          config_wifi_ssid = String(value);
        } else if ( name == PARTYTAP_CFG_WIFIPASS ) {
          config_wifi_pwd = String(value);
        } else if ( name == PARTYTAP_CFG_SERVO_CLOSE ) {
          config_servo_close = String(value).toInt();
        } else if ( name == PARTYTAP_CFG_SERVO_OPEN ) {
          config_servo_open = String(value).toInt();
        } else if ( name == PARTYTAP_CFG_LNBITSHOST ) {
          config_lnbitshost = String(value);     
        } else if (name == PARTYTAP_CFG_PIN ) {
          config_pin = String(value);
        } else if ( name == PARTYTAP_CFG_DEVICEID ) {
          config_deviceid = String(value);
        }
      }
    }
  }
}

void saveConfig() {
  File file = LittleFS.open("/config.json", "w");
  if (!file) {
    return;
  }

  DynamicJsonDocument doc(2048);
  doc[0]["name"] = PARTYTAP_CFG_SSID;
  doc[0]["value"] = config_wifi_ssid;    
  doc[1]["name"] = PARTYTAP_CFG_WIFIPASS;
  doc[1]["value"]= config_wifi_pwd;
  doc[2]["name"] = PARTYTAP_CFG_SERVO_CLOSE;
  doc[2]["value"] = config_servo_close;
  doc[3]["name"] = PARTYTAP_CFG_SERVO_OPEN;
  doc[3]["value"] = config_servo_open;
  doc[4]["name"] = PARTYTAP_CFG_LNBITSHOST;
  doc[4]["value"] = config_lnbitshost;
  doc[5]["name"] = PARTYTAP_CFG_PIN;
  doc[5]["value"] = config_pin;
  doc[6]["name"] = PARTYTAP_CFG_DEVICEID;
  doc[6]["value"] = config_deviceid;

  String output = "";
  serializeJson(doc, output);
  serializeJson(doc, file);
  file.close();
}

void handlePaid(DynamicJsonDocument *doc) {
  if ( ! (*doc)["payment_hash"].as<String>().equals(payment_hash) ) {
    Serial.println("Payment Hash not OK");
    return;
  }
  payment_hash = "";

  expireInvoiceTask.disable();
  tap_duration = (*doc)["payload"].as<String>().toInt();
  beerScreen();
}


void configureSwitches(DynamicJsonDocument *doc) {
  char charValue[100];

  // clear current switches
  config_numswitches = 0;
  
  // bewaar opties in een keuzelijstje
  JsonArray switches = (*doc)["switches"].as<JsonArray>();
  config_numswitches = switches.size() < PARTYTAP_CFG_MAX_SWITCHES ? switches.size() : PARTYTAP_CFG_MAX_SWITCHES;
  for (int i=0;i < config_numswitches;i++) {
    JsonObject obj = switches[i];
    config_switchid[i] = obj["id"].as<String>();
    config_label[i] = obj["label"].as<String>();
    config_duration[i] = obj["duration"].as<int>();

    float amount = obj["amount"].as<float>();    
    String currency = obj["currency"].as<String>();
    if ( currency.equals("sat") ) { 
      sprintf(charValue,"PAY %.0f %s",amount,currency.c_str());
    } else {
      sprintf(charValue,"PAY %.2f %s",amount,currency.c_str());
    }
    config_paystr[i] = charValue;

    config_label[i].toUpperCase();
    config_paystr[i].toUpperCase();

    // get duration here? 
  }

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    switch ( config_numswitches ) {
      case 0:
        lv_obj_add_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        break;
      case 1:
        lv_obj_set_x(ui_ButtonAboutOne, 0);
        lv_label_set_text(ui_LabelAboutOne, config_label[0].c_str());
        lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        break;
      case 2:
        lv_obj_clear_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_x(ui_ButtonAboutOne, -60);
        lv_obj_set_x(ui_ButtonAboutTwo, 60);
        lv_label_set_text(ui_LabelAboutOne, config_label[0].c_str());
        lv_label_set_text(ui_LabelAboutTwo, config_label[1].c_str());
        break;
      case 3:
        lv_obj_clear_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_x(ui_ButtonAboutOne, -105);
        lv_obj_set_x(ui_ButtonAboutTwo, 0);
        lv_obj_set_x(ui_ButtonAboutThree, 105);
        lv_label_set_text(ui_LabelAboutOne, config_label[0].c_str());
        lv_label_set_text(ui_LabelAboutTwo, config_label[1].c_str());
        lv_label_set_text(ui_LabelAboutThree, config_label[2].c_str());
        break;
     default:
        break;
    }
  }

  setUIStatus("Ready to Serve","Ready to Serve");

}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:      
      if ( WiFi.status() != WL_CONNECTED ) {
        Serial.println("Wi-Fi disconnected");
        setUIStatus("WiFi Disconnected","WiFi Disconnected");
      } else {
        Serial.println("WebSocket disconnected");
        setUIStatus("WebSocket Disconnected","WebSocket Disconnected");        
      }      
      break;
    case WStype_CONNECTED:
      setUIStatus("WebSocket Connected","WebSocket Connected");
      break;
    case WStype_TEXT:
      {
        DynamicJsonDocument doc(2000);
        DeserializationError error = deserializeJson(doc, (char *)payload);
        if ( error.code() !=  DeserializationError::Ok ) {
          Serial.println("Error in JSON parsing");
        }
      
        // get the message type
        String event = doc["event"].as<String>();
        Serial.printf("WS Event type = %s\n",event.c_str());

        if ( event.equals("switches")) {
          configureSwitches(&doc);
        } else if ( event.equals("invoice")) {
          showInvoice(&doc);
        } else if ( event.equals("paid")) {     
          {
            const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);  
            lv_obj_clear_flag(ui_LabelMainMessage,LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(ui_LabelMainMessage, "PAYMENT SUCCES");
          }
          hidePanelMainMessageTask.restartDelayed(TASK_SECOND * 5);     
          handlePaid(&doc);
        } else if ( event.equals("paymentfailed") ) {
          const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);  
          lv_obj_clear_flag(ui_LabelMainMessage,LV_OBJ_FLAG_HIDDEN);
          lv_label_set_text(ui_LabelMainMessage, "PAYMENT FAILED");
          hidePanelMainMessageTask.restartDelayed(TASK_SECOND * 5);  

          // go back to about screen  
        }      
      }
      break;
    case WStype_PING:
    case WStype_PONG:
      break;    
    default:
      Serial.printf("Unknown Websocket message of type: %d\n",type);
			break;
  }


}


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);

  // add tasks to task scheduler
  taskScheduler.addTask(checkWiFiTask);
  taskScheduler.addTask(checkUpdateTask);
  taskScheduler.addTask(hidePanelMainMessageTask);
  taskScheduler.addTask(expireInvoiceTask);
  taskScheduler.addTask(backToAboutPageTask);
  taskScheduler.addTask(beerTapProgressTask);

  checkWiFiTask.restartDelayed(1000);
  checkUpdateTask.restartDelayed(5000);

  LittleFS.begin(true);


  smartdisplay_init();
  ui_init();

#ifdef BOARD_HAS_RGB_LED
  //smartdisplay_led_set_rgb(0,0,0);
#endif
  smartdisplay_lcd_set_backlight(BB_TFT_INTENSITY);
  // set UI components from config
  loadConfig();

  // set the values of the sliders
  lv_slider_set_value(ui_SliderConfigServoClosed,config_servo_close,LV_ANIM_OFF);
  lv_slider_set_value(ui_SliderConfigServoOpen,config_servo_open,LV_ANIM_OFF);
  lv_slider_set_value(ui_SliderConfigTapDuration,config_tap_duration,LV_ANIM_OFF);
  
  // set the current values of the labels
  lv_label_set_text_fmt(ui_LabelConfigServoClosed,"%d",config_servo_close);
  lv_label_set_text_fmt(ui_LabelConfigServoOpen,"%d",config_servo_open);
  lv_label_set_text_fmt(ui_LabelConfigTapDuration,"%d",config_tap_duration);

  // set wifi configuration and device id
  lv_textarea_set_text(ui_TextAreaConfigSSID,config_wifi_ssid.c_str());
  lv_textarea_set_text(ui_TextAreaWifiPassword,config_wifi_pwd.c_str());
  lv_textarea_set_text(ui_TextAreaConfigHost,config_lnbitshost.c_str());
  lv_textarea_set_text(ui_TextAreaConfigDeviceID,config_deviceid.c_str());
  lv_label_set_text(ui_LabelPINValue,"");

  servo.attach(BIER_SERVO_PIN);

  beerClose();
  
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(500);
  webSocket.enableHeartbeat(10000,2000,2);
    

  // set label in the About screen
  setUIStatus("Initialized","Initialized");

  WiFi.begin(config_wifi_ssid.c_str(),config_wifi_pwd.c_str());

  xTaskCreatePinnedToCore (
    loop0,     // Function to implement the task
    "loop0",   // Name of the task
    20000,      // Stack size in bytes
    NULL,      // Task input parameter
    10,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

}


void checkWiFi() {
  static bool bConnected = false;

  if ( bDoReconnect ) {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);  
    bDoReconnect = false;
    webSocket.disconnect();
    WiFi.disconnect();
    WiFi.begin(config_wifi_ssid,config_wifi_pwd);
  }

  if ( checkWiFiTask.isFirstIteration() ) { 
    bConnected = false;
  }

  wl_status_t status = WiFi.status();
  switch ( status ) {
    case WL_CONNECTED:
      if ( bConnected == false ) {
        setUIStatus("Wi-Fi connected","Wi-Fi connected");
        Serial.println("Connecting WebSocket");
        config_wspath = "/partytap/api/v1/ws/";
        config_wspath += config_deviceid;
        webSocket.beginSSL(config_lnbitshost, 443, config_wspath);
        bConnected = true;
      }
      break;
    case WL_NO_SSID_AVAIL:
      Serial.println("ERROR_CONFIG_SSID");
      setUIStatus("SSID not found","SSID not found");
      break;
    case WL_CONNECTION_LOST:
      Serial.println("CONNECTION LOST");
      break;
    case WL_IDLE_STATUS:
      Serial.println("W_IDLE_STATUS");
      break;
    case WL_DISCONNECTED:
      Serial.println("WL_DISCONNECTED");
      break;
    case WL_NO_SHIELD:
      Serial.println("Wi-Fi device not initialized");
      break;
    case WL_CONNECT_FAILED:
      Serial.println("WL_CONNECT_FAILED");
      break;
    default:
      Serial.printf("Unknown WiFi state %d\n",status);
      break;
    }


}

void loop0(void *parameters) 
{
  while ( 1 ) {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_task_handler();
  }
}


void loop()
{
  taskScheduler.execute();
  webSocket.loop();
}

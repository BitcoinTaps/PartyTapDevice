#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include "partytap.h"
#include "ui.h"
#include <sensact.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <TaskScheduler.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <I2CServo.h>
#include <mutex>
#include <tapconfig.h>
#include <tapproduct.h>
#include <productconfig.h>
#include <Adafruit_PN532_NTAG424.h>
#include <bitcoin.h>

std::recursive_mutex lvgl_mutex;

#define STR_INVOICE    PSTR("invoice")
#define STR_SAT        PSTR("sat")
#define STR_SWITCHES   PSTR("switches")
#define STR_RESTARTING PSTR("RESTARTING")

// config variables
TapConfig config;
String config_wspath = "";
ProductConfig productConfig;

// Sensors and actuators
Sensact *sensact = NULL;

/// WebSocket Mutex
WebSocketsClient webSocket;

bool bDoUpdate = false;
bool bDoReconnect = false;

// data related to a payment
int selectedItem = 0;  // the index of the selected button
String payment_request = "";  // the payment request
String payment_hash = ""; // the payment hash
String payment_pin = ""; // pin for offline payments
String tap_payment_hash = ""; // the payment hash of the current tap action
//String paymentStateURL = ""; // the URL to retrieve state of the payment
int tap_duration = 0;  // the duration of the tap

// task functions
void notifyOrderFulfilled();
void notifyOrderReceived();
void checkWiFi();
void checkUpdate();
void hidePanelMainMessage();
void expireInvoice();
void checkNFCPayment();
void updateBeerTapProgress();
void loop0(void *parameters);

// task scheduler
Scheduler taskScheduler;
Task checkWiFiTask(4 * TASK_SECOND, TASK_FOREVER, &checkWiFi);
Task hidePanelMainMessageTask(TASK_IMMEDIATE, TASK_ONCE, &hidePanelMainMessage);
Task expireInvoiceTask(TASK_IMMEDIATE, TASK_ONCE, &expireInvoice);
Task backToAboutPageTask(TASK_IMMEDIATE, TASK_ONCE, &backToAboutPage);
Task beerTapProgressTask(TASK_IMMEDIATE, TAPPROGRESS_STEPS, &updateBeerTapProgress);
Task checkUpdateTask(TASK_SECOND, TASK_FOREVER, &checkUpdate);
Task checkNFCPaymentTask(TASK_IMMEDIATE, TASK_FOREVER, &checkNFCPayment);



void setPanelMainMessage(const char *s,int timeout)  {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_label_set_text(ui_LabelMainMessage, s);  
  lv_obj_clear_flag(ui_PanelMainMessage, LV_OBJ_FLAG_HIDDEN);    
  hidePanelMainMessageTask.restartDelayed(TASK_SECOND * timeout);
}

void update_finished() {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_label_set_text(ui_LabelAboutMessage, STR_RESTARTING);
}

void update_progress(int cur, int total) {
  static char message[25];
  snprintf_P(message, sizeof(message), PSTR("UPDATE PROGRESS %d%%"), 100 * cur / total);
  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelAboutMessage, message);
  }
}

void display_rssi() {
  static char message[20];
  int rssi = WiFi.RSSI();
  if ( rssi < -90 ) {
    snprintf_P(message, sizeof(message), PSTR("Weak (%d)"), rssi);
  } else if ( rssi < -80 ) {
    snprintf_P(message, sizeof(message), PSTR("Fair (%d)"), rssi);
  } else if ( rssi < -70 ) {
    snprintf_P(message, sizeof(message), PSTR("Good (%d)"), rssi);
  } else if ( rssi < 0 ) {
    snprintf_P(message, sizeof(message), PSTR("Excellent (%d)"), rssi);
  } else {
    snprintf_P(message, sizeof(message), PSTR("No signal (%d)"), rssi);
  }

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelConfigRSSIValue, message);
  }  
}

void update_error(int err) {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  switch (err ) {
    case HTTP_UE_NO_PARTITION:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("NO PARTITION"));
      break;
    case HTTP_UE_BIN_FOR_WRONG_FLASH:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("WRONG FLASH"));
      break;
    case HTTP_UE_BIN_VERIFY_HEADER_FAILED:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("VERIFY FAILED"));
      break;
    case HTTP_UE_SERVER_FAULTY_MD5:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("HASH ERROR"));
      break;
    case HTTP_UE_SERVER_WRONG_HTTP_CODE:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("BAD SERVER RESPONSE"));      
      break;
    case HTTP_UE_SERVER_FORBIDDEN:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("NOT ALLOWED"));
      break;
    case HTTP_UE_SERVER_FILE_NOT_FOUND:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("FILE NOT FOUND"));
      break;
    case HTTP_UE_SERVER_NOT_REPORT_SIZE:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("SIZE NOT REPORTED"));
      break;
    case HTTP_UE_TOO_LESS_SPACE:
      lv_label_set_text(ui_LabelAboutMessage, PSTR("NOT ENOUGH SPACE"));
      break;
    default:
      break;
  }
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
  static char firmware_path[100];
  if ( ! bDoUpdate ) {
    return;
  }
  bDoUpdate = false;

  webSocket.disableHeartbeat();
  webSocket.disconnect();

  WiFiClientSecure client;
  client.setInsecure();
  client.setTimeout(12000);


  httpUpdate.onEnd(update_finished);
  httpUpdate.onProgress(update_progress);
  httpUpdate.onError(update_error);
  httpUpdate.rebootOnUpdate(true);

#define FIRMWARE_HOST "firmware.bitcointaps.com"
  snprintf_P(firmware_path, sizeof(firmware_path), PSTR("/partytap/ESP32_3248S035C/%s/firmware.bin"), productConfig.getServerVersion());


  t_httpUpdate_return ret = httpUpdate.update(client, FIRMWARE_HOST, 443, firmware_path);
  
  if ( ret == HTTP_UPDATE_FAILED ) {
#ifdef DEBUG
    Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
#endif
    update_error(httpUpdate.getLastError());
    delay(10000);
    ESP.restart();
    return;
  }
}

void beerClose() {
  sensact->writeServo(config.getServoClose());
}

void beerOpen() {
  sensact->writeServo(config.getServoOpen());
}

void connectPartyTap(const char *ssid,const char *pwd, const char *deviceid,const char *lnbitshost) {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  config.setWiFiSSID(ssid);
  config.setWiFiPWD(pwd);
  config.setDeviceID(deviceid);
  config.setLNbitsHost(lnbitshost);
  config.save();

  bDoReconnect = true;
}

void saveTuning(int32_t servoClosed, int32_t servoOpen, int32_t tapDuration) {
  config.setServoClose(servoClosed);
  config.setServoOpen(servoOpen);
  config.setTapDuration(tapDuration);
  config.save();
}

void updatePIN(const char *pin) {
  config.setPIN(pin);
  config.save();
}

bool checkConfigPIN(const char *pin) {
  if ( pin == NULL ) {
    return false;
  }

  if ( strcmp(pin,config.getPIN()) == 0 ) {
    return true;
  }

  return false;
}


void handlePINResult(const char *pin) {
  if ( checkConfigPIN(pin) == true ) {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);

    lv_dropdown_set_selected(ui_DropdownConfigOperatingMode,config.getOperatingMode());
  	lv_disp_load_scr(ui_ScreenConfig);	
		lv_label_set_text(ui_LabelPINValue,"ENTER PIN");
    return;
  }


  if ( strncmp(pin,payment_pin.c_str(),6) == 0 ) {
    payment_pin = "";
    beerScreen();
    return;
  }

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelPINValue,"PIN INCORRECT");    
  }

}

void notifyOrderReceived()
{
  String wsmessage = PSTR("{\"event\":\"acknowledged\",\"payment_hash\":\"");
  wsmessage += tap_payment_hash;
  wsmessage += PSTR("\"}");
  webSocket.sendTXT(wsmessage);  
}

void notifyOrderFulfilled()
{
  String wsmessage = PSTR("{\"event\":\"fulfilled\",\"payment_hash\":\"");
  wsmessage += tap_payment_hash;
  wsmessage += PSTR("\"}");
  webSocket.sendTXT(wsmessage);  
}

void toConfigPage()
{
  expireInvoiceTask.disable();
  if ( sensact->isNFCAvailable() ) {
    checkNFCPaymentTask.disable();
  }

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_obj_add_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    lv_disp_load_scr(ui_ScreenPin);	  
  }
}

void backToAboutPage()
{
  expireInvoiceTask.disable();
  if ( sensact->isNFCAvailable() ) {
    checkNFCPaymentTask.disable();
  }

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
  // the user hascommende to tap the beer, delete the payment_pin for offline payments
  payment_pin = "";
  
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
  tap_duration = config.getTapDuration();
  beerScreen();
}

void setUIStatus(const char *shortMsg, const char *longMsg, bool bDisplayQRCode = false) {
  static char prevLongMsg[50] = "";
  
  if ( strcmp(prevLongMsg,longMsg) == 0 ) {
    return;
  } 
  strncpy(prevLongMsg,longMsg,min(strlen(longMsg),strlen(prevLongMsg)));

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelAboutStatus,shortMsg);
    lv_label_set_text(ui_LabelConfigStatus,longMsg);
  }
}

void make_lnurlw_withdraw(const char *lnurlw) {
  String wsmessage = PSTR("{\"event\":\"lnurlw\",\"payment_request\":\""); 
  wsmessage += payment_request;
  wsmessage += PSTR("\",\"lnurlw\":\"");
  wsmessage += lnurlw;
  wsmessage += PSTR("\"}");
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
  if ( sensact->isNFCAvailable() ) {
    checkNFCPaymentTask.disable();
  }

  payment_pin = "";
  payment_hash = "";
  payment_request = "";  
}

void showInvoice(DynamicJsonDocument *doc)
{
  payment_request = (*doc)["pr"].as<const char *>();
  payment_hash = (*doc)["payment_hash"].as<const char *>();

  // Start countdown to expire invoice
  expireInvoiceTask.restartDelayed(TASK_SECOND * 60);
  if ( sensact->isNFCAvailable() ) {
    checkNFCPaymentTask.restart();
  }

  // Update UI
  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_obj_add_flag(ui_PanelMainMessage,LV_OBJ_FLAG_HIDDEN);
    lv_qrcode_update(ui_QrcodeLnurl, payment_request.c_str(), payment_request.length());
    lv_obj_clear_flag(ui_QrcodeLnurl,LV_OBJ_FLAG_HIDDEN);
    lv_disp_load_scr(ui_ScreenMain);	
    lv_label_set_text(ui_LabelHeaderMain,productConfig.getProduct(selectedItem)->getPayString());
    lv_obj_set_x(ui_ButtonMainAbout, 0);
    lv_obj_add_flag(ui_ButtonMainEnterPIN,LV_OBJ_FLAG_HIDDEN);
  }
}

// called from LVGL thread
void wantBierClicked(int item) {
  if ( productConfig.getNumProducts() == 0 ) {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_disp_load_scr(ui_ScreenPin);	
    return;
  }

  // reset all parameters
  selectedItem = item;
  payment_hash = "";
  payment_request = "";
  payment_pin = "";
  
  // set tap duration to default
  tap_duration = productConfig.getProduct(selectedItem)->getTapDuration();
  
  // send request to create invoice
  if ((( config.getOperatingMode() == MODE_AUTO ) || ( config.getOperatingMode() == MODE_ONLINE)) && webSocket.isConnected() ) {
    String wsmessage = PSTR("{\"event\":\"createinvoice\",\"switch_id\":\"");
    wsmessage +=  productConfig.getProduct(selectedItem)->getSwitchID();
    wsmessage += PSTR("\"}");

    if ( webSocket.sendTXT(wsmessage) ) {
      const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
      lv_label_set_text(ui_LabelAboutMessage, PSTR("CREATING INVOICE"));
      lv_obj_clear_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    }
  } else if (( config.getOperatingMode() == MODE_OFFLINE ) || ( config.getOperatingMode() == MODE_AUTO )) {
    // take the offline route
    const char *ckey = (const char *)productConfig.getKey();
    unsigned char key[16];

    for(int i=0;(i<16);i++) {
      key[i] = (unsigned char)ckey[i];
    }
    key[16] = 0;

#ifdef DEBUG
    Serial.printf("KEY: ");
    for (int i = 0; i < 16; i++)
    {
      Serial.printf("%02x",key[i]);
    }
    Serial.println();
#endif

    unsigned char iv[16];
    unsigned char iiv[16];

    for (int i = 0; i < 16; i++)
    {
      iiv[i] = random(256);
      iv[i] = iiv[i];    
    }

#ifdef DEBUG
    Serial.printf("IV: ");
    for (int i = 0; i < 16; i++)
    {
      Serial.printf("%02x",iv[i]);

    }
    Serial.println();
#endif

    for(int i=0;(i<6);i++) {
      payment_pin += String(random(10));
    }
    payment_pin[6] = 0;

    unsigned char input[128];
    memcpy(input, productConfig.getProduct(selectedItem)->getSwitchID(),8);
    memset(input + 8,':',1);
    memcpy(input + 9, payment_pin.c_str(), 6);
    memset(input + 15,':',1);
    input[16] = 0;

#ifdef DEBUG
    Serial.printf("Input: ");
    for(int i=0;(i<16);i++) {
      Serial.printf("%c",input[i]);
    }
    Serial.println();
#endif

    unsigned char output[128];

    byte sha256Result[32];
    mbedtls_md_context_t sha;
    mbedtls_md_init(&sha);
    mbedtls_md_setup(&sha,mbedtls_md_info_from_type(MBEDTLS_MD_SHA256),0);
    mbedtls_md_starts(&sha);
    mbedtls_md_update(&sha,(const unsigned char *)(input),16);
    mbedtls_md_finish(&sha,sha256Result);
    mbedtls_md_free(&sha);

#ifdef DEBUG
    Serial.printf("SHA256: ");
    for(int i=0;(i<32);i++) {
      Serial.printf("%02x",sha256Result[i]);
    }
    Serial.println();
#endif

    memcpy(input + 16, sha256Result, 32);

#ifdef DEBUG
    Serial.printf("Input: ");
    for(int i=0;(i<48);i++) {
      Serial.printf("%02x",input[i]);
    }
    Serial.println();
#endif

    mbedtls_aes_context aes;
    mbedtls_aes_setkey_enc( &aes, key, 128 );
    mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, 48, iv, input, output );
    mbedtls_aes_free(&aes);

#ifdef DEBUG
    Serial.printf("Encrypted: ");
    for(int i=0;(i<48);i++) {
      Serial.printf("%02x",output[i]);
    }
    Serial.println();
#endif


    String url = "https://";
    url += config.getLNbitsHost();
    url += "/partytap/api/v1/device/";
    url += config.getDeviceID();
    url += "/payment?encrypted=";
    for (int i=0;i<48;i++) {
      char str[3];
      sprintf(str, "%02x", (int)output[i]);
      url += str;
    }
    url += "&iv=";
    for (int i=0;i<16;i++) {
      char str[3];
      sprintf(str, "%02x", (int)iiv[i]);
      url += str;
    }
    

    byte *data = (byte *)calloc(strlen(url.c_str()) * 2, sizeof(byte));
    size_t len = 0;
    int res = convert_bits(data, &len, 5, (byte *)(url.c_str()), url.length(), 8, 1);
    char *charLnurl = (char *)calloc(url.length() * 2, sizeof(byte));
    bech32_encode(charLnurl, "lnurl", data, len);
#ifdef DEBUG
    Serial.println(charLnurl);
#endif

    // Update UI
    {
      const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
      
      lv_label_set_text(ui_LabelHeaderMain, "PAY FOR YOUR DRINK");
      lv_obj_set_x(ui_ButtonMainAbout, -70);
      lv_obj_set_x(ui_ButtonMainEnterPIN, 70);
      lv_obj_clear_flag(ui_ButtonMainEnterPIN,LV_OBJ_FLAG_HIDDEN);

      lv_obj_add_flag(ui_PanelMainMessage,LV_OBJ_FLAG_HIDDEN);
      lv_qrcode_update(ui_QrcodeLnurl, charLnurl, strlen(charLnurl));
      lv_obj_clear_flag(ui_QrcodeLnurl,LV_OBJ_FLAG_HIDDEN);
      lv_disp_load_scr(ui_ScreenMain);	
    }
    expireInvoiceTask.restartDelayed(TASK_SECOND * 60);
  }


}

void handlePaid(DynamicJsonDocument *doc) {
  const char *phash = (*doc)["payment_hash"].as<const char *>();

  if ( strcmp(phash,payment_hash.c_str()) != 0 ) {
#ifdef DEBUG
    Serial.println("Payment Hash not OK");
#endif
    return;
  }

  tap_payment_hash = payment_hash;
  payment_hash = "";

  expireInvoiceTask.disable();
  if ( sensact->isNFCAvailable() ) {
    checkNFCPaymentTask.disable();
  }

  tap_duration = (*doc)["payload"].as<int>();
  beerScreen();
}

void configureSwitches() {
  // hide the update button if versions are the same 
#define STR1(x)  #x
#define STR(x)  STR1(x)    
  if ( strcmp(productConfig.getServerVersion(),STR(FIRMWARE_VERSION)) != 0 ) {
    lv_obj_clear_flag(ui_ButtonConfigUpdate,LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(ui_ButtonConfigUpdate,LV_OBJ_FLAG_HIDDEN);
  }

  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    switch ( productConfig.getNumProducts() ) {
      case 0:
        lv_obj_add_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        break;
      case 1:
        lv_obj_set_x(ui_ButtonAboutOne, 0);
        lv_label_set_text(ui_LabelAboutOne, productConfig.getProduct(0)->getLabel());
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
        lv_label_set_text(ui_LabelAboutOne, productConfig.getProduct(0)->getLabel());
        lv_label_set_text(ui_LabelAboutTwo, productConfig.getProduct(1)->getLabel());
        break;
      case 3:
        lv_obj_clear_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_x(ui_ButtonAboutOne, -105);
        lv_obj_set_x(ui_ButtonAboutTwo, 0);
        lv_obj_set_x(ui_ButtonAboutThree, 105);
        lv_label_set_text(ui_LabelAboutOne, productConfig.getProduct(0)->getLabel());
        lv_label_set_text(ui_LabelAboutTwo, productConfig.getProduct(1)->getLabel());
        lv_label_set_text(ui_LabelAboutThree, productConfig.getProduct(2)->getLabel());
        break;
     default:
        break;
    }
  }

  // online 
  switch ( config.getOperatingMode() ) {
    case MODE_OFFLINE:
      if ( productConfig.getNumProducts() > 0 ) {
        setUIStatus(PSTR("Ready to Serve"),PSTR("Ready to Serve (offline)"));  
      }
      break;
    case MODE_ONLINE:
      if ( webSocket.isConnected() ) {
        setUIStatus(PSTR("Ready to Serve"),PSTR("Ready to Serve (online)"));  
      }    
      break;
    case MODE_AUTO:
      if ( productConfig.getNumProducts() > 0 ) {
        if ( webSocket.isConnected() ) {
          setUIStatus(PSTR("Ready to Serve"),PSTR("Ready to Serve (online)"));  
        } else {
          setUIStatus(PSTR("Ready to Serve"),PSTR("Ready to Serve (offline)"));  
        }
      }
      break;
  }
}

void changeOperatingMode(const char *mode) {
#ifdef DEBUG
  Serial.println("Changing operating mode");
  Serial.println(mode);
#endif

  if ( strncasecmp(mode,"online",6) == 0 ) {
    config.setOperatingMode(MODE_ONLINE);
    config.save();
  } else if ( strncasecmp(mode,"offline",7) == 0 ) {
    config.setOperatingMode(MODE_OFFLINE);
    config.save();
  } else if ( strncasecmp(mode,"auto",4) == 0 ) {
    config.setOperatingMode(MODE_AUTO);
    config.save();
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
#ifdef DEBUG
      Serial.printf("WebSocket event %d\n",type);
#endif
  switch(type) {
    case WStype_DISCONNECTED:      
#ifdef DEBUG
      Serial.println("WebSocket disconnected");
#endif

      switch ( config.getOperatingMode() ) {
        case MODE_ONLINE:
          if ( WiFi.status() != WL_CONNECTED ) {
            setUIStatus("WiFi Disconnected","WiFi Disconnected");
            webSocket.disableHeartbeat();
          } else {
            setUIStatus("WebSocket Disconnected","WebSocket Disconnected");  
          }                
          break;
        case MODE_OFFLINE:
          if ( productConfig.getNumProducts() > 0 ) {
            setUIStatus("Ready to serve","Ready to serve (offline)");           
          } else {
            setUIStatus("No products to serve","No products (offline)");      
          }
          break;
        case MODE_AUTO:
          if ( productConfig.getNumProducts() > 0 ) {
            setUIStatus("Ready to serve","Ready to serve (auto)");           
          } else if ( WiFi.status() != WL_CONNECTED ) {
            setUIStatus("WiFi Disconnected","WiFi Disconnected");
            webSocket.disableHeartbeat();
          } else {
            setUIStatus("WebSocket Disconnected","WebSocket Disconnected");  
          } 
          break;
      }               
      break;
    case WStype_CONNECTED:
      setUIStatus("WebSocket Connected 1","WebSocket Connected");
      break;
    case WStype_TEXT:
      {
        DynamicJsonDocument doc(2000);
        DeserializationError error = deserializeJson(doc, (char *)payload);
#ifdef DEBUG
        if ( error.code() !=  DeserializationError::Ok ) {
          Serial.println("Error in JSON parsing");
          return;
        }
#endif      
        // get the message type
        const char *event = doc["event"].as<const char *>();
#ifdef DEBUG
        Serial.printf("WS Event type = %s\n",event);
#endif
        if ( strcmp(event,STR_SWITCHES) == 0 ) {
#ifdef DEBUG
          Serial.println("Received switches");
#endif
          productConfig.parse(&doc);        
          productConfig.save();
          configureSwitches();
        } else if ( strcmp(event,STR_INVOICE) == 0 ) {
          showInvoice(&doc);
        } else if ( strcmp(event,"paid") == 0 ) {     
          setPanelMainMessage(PSTR("PAYMENT SUCCES"),3);
          handlePaid(&doc);
        } else if ( strcmp(event,"paymentfailed") == 0 ) {
          setPanelMainMessage("PAYMENT FAILED",3);
          checkNFCPaymentTask.restartDelayed(TASK_SECOND * 3);  
        } else if ( strcmp(event,"error") == 0 ) {
          setUIStatus("WebSocket error",doc["message"].as<const char *>());
        } else {
#ifdef DEBUG
          Serial.println(event);
#endif
        }
      }
      break;
    case WStype_PING:
    case WStype_PONG:
      break;    
    default:
#ifdef DEBUG
      Serial.printf("Unknown Websocket message of type: %d\n",type);
#endif
			break;
  }


}



void nfcReadCallback(int statusCode ) {
  switch ( statusCode ) {
    case SENSACT_NFC_CB_INCOMPATIBLE:
      setPanelMainMessage("INCOMPATIBLE CARD",3);
      break;
    case SENSACT_NFC_CB_NO_BYTES:
      setPanelMainMessage("MOVE CARD",3);
      break;
    case SENSACT_NFC_CB_NO_NTAG424:
      setPanelMainMessage("BAD CARD",3);
      break;  
    case SENSACT_NFC_CB_READING:
    case SENSACT_NFC_CB_NTAG424:
      setPanelMainMessage("READING CARD",1);
      break;  
    case SENSACT_NFC_CB_NOREAD:
      //setPanelMainMessage("NOTHING READ",3);
      break;
    case SENSACT_NFC_CB_UNAVAILABLE:
      setPanelMainMessage("NFC UNAVAILABLE",3);
      break;    
    case SENSACT_NFC_CB_READ_SUCCESS:
      setPanelMainMessage("CARD READ",3);
      break;
  }
}

void nfcReadSucces(int len,const char *data ) {


#ifdef DEBUG
  Serial.printf("NFC read succes %d\n",len);
#endif

  String wsmessage = "{\"event\":\"lnurlw\",\"payment_request\":\"";
  wsmessage += payment_request;
  wsmessage += "\",\"lnurlw\":\"";
  wsmessage += data;
  wsmessage += "\"}";
#ifdef DEBUG
  Serial.println(wsmessage);
#endif
  webSocket.sendTXT(wsmessage);
}


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);

  // add tasks to task scheduler
  taskScheduler.addTask(checkWiFiTask);
  taskScheduler.addTask(checkNFCPaymentTask);
  taskScheduler.addTask(checkUpdateTask);
  taskScheduler.addTask(hidePanelMainMessageTask);
  taskScheduler.addTask(expireInvoiceTask);
  taskScheduler.addTask(backToAboutPageTask);
  taskScheduler.addTask(beerTapProgressTask);

  // init filesystem and load config
  LittleFS.begin(true);
  config.load();

  smartdisplay_init();
  ui_init();

#ifdef BOARD_HAS_RGB_LED
  smartdisplay_led_set_rgb(0,0,0);
#endif
  smartdisplay_lcd_set_backlight(BB_TFT_INTENSITY);
  // set UI components from config

  // set the values of the sliders
  lv_slider_set_value(ui_SliderConfigServoClosed,config.getServoClose(),LV_ANIM_OFF);
  lv_slider_set_value(ui_SliderConfigServoOpen,config.getServoOpen(),LV_ANIM_OFF);
  lv_slider_set_value(ui_SliderConfigTapDuration,config.getTapDuration(),LV_ANIM_OFF);
  
  // set the current values of the labels
  lv_label_set_text_fmt(ui_LabelConfigServoClosed,"%d",config.getServoClose());
  lv_label_set_text_fmt(ui_LabelConfigServoOpen,"%d",config.getServoOpen());
  lv_label_set_text_fmt(ui_LabelConfigTapDuration,"%d",config.getTapDuration());

  // set wifi configuration and device id
  lv_textarea_set_text(ui_TextAreaConfigSSID,config.getWiFiSSID());
  lv_textarea_set_text(ui_TextAreaWifiPassword,config.getWiFiPWD());
  lv_textarea_set_text(ui_TextAreaConfigHost,config.getLNbitsHost());
  lv_textarea_set_text(ui_TextAreaConfigDeviceID,config.getDeviceID());
  lv_label_set_text(ui_LabelPINValue,"");

  xTaskCreatePinnedToCore (
    loop0,     // Function to implement the task
    "loop0",   // Name of the task
    20000,      // Stack size in bytes
    NULL,      // Task input parameter
    10,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

  // initialize I2C
#if defined(TAP_I2C_SCL) && defined(TAP_I2C_SDA) && defined (TAP_I2C_BUS)
  sensact = new Sensact(TAP_I2C_SDA, TAP_I2C_SCL,TAP_I2C_BUS);
  sensact->init();

  // search NFC sensor
  setUIStatus("Detecting NFC","Detecting NFC");
  sensact->initNFC();
    
  // search for I2C servo
#ifdef ESP32_3248S035C
#ifdef DEBUG
  Serial.println("Initialising servo");
#endif
  sensact->initServo(TAP_I2C_TAP_ADDRESS,TAP_I2C_SERVO_PIN);
  if ( sensact->isServoAvailable() ) {
#ifdef DEBUG
    Serial.println("Servo configured");
#endif
  } else if ( ! sensact->isNFCAvailable() ) {
#ifdef DEBUG
    Serial.println("Using conventional servo");
#endif
    sensact->initServo(TAP_SERVO_PIN);
  }
#else
  if ( ! sensact->initServo(TAP_I2C_TAP_ADDRESS,TAP_I2C_SERVO_PIN) ) {
    sensact->initServo(TAP_SERVO_PIN);
  }
#endif

#else
  sensact = new Sensact();
  sensact->init();
  sensact->initServo(TAP_SERVO_PIN);
#endif

  if (( sensact->isNFCAvailable()) && (sensact->isServoAvailable() )) {
    setUIStatus("Initialized with NFC","Initialized with NFC");
  } else if ( sensact->isServoAvailable() ) {
    setUIStatus("Initialized","Initialized");   
  } else if ( sensact->isNFCAvailable() ) {
    setUIStatus("Initialization failed","Initialization failed. NFC is available, no tap control");
  } else {
    setUIStatus("Initialization failed","Initialization failed. NFC unavailable, Tap unavailable");
  }
  
  beerClose();

  if ( productConfig.load() ) {
#ifdef DEBUG
    Serial.println("[main] products loaded from flash\n");
#endif    
    configureSwitches();
  }
  

  
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(3000);
  webSocket.enableHeartbeat(15000,4000,2);
    

  checkWiFiTask.restartDelayed(1000);
  checkUpdateTask.restartDelayed(5000);

  WiFi.begin(config.getWiFiSSID(),config.getWiFiPWD());
}

void checkNFCPayment() {
  sensact->readNFC(NFC_TIMEOUT,nfcReadCallback,nfcReadSucces);
}

void checkWiFi() {
  static bool bConnected = false;

  if ( bDoReconnect ) {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);  
    bDoReconnect = false;
    bConnected = false;
    webSocket.disableHeartbeat();
    webSocket.disconnect();    
    WiFi.disconnect();
    WiFi.begin(config.getWiFiSSID(),config.getWiFiPWD());
  }

  display_rssi();

  wl_status_t status = WiFi.status();
  switch ( status ) {
    case WL_CONNECTED:
      if ( bConnected == false ) {
        setUIStatus("Wi-Fi connected","Wi-Fi connected");
#ifdef DEBUG
        Serial.println("Connecting WebSocket");
#endif
        
        config_wspath = "/partytap/api/v1/ws/";
        config_wspath += config.getDeviceID();
        webSocket.disconnect();
        webSocket.beginSSL(config.getLNbitsHost(), 443, config_wspath);
        webSocket.enableHeartbeat(15000,4000,2);
        bConnected = true;
      }
      break;
    case WL_NO_SSID_AVAIL:
#ifdef DEBUG
      Serial.println("ERROR_CONFIG_SSID");
#endif
      switch ( config.getOperatingMode() ) {
        case MODE_ONLINE:
          setUIStatus("SSID not found","SSID not found");      
          break;
        case MODE_OFFLINE:
          if ( productConfig.getNumProducts() > 0 ) {
            setUIStatus("Ready to serve","Ready to serve (offline)");      
          } else {
            setUIStatus("No products to serve","No products (offline)");      
          }
          break;
        case MODE_AUTO:
          if ( productConfig.getNumProducts() > 0 ) {
            setUIStatus("Ready to serve","Ready to serve (auto)");      
          } else {
            setUIStatus("No products to server","No products (auto)");      
          }
          break;
      }
      break;
    case WL_CONNECTION_LOST:
#ifdef DEBUG
      Serial.println("CONNECTION LOST");
#endif
      break;
    case WL_IDLE_STATUS:
#ifdef DEBUG
      Serial.println("W_IDLE_STATUS");
#endif
      break;
    case WL_DISCONNECTED:
      setUIStatus("Wi-Fi disconnected","Wi-Fi disconnected");
#ifdef DEBUG
      Serial.println("WL_DISCONNECTED");
#endif
      break;
    case WL_NO_SHIELD:
#ifdef DEBUG
      Serial.println("Wi-Fi device not initialized");
#endif
      break;
    case WL_CONNECT_FAILED:
#ifdef DEBUG
      Serial.println("WL_CONNECT_FAILED");
#endif
      break;
    default:
#ifdef DEBUG
      Serial.printf("Unknown WiFi state %d\n",status);
#endif
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

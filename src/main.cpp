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

#define STR1(x)  #x
#define STR(x)  STR1(x)    

std::recursive_mutex lvgl_mutex;

#define STR_INVOICE    PSTR("invoice")
#define STR_SAT        PSTR("sat")
#define STR_SWITCHES   PSTR("switches")
#define STR_RESTARTING PSTR("RESTARTING")


// config variables
TapConfig tapConfig;
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
void doFirmwareUpdate();
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
Task checkUpdateTask(TASK_SECOND, TASK_FOREVER, &doFirmwareUpdate);
Task checkNFCPaymentTask(TASK_IMMEDIATE, TASK_FOREVER, &checkNFCPayment);





void setPanelMainMessage(const char *s,int timeout)  {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_label_set_text(ui_LabelMainMessage, s);  
  lv_obj_clear_flag(ui_PanelMainMessage, LV_OBJ_FLAG_HIDDEN);    
  hidePanelMainMessageTask.restartDelayed(TASK_SECOND * timeout);
}

void firmwareUpdateFinished() {
  const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
  lv_label_set_text(ui_LabelAboutMessage, STR_RESTARTING);
}

void firmwareUpdateProgress(int cur, int total) {
  static char message[25];
  snprintf_P(message, sizeof(message), PSTR("UPDATE PROGRESS %d%%"), 100 * cur / total);
  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_label_set_text(ui_LabelAboutMessage, message);
  }
}

void firmwareUpdateError(int err) {
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

void startFirmwareUpdate() {
  {

    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);

    lv_obj_del(ui_ScreenBierFlowing);
    lv_obj_del(ui_ScreenConfig);
    lv_obj_del(ui_ScreenPin);
    lv_obj_del(ui_ScreenMain);
  }

  delay(5000);

  {
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
  }  
  bDoUpdate = true;
  checkUpdateTask.restartDelayed(2000);
}

bool isReadyToServe() {
  if ( productConfig.getNumProducts() == 0 ) {
    return false;    
  }
  if (( tapConfig.getPaymentMode() == PAYMENT_MODE_ONLINE) && ( webSocket.isConnected() )) {
    return true;    
  }
  return false;
}

void doFirmwareUpdate() {
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


  httpUpdate.onEnd(firmwareUpdateFinished);
  httpUpdate.onProgress(firmwareUpdateProgress);
  httpUpdate.onError(firmwareUpdateError);
  httpUpdate.rebootOnUpdate(true);

#define FIRMWARE_HOST "firmware.bitcointaps.com"
  snprintf_P(firmware_path, sizeof(firmware_path), PSTR("/partytap/ESP32_3248S035C/%s/firmware_%s.bin"), productConfig.getServerVersion(), productConfig.getServerBranding());

  t_httpUpdate_return ret = httpUpdate.update(client, FIRMWARE_HOST, 443, firmware_path);
  
  if ( ret == HTTP_UPDATE_FAILED ) {
#ifdef DEBUG
    Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
#endif
    firmwareUpdateError(httpUpdate.getLastError());
    delay(10000);
    ESP.restart();
    return;
  }
}

void tapOpen(int i) {
  switch ( tapConfig.getControlMode() ) {
    case CONTROL_MODE_SERVO_TIME:
      sensact->writeServo(i);
      break;
    case CONTROL_MODE_RELAY_TIME:
      sensact->writeRelay(HIGH);
      break;
    case CONTROL_MODE_I2C_SERVO_TICKS:
    case CONTROL_MODE_I2C_SERVO_TIME:
      sensact->writeI2CServo(i);
      break;    
    case CONTROL_MODE_I2C_RELAY_TICKS:
    case CONTROL_MODE_I2C_RELAY_TIME:
      sensact->writeI2CRelay(HIGH);
      break;    
    case CONTROL_MODE_NONE:
    default:
      return;
  }
}

void tapClose(int i) {
  switch ( tapConfig.getControlMode() ) {
    case CONTROL_MODE_SERVO_TIME:
      sensact->writeServo(i);
      break;
    case CONTROL_MODE_RELAY_TIME:
      sensact->writeRelay(HIGH);
      break;
    case CONTROL_MODE_I2C_SERVO_TICKS:
    case CONTROL_MODE_I2C_SERVO_TIME:
      sensact->writeI2CServo(i);
      break;    
    case CONTROL_MODE_I2C_RELAY_TICKS:
    case CONTROL_MODE_I2C_RELAY_TIME:
      sensact->writeI2CRelay(HIGH);
      break;    
    case CONTROL_MODE_NONE:
    default:
      return;
  }
}

void tapStop() {
  tapClose(tapConfig.getServoClose());
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
    tapClose(tapConfig.getServoClose());
    notifyOrderFulfilled();
    lv_obj_add_flag(ui_BarBierProgress,LV_OBJ_FLAG_HIDDEN);
    backToAboutPageTask.restartDelayed(TASK_SECOND * 3);
  }
} 

void beerScreen()
{
  payment_pin = "";
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
	tapOpen(tapConfig.getServoOpen());    
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
  expireInvoiceTask.restartDelayed(TASK_SECOND * 120);
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

  if ( productConfig.getProduct(selectedItem)->getAmount() == 0 ) {
    beerScreen();
    return;
  }
  
  // send request to create invoice
  if ((( tapConfig.getPaymentMode() == PAYMENT_MODE_AUTO ) || ( tapConfig.getPaymentMode() == PAYMENT_MODE_ONLINE)) && webSocket.isConnected() ) {
    String wsmessage = PSTR("{\"event\":\"createinvoice\",\"switch_id\":\"");
    wsmessage +=  productConfig.getProduct(selectedItem)->getSwitchID();
    wsmessage += PSTR("\"}");

    if ( webSocket.sendTXT(wsmessage) ) {
      const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
      lv_label_set_text(ui_LabelAboutMessage, PSTR("CREATING INVOICE"));
      lv_obj_clear_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    }
  } else if (( tapConfig.getPaymentMode() == PAYMENT_MODE_OFFLINE ) || ( tapConfig.getPaymentMode() == PAYMENT_MODE_AUTO )) {
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

    for(int i=0;(i<PAYMENT_PIN_LEN);i++) {
      payment_pin += String(random(10));
    }
    payment_pin[PAYMENT_PIN_LEN] = 0;

    unsigned char input[128];
    memcpy(input, productConfig.getProduct(selectedItem)->getSwitchID(),8);
    memset(input + 8,':',1);
    memcpy(input + 9, payment_pin.c_str(), PAYMENT_PIN_LEN);
    memset(input + 9 + PAYMENT_PIN_LEN,':',1);
    input[9 + PAYMENT_PIN_LEN + 1] = 0;

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
    url += tapConfig.getLNbitsHost();
    url += "/partytap/api/v1/device/";
    url += tapConfig.getDeviceID();
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
    expireInvoiceTask.restartDelayed(TASK_SECOND * 120);
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

void hidePaymentButtons()
{
  Serial.println("hidePaymentButtons");
  {
    const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
    lv_obj_add_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
  }
}

void configureSwitches() {
  hidePaymentButtons();

  if ( isReadyToServe() == false ) {
    return;
  }

  switch ( productConfig.getNumProducts() ) {
    case 1:
      {
        const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
        lv_obj_set_x(ui_ButtonAboutOne, 0);
        lv_label_set_text(ui_LabelAboutOne, productConfig.getProduct(0)->getLabel());
        lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
      }
      break;
    case 2:
      {
        const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
        lv_obj_clear_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_x(ui_ButtonAboutOne, -60);
        lv_obj_set_x(ui_ButtonAboutTwo, 60);
        lv_label_set_text(ui_LabelAboutOne, productConfig.getProduct(0)->getLabel());
        lv_label_set_text(ui_LabelAboutTwo, productConfig.getProduct(1)->getLabel());
      }
      break;
    case 3:
      {
        const std::lock_guard<std::recursive_mutex> lock(lvgl_mutex);
        lv_obj_clear_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_x(ui_ButtonAboutOne, -105);
        lv_obj_set_x(ui_ButtonAboutTwo, 0);
        lv_obj_set_x(ui_ButtonAboutThree, 105);
        lv_label_set_text(ui_LabelAboutOne, productConfig.getProduct(0)->getLabel());
        lv_label_set_text(ui_LabelAboutTwo, productConfig.getProduct(1)->getLabel());
        lv_label_set_text(ui_LabelAboutThree, productConfig.getProduct(2)->getLabel());
      }
      break;
    default:
      break;
  } 
}



void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:      
#ifdef DEBUG
      Serial.println("WStype_DISCONNECTED");
#endif
      if ( ! isReadyToServe() ) {
        hidePaymentButtons();
      }               
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
        } else {
#ifdef DEBUG
          Serial.println(event);
#endif
        }
      }
      break;
    default:
#ifdef DEBUG
      Serial.printf("Received Websocket message of type: %d\n",type);
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

void restartTap() {
  ESP.restart();
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
  tapConfig.load();

  smartdisplay_init();
  ui_init();

#ifdef BOARD_HAS_RGB_LED
  smartdisplay_led_set_rgb(0,0,0);
#endif


  xTaskCreatePinnedToCore (
    loop0,     // Function to implement the task
    "loop0",   // Name of the task
    20000,      // Stack size in bytes
    NULL,      // Task input parameter
    10,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

  sensact = new Sensact();
  switch ( tapConfig.getControlMode() ) {
    case CONTROL_MODE_NONE:
      break;
    case CONTROL_MODE_SERVO_TIME:
      sensact->initServo(TAP_SERVO_PIN);    
      break;
    case CONTROL_MODE_RELAY_TIME:
      sensact->initRelay(TAP_SERVO_PIN);
      break;
    case CONTROL_MODE_I2C_SERVO_TIME:
      sensact->initI2C(TAP_I2C_SDA, TAP_I2C_SCL,TAP_I2C_BUS);    
      sensact->initI2CServo(TAP_I2C_TAP_ADDRESS,TAP_I2C_SERVO_PIN);
      sensact->initNFC();
      break;
    case CONTROL_MODE_I2C_RELAY_TIME:
      sensact->initI2C(TAP_I2C_SDA, TAP_I2C_SCL,TAP_I2C_BUS);    
      sensact->initI2CRelay(TAP_I2C_TAP_ADDRESS,TAP_I2C_SERVO_PIN);
      sensact->initNFC();
      break;
    default:
      break;
  }

  tapClose(tapConfig.getServoClose());

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

  WiFi.begin(tapConfig.getWiFiSSID(),tapConfig.getWiFiPWD());
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
    WiFi.begin(tapConfig.getWiFiSSID(),tapConfig.getWiFiPWD());
  }


  wl_status_t status = WiFi.status();
  switch ( status ) {
    case WL_CONNECTED:
      if ( bConnected == false ) {
#ifdef DEBUG
        Serial.println("Connecting WebSocket");
#endif
        
        config_wspath = "/partytap/api/v1/ws/";
        config_wspath += tapConfig.getDeviceID();
        webSocket.disconnect();
        webSocket.beginSSL(tapConfig.getLNbitsHost(), 443, config_wspath);
        webSocket.enableHeartbeat(15000,4000,2);
        bConnected = true;
      }
      break;
    case WL_NO_SSID_AVAIL:
#ifdef DEBUG
      Serial.println("ERROR_CONFIG_SSID");
#endif
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

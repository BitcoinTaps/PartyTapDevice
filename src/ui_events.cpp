#include "ui.h"
#include "partytap.h"
#include <WString.h>

String entered_pin = "";

void addToPIN(int digit) {
	if (( payment_pin.length() > 0 ) && ( entered_pin.length() >= payment_pin.length())) {
		// return if longer than the payment_pin length (if there is a payment pin)
		return;
	}
	if ( entered_pin.length() >= 6 ) {
		// return if longer than th config pin length
		return;
	}
    entered_pin += digit;

    String hidePIN = "";
    for(int i=0;(i<entered_pin.length());i++) {
      hidePIN += "*";
    }
    lv_label_set_text(ui_LabelPINValue,hidePIN.c_str());
}

void ButtonPinNumberClicked(lv_event_t * e)
{
	// Your code here	
	addToPIN(int(e->user_data));
}


void ButtonPinCancelClicked(lv_event_t * e)
{
	// Your code here
	if ( entered_pin.length() == 0 ) {
		ui_ScreenAbout_screen_init();
		configureSwitches();
		lv_disp_load_scr(ui_ScreenAbout);		
		lv_obj_del(ui_ScreenPin);
		ui_ScreenPin = NULL;
	}
	entered_pin = "";
	lv_label_set_text(ui_LabelPINValue,"ENTER PIN");
}

void ButtonPinOKClicked(lv_event_t * e)
{
	// if the config PIN is entered, go to config
	if ( strcmp(entered_pin.c_str(),tapConfig.getPIN()) == 0 ) {
		entered_pin = "";  
		ui_ScreenAdmin_screen_init();
		lv_label_set_text_fmt(ui_LabelAdminServerVersion,"Server version: %s",productConfig.getServerVersion());
		lv_label_set_text_fmt(ui_LabelAdminBranding,"Server Branding: %s",productConfig.getServerBranding());
		lv_disp_load_scr(ui_ScreenAdmin);
		lv_obj_del(ui_ScreenPin);
  		ui_ScreenPin = NULL;
		return;
	}

	if ((payment_pin.length() == PAYMENT_PIN_LEN) && (strncmp(entered_pin.c_str(),payment_pin.c_str(),PAYMENT_PIN_LEN) == 0 )) {
#ifdef DEBUG
    	Serial.println("[ButtonPinOKClicked] PIN correct");
#endif
		entered_pin = "";
    	payment_pin = "";

  		ui_ScreenBierFlowing_screen_init();
  		lv_obj_add_flag(ui_BarBierProgress,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(ui_ButtonBierStart,LV_OBJ_FLAG_HIDDEN);
  		lv_bar_set_value(ui_BarBierProgress,0,LV_ANIM_OFF);
		lv_disp_load_scr(ui_ScreenBierFlowing);	
  		lv_obj_del(ui_ScreenPin);
  		ui_ScreenPin = NULL;
		
		return;
  	}
 
#ifdef DEBUG
	Serial.printf("[ButtonPinOKClicked] entered_pin = '%s'\n",entered_pin);
	Serial.printf("[ButtonPinOKClicked] payment_pin = '%s'\n",payment_pin);
#endif
	entered_pin = "";
 	lv_label_set_text(ui_LabelPINValue,"PIN INCORRECT");    
}

void ButtonConfigDoneClicked(lv_event_t * e)
{
	char buf[20];

	lv_dropdown_get_selected_str(ui_DropdownConfigPaymentMode, buf, sizeof(buf));
  	if ( strncasecmp(buf,"online",6) == 0 ) {
    	tapConfig.setPaymentMode(PAYMENT_MODE_ONLINE);
  	} else if ( strncasecmp(buf,"offline",7) == 0 ) {
    	tapConfig.setPaymentMode(PAYMENT_MODE_OFFLINE);
  	} else if ( strncasecmp(buf,"auto",4) == 0 ) {
    	tapConfig.setPaymentMode(PAYMENT_MODE_AUTO);
  	}

	lv_dropdown_get_selected_str(ui_DropdownConfigControlMode, buf, sizeof(buf));
	if ( strncasecmp(buf,"Servo, Time",11) == 0 ) {
    	tapConfig.setControlMode(CONTROL_MODE_SERVO_TIME);
  	} else if ( strncasecmp(buf,"Relay, Time",11) == 0 ) {
    	tapConfig.setControlMode(CONTROL_MODE_RELAY_TIME);
  	} else if ( strncasecmp(buf,"I2C Servo, Time",15) == 0 ) {
    	tapConfig.setControlMode(CONTROL_MODE_I2C_SERVO_TIME);
  	} else if ( strncasecmp(buf,"I2C_Relay, Time",15) == 0 ) {
    	tapConfig.setControlMode(CONTROL_MODE_I2C_RELAY_TIME);
  	} else if ( strncasecmp(buf,"I2C Servo, Ticks",16) == 0 ) {
    	tapConfig.setControlMode(CONTROL_MODE_I2C_SERVO_TICKS);
  	} else if ( strncasecmp(buf,"I2C_Relay, Ticks",16) == 0 ) {
    	tapConfig.setControlMode(CONTROL_MODE_I2C_RELAY_TICKS);
  	} else {
    	tapConfig.setControlMode(CONTROL_MODE_NONE);
 	}

	// make config persistemtt
	const char *ssid = lv_textarea_get_text(ui_TextAreaConfigSSID);
 	tapConfig.setWiFiSSID(ssid);

	const char *pwd = lv_textarea_get_text(ui_TextAreaConfigWifiPassword);
  	tapConfig.setWiFiPWD(pwd);

	const char *deviceid = lv_textarea_get_text(ui_TextAreaConfigDeviceID);
  	tapConfig.setDeviceID(deviceid);

	const char *lnbitshost = lv_textarea_get_text(ui_TextAreaConfigLNbitsHost);
  	tapConfig.setLNbitsHost(lnbitshost);

	
	int32_t servoClosed = atoi(lv_textarea_get_text(ui_TextAreaConfigServoClosed));
 	tapConfig.setServoClose(servoClosed);

	int32_t servoOpen = atoi(lv_textarea_get_text(ui_TextAreaConfigServoOpen));
  	tapConfig.setServoOpen(servoOpen);
	
	tapConfig.save();

	lv_obj_del(ui_ScreenConfig);

	restartTap();
}

void ButtonOKPINClicked(lv_event_t * e)
{
	// Your code here
	const char *currentPIN = lv_textarea_get_text(ui_TextAreaConfigPINCurrent);
	const char *newPIN = lv_textarea_get_text(ui_TextAreaConfigPINNew);
	const char *repeatPIN = lv_textarea_get_text(ui_TextAreaConfigPINRepeat);

	if ( strcmp(tapConfig.getPIN(),currentPIN) != 0 ) {	
		lv_label_set_text(ui_LabelConfigPINMessage,"Current PIN incorrect");
		return;
	}

	if ( strlen(newPIN) != 6 ) {
		lv_label_set_text(ui_LabelConfigPINMessage,"PIN must be 6 characters");
		return;	
	}

	if ( strncmp(newPIN,repeatPIN,6) != 0 ) {
		lv_label_set_text(ui_LabelConfigPINMessage,"New PIN not equal");
		return;	
	}

	tapConfig.setPIN(newPIN);
	tapConfig.save();

	// Your code here
	lv_textarea_set_text(ui_TextAreaConfigPINCurrent,"");
	lv_textarea_set_text(ui_TextAreaConfigPINNew,"");
	lv_textarea_set_text(ui_TextAreaConfigPINRepeat,"");
	lv_label_set_text(ui_LabelConfigPINMessage,"");
	lv_obj_add_flag(ui_PanelConfigPIN,LV_OBJ_FLAG_HIDDEN);
}

void ButtonCancelPINClicked(lv_event_t * e)
{
	// Your code here
	lv_textarea_set_text(ui_TextAreaConfigPINCurrent,"");
	lv_textarea_set_text(ui_TextAreaConfigPINNew,"");
	lv_textarea_set_text(ui_TextAreaConfigPINRepeat,"");
	lv_label_set_text(ui_LabelConfigPINMessage,"");
	lv_obj_add_flag(ui_PanelConfigPIN,LV_OBJ_FLAG_HIDDEN);
}

void ButtonConfigServoCloseClicked(lv_event_t * e)
{
	int32_t servoClosed = atoi(lv_textarea_get_text(ui_TextAreaConfigServoClosed));
	tapClose(servoClosed);
}

void ButtonConfigServoOpenClicked(lv_event_t * e)
{
	int32_t servoOpen = atoi(lv_textarea_get_text(ui_TextAreaConfigServoOpen));
	tapOpen(servoOpen);
}

void ButtonConfigCancelClicked(lv_event_t * e)
{
	ui_ScreenAdmin_screen_init();
	lv_label_set_text_fmt(ui_LabelAdminServerVersion,"Server version: %s",productConfig.getServerVersion());
	lv_label_set_text_fmt(ui_LabelAdminBranding,"Server Branding: %s",productConfig.getServerBranding());
	lv_disp_load_scr(ui_ScreenAdmin);
	lv_obj_del(ui_ScreenConfig);
	ui_ScreenConfig = NULL;
}

void ButtonConfigUpdateClicked(lv_event_t * e)
{
	ui_ScreenAbout_screen_init();
	lv_obj_set_y(ui_PanelAboutMessage, 120);
    lv_label_set_text(ui_LabelAboutMessage, PSTR("UPDATING FIRMWARE"));
    lv_obj_clear_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_LabelAboutStatus,LV_OBJ_FLAG_HIDDEN);	
    lv_disp_load_scr(ui_ScreenAbout);	  	
	lv_obj_del(ui_ScreenConfig);
	ui_ScreenConfig = NULL;
	startFirmwareUpdate();
}


void ButtonScreenBierFlowingClicked(lv_event_t * e)
{
#ifdef DEBUG
	Serial.println("[ButtonScreenBeerFlowingClicked]");
#endif
	tapStop();
}


void ButtonBierStartClicked(lv_event_t *e ) 
{
	beerStart();
}

void ButtonAboutOneClicked(lv_event_t *e) 
{
	wantBierClicked(0);
}

void ButtonAboutTwoClicked(lv_event_t *e) 
{
	wantBierClicked(1);
}

void ButtonAboutThreeClicked(lv_event_t *e) 
{
	wantBierClicked(2);
}

void ButtonMainBackClicked(lv_event_t *e) {
#ifdef DEBUG
	Serial.println("[ButtonMainBackClicked]");
#endif
	expireInvoice();
	ui_ScreenAbout_screen_init();
    lv_obj_add_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);
    configureSwitches();
    lv_disp_load_scr(ui_ScreenAbout);	  
    lv_obj_del(ui_ScreenMain);
	ui_ScreenMain = NULL;
}

void ButtonMainEnterPINClicked(lv_event_t *e) {
#ifdef DEBUG
	Serial.println("[ButtonMainEnterPINClicked]");
#endif
    entered_pin = "";
	ui_ScreenPin_screen_init();
    lv_label_set_text(ui_LabelPINValue,"ENTER PIN");
    lv_disp_load_scr(ui_ScreenPin);	  
	lv_obj_del(ui_ScreenMain);
	ui_ScreenMain = NULL;
}




void PanelAboutHeaderClicked(lv_event_t *e) {
	// move from About to PIN Screen
#ifdef DEBUG
	Serial.println("[PanelAboutHeaderClicked]");
#endif
	expireInvoice();
	entered_pin = "";
	payment_pin = "";
	ui_ScreenPin_screen_init();
    lv_label_set_text(ui_LabelPINValue,"ENTER PIN");
    lv_disp_load_scr(ui_ScreenPin);	  
	lv_obj_del(ui_ScreenAbout);
	ui_ScreenAbout = NULL;
}

// navigate from admin screen to config screen
void ButtonAdminConfigClicked(lv_event_t *e) {
#ifdef DEBUG
	Serial.println("[ButtonAdminConfigClicked]");
#endif	
	char servo_text[10];
	ui_ScreenConfig_screen_init();
    lv_textarea_set_text(ui_TextAreaConfigSSID,tapConfig.getWiFiSSID());
    lv_textarea_set_text(ui_TextAreaConfigWifiPassword,tapConfig.getWiFiPWD());
    lv_textarea_set_text(ui_TextAreaConfigLNbitsHost,tapConfig.getLNbitsHost());
    lv_textarea_set_text(ui_TextAreaConfigDeviceID,tapConfig.getDeviceID());
    snprintf_P(servo_text, sizeof(servo_text), PSTR("%d"), tapConfig.getServoClose());
    lv_textarea_set_text(ui_TextAreaConfigServoClosed,servo_text);
    snprintf_P(servo_text, sizeof(servo_text), PSTR("%d"), tapConfig.getServoOpen());
    lv_textarea_set_text(ui_TextAreaConfigServoOpen,servo_text);
    lv_dropdown_set_selected(ui_DropdownConfigPaymentMode,tapConfig.getPaymentMode());
    lv_dropdown_set_selected(ui_DropdownConfigControlMode,tapConfig.getControlMode());
  	lv_disp_load_scr(ui_ScreenConfig);	
	lv_obj_del(ui_ScreenAdmin);
	ui_ScreenAdmin = NULL;
}

// Navigate from Admin Screen to About screen
void ButtonAdminCancelClicked(lv_event_t *e) {
#ifdef DEBUG
	Serial.println("[ButtonAdminCancelClicked]");
#endif	
	ui_ScreenAbout_screen_init();
	configureSwitches();	
	lv_disp_load_scr(ui_ScreenAbout);
	lv_obj_del(ui_ScreenAdmin);
	ui_ScreenAdmin = NULL;
}

// Tap Open Click on Admin screen
void ButtonAdminOpenClicked(lv_event_t *)
{
#ifdef DEBUG
	Serial.println("[ButtonAdminOpenClicked]");
#endif
	tapStart();
}

// Tap Close Click on Admin screen
void ButtonAdminCloseClicked(lv_event_t *)
{
#ifdef DEBUG
	Serial.println("[ButtonAdminCloseClicked]");
#endif
	tapStop();
}

// Free Clicked on Admin screen
void ButtonAdminFreeClicked(lv_event_t *)
{
#ifdef DEBUG
	Serial.println("[ButtonAdminFreeClicked]");
#endif
	freeTap = true;
	ui_ScreenAbout_screen_init();
	configureSwitches();	
	lv_disp_load_scr(ui_ScreenAbout);
	lv_obj_del(ui_ScreenAdmin);
	ui_ScreenAdmin = NULL;
}


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
		lv_disp_load_scr(ui_ScreenAbout);		
	}
	entered_pin = "";
	lv_label_set_text(ui_LabelPINValue,"ENTER PIN");
}




void ButtonPinOKClicked(lv_event_t * e)
{
	// Your code here
	handlePINResult(entered_pin.c_str());
	entered_pin = "";
}

void ButtonConfigDoneClicked(lv_event_t * e)
{
	char buf[20];

	const char *ssid = lv_textarea_get_text(ui_TextAreaConfigSSID);
	const char *pwd = lv_textarea_get_text(ui_TextAreaConfigWifiPassword);
	const char *deviceid = lv_textarea_get_text(ui_TextAreaConfigDeviceID);
	const char *cfgserver = lv_textarea_get_text(ui_TextAreaConfigLNbitsHost);
	
	int32_t servoClosed = atoi(lv_textarea_get_text(ui_TextAreaConfigServoClosed));
	int32_t servoOpen = atoi(lv_textarea_get_text(ui_TextAreaConfigServoOpen));

	lv_dropdown_get_selected_str(ui_DropdownConfigPaymentMode, buf, sizeof(buf));
	setPaymentMode(buf);

	lv_dropdown_get_selected_str(ui_DropdownConfigControlMode, buf, sizeof(buf));
	setControlMode(buf);


	saveTuning(servoClosed,servoOpen);	
	connectPartyTap(ssid,pwd,deviceid,cfgserver);

	ESP.restart();
}

void ButtonOKPINClicked(lv_event_t * e)
{
	// Your code here
	const char *currentPIN = lv_textarea_get_text(ui_TextAreaConfigPINCurrent);
	const char *newPIN = lv_textarea_get_text(ui_TextAreaConfigPINNew);
	const char *repeatPIN = lv_textarea_get_text(ui_TextAreaConfigPINRepeat);

	if ( checkConfigPIN(currentPIN) == false ) {	
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

	
	updatePIN(newPIN);

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

void ButtonConfigCloseClicked(lv_event_t * e)
{
	int32_t servoClosed = atoi(lv_textarea_get_text(ui_TextAreaConfigServoClosed));
	beerClose(servoClosed);
}

void ButtonConfigOpenClicked(lv_event_t * e)
{
	int32_t servoOpen = atoi(lv_textarea_get_text(ui_TextAreaConfigServoOpen));
	beerOpen(servoOpen);
}

void ButtonConfigCancelClicked(lv_event_t * e)
{
}

void ButtonScreenBierFlowingClicked(lv_event_t * e)
{
	beerStop();
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

void ButtonFreeClicked(lv_event_t *e)
{
	freeBeerClicked();
}

void ButtonMainBackClicked(lv_event_t *e) {
	backToAboutPage();
}

void ButtonMainEnterPINClicked(lv_event_t *e) {
	entered_pin = "";
	toConfigPage();
}


void ButtonAboutConfigClicked(lv_event_t *e) {
	entered_pin = "";
	payment_pin = "";
	toConfigPage();
}

void ButtonConfigFirmwareUpdateClicked(lv_event_t * e) {
	doUpdate();
}


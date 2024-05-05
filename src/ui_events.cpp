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

void ButtonPinOneClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(1);
}

void ButtonPinTwoClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(2);
}

void ButtonPinThreeClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(3);
}

void ButtonPinFourClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(4);
}

void ButtonPinFiveClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(5);
}

void ButtonPinSixClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(6);
}

void ButtonPinSevenClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(7);
}

void ButtonPinEightClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(8);
}

void ButtonPinNineClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(9);
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

void ButtonPinZeroClicked(lv_event_t * e)
{
	// Your code here
	addToPIN(0);
}

void DropdownConfigOperatingModeChanged(lv_event_t *e) 
{
	char buf[20];
	lv_dropdown_get_selected_str(ui_DropdownConfigOperatingMode, buf, sizeof(buf));
	changeOperatingMode(buf);
}

void ButtonPinOKClicked(lv_event_t * e)
{
	// Your code here
	handlePINResult(entered_pin.c_str());
	entered_pin = "";
}

void ButtonConfigTunerClicked(lv_event_t * e)
{
	lv_disp_load_scr(ui_ScreenConfigAdvanced);
	if ( false ) {
		beginOTA();
		/// UNREACHABLE CODE
	}
}

void ButtonConfigConnectClicked(lv_event_t * e)
{
	// Your code here
	const char *ssid = lv_textarea_get_text(ui_TextAreaConfigSSID);
	const char *pwd = lv_textarea_get_text(ui_TextAreaWifiPassword);
	const char *deviceid = lv_textarea_get_text(ui_TextAreaConfigDeviceID);
	const char *cfgserver = lv_textarea_get_text(ui_TextAreaConfigHost);
	connectPartyTap(ssid,pwd,deviceid,cfgserver);
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

void ButtoCancelPINClicked(lv_event_t * e)
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
	beerClose();
}

void ButtonConfigOpenClicked(lv_event_t * e)
{
	beerOpen();
}

void ButtonConfigSaveClicked(lv_event_t * e)
{
	int32_t servoClosed = lv_slider_get_value(ui_SliderConfigServoClosed);
	int32_t servoOpen = lv_slider_get_value(ui_SliderConfigServoOpen);
	int32_t tapDuration = lv_slider_get_value(ui_SliderConfigTapDuration);
	int32_t backlight = lv_slider_get_value(ui_SliderConfigBacklight);
	saveTuning(servoClosed,servoOpen,tapDuration, backlight);	
}

void ButtonScreenBierFlowingClicked(lv_event_t * e)
{
	beerClose();
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
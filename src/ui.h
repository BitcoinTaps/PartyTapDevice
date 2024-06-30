#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

extern lv_obj_t * ui_ScreenAbout;
extern lv_obj_t * ui_PanelHeaderAbout;
extern lv_obj_t * ui_LabelAboutHeader;
extern lv_obj_t * ui_ImageAbout;
extern lv_obj_t * ui_LabelAboutStatus;
extern lv_obj_t * ui_ButtonAboutOne;
extern lv_obj_t * ui_ButtonAboutTwo;
extern lv_obj_t * ui_ButtonAboutThree;
extern lv_obj_t * ui_LabelAboutOne;
extern lv_obj_t * ui_LabelAboutTwo;
extern lv_obj_t * ui_LabelAboutThree;
extern lv_obj_t * ui_PanelAboutMessage;
extern lv_obj_t * ui_LabelAboutMessage;
void ui_event_ButtonAboutConfig(lv_event_t * e);
void ui_event_ButtonAboutOne(lv_event_t * e);
void ui_event_ButtonAboutTwo(lv_event_t * e);
void ui_event_ButtonAboutThree(lv_event_t * e);
extern lv_obj_t * ui_ScreenMain;
extern lv_obj_t * ui_PanelHeaderMain;
extern lv_obj_t * ui_LabelHeaderMain;
void ui_event_ButtonMainAbout(lv_event_t * e);
extern lv_obj_t * ui_ButtonMainAbout;
void ui_event_ButtonMainEnterPIN(lv_event_t * e);
extern lv_obj_t * ui_ButtonMainEnterPIN;
extern lv_obj_t * ui_LabelMainEnterPIN;
extern lv_obj_t * ui_QrcodeLnurl;
extern lv_obj_t * ui_Label18;
extern lv_obj_t * ui_ScreenPin;
extern lv_obj_t * ui_LabelPINValue;
extern lv_obj_t * ui_PanelPin;
extern lv_obj_t * ui_LabelPinPanel;

extern lv_obj_t * ui_PanelMainMessage;
extern lv_obj_t * ui_LabelMainMessage;

void ui_event_ButtonNumber(lv_event_t * e);
extern lv_obj_t * ui_ButtonPin0;
extern lv_obj_t * ui_LabelPin0;
extern lv_obj_t * ui_ButtonPin1;
extern lv_obj_t * ui_LabelPin0;
extern lv_obj_t * ui_ButtonPin2;
extern lv_obj_t * ui_LabelPin2;
extern lv_obj_t * ui_ButtonPin3;
extern lv_obj_t * ui_LabelPin3;
extern lv_obj_t * ui_ButtonPin4;
extern lv_obj_t * ui_LabelPin4;
extern lv_obj_t * ui_ButtonPin5;
extern lv_obj_t * ui_LabelPin5;
extern lv_obj_t * ui_ButtonPin6;
extern lv_obj_t * ui_LabelPin6;
extern lv_obj_t * ui_ButtonPin7;
extern lv_obj_t * ui_LabelPin7;
extern lv_obj_t * ui_ButtonPin8;
extern lv_obj_t * ui_LabelPin8;
extern lv_obj_t * ui_ButtonPin9;
extern lv_obj_t * ui_LabelPin9;
void ui_event_ButtonPINCancel(lv_event_t * e);
extern lv_obj_t * ui_ButtonPINCancel;
extern lv_obj_t * ui_LabelPINCancel;
void ui_event_ButtonPinOK(lv_event_t * e);
extern lv_obj_t * ui_ButtonPinOK;
extern lv_obj_t * ui_LabelPinOK;
extern lv_obj_t * ui_ScreenConfig;
extern lv_obj_t * ui_PanelConfig;
extern lv_obj_t * ui_LabelConfigPanel;
extern lv_obj_t * ui_LabelConfigSSID;
extern lv_obj_t * ui_LabelConfigWifiPassword;
extern lv_obj_t * ui_LabelConfigLNbitsHost;
extern lv_obj_t * ui_LabelConfigDeviceID;
extern lv_obj_t * ui_Label14;
void ui_event_TextAreaConfigSSID(lv_event_t * e);
extern lv_obj_t * ui_TextAreaConfigSSID;
void ui_event_TextAreaWifiPassword(lv_event_t * e);
extern lv_obj_t * ui_TextAreaConfigWifiPassword;
void ui_event_TextAreaConfigLNbitsHost(lv_event_t * e);
extern lv_obj_t * ui_TextAreaConfigLNbitsHost;
void ui_event_TextAreaConfigDeviceID(lv_event_t * e);
extern lv_obj_t * ui_TextAreaConfigDeviceID;
extern lv_obj_t * ui_LabelConfigDeviceID;
void ui_event_ButtonPIN(lv_event_t * e);
extern lv_obj_t * ui_ButtonPIN;
extern lv_obj_t * ui_LabelConfigPIN;
extern lv_obj_t * ui_LabelConfigStatus;
void ui_event_ButtonConfigDone(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigDone;
extern lv_obj_t * ui_LabelConfigDone;
void ui_event_ButtonConfigCancel(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigCancel;
extern lv_obj_t * ui_LabelConfigCancel;



extern lv_obj_t * ui_PanelConfigPIN;
extern lv_obj_t * ui_LabelConfigPINCurrent;
extern lv_obj_t * ui_LabelConfigPINNew;
extern lv_obj_t * ui_LabelConfigPINRepeat;
void ui_event_TextAreaConfigPINCurrent(lv_event_t * e);
extern lv_obj_t * ui_TextAreaConfigPINCurrent;
void ui_event_TextAreaConfigPINRepeat(lv_event_t * e);
extern lv_obj_t * ui_TextAreaConfigPINRepeat;
void ui_event_TextAreaConfigPINNew(lv_event_t * e);
extern lv_obj_t * ui_TextAreaConfigPINNew;
void ui_event_ButtonConfigPINOK(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigPINOK;
extern lv_obj_t * ui_LabelConfigButtonPINOK;
void ui_event_ButtonConfigPINCancel(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigPINCancel;
extern lv_obj_t * ui_LabelConfigButtonPINCancel;
extern lv_obj_t * ui_LabelConfigPINMessage;

extern lv_obj_t * ui_LabelConfigRSSI;
extern lv_obj_t * ui_LabelConfigPaymentMode;
extern lv_obj_t * ui_LabelConfigRSSIValue;
extern lv_obj_t * ui_DropdownConfigPaymentMode;
extern lv_obj_t * ui_DropdownConfigControlMode;

void ui_event_KeyboardConfig(lv_event_t * e);
extern lv_obj_t * ui_KeyboardConfig;
extern lv_obj_t * ui_Label2;
void ui_event_ButtonConfigBack(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigBack;
extern lv_obj_t * ui_Label16;
void ui_event_ButtonConfigUpdate(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigUpdate;
extern lv_obj_t * ui_LabelConfigUpdate;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_TextAreaConfigServoClosed;
extern lv_obj_t * ui_TextAreaConfigServoOpen;
void ui_event_ButtonConfigServoClose(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigServoClose;
extern lv_obj_t * ui_Label10;
void ui_event_ButtonConfigServoOpen(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigServoOpen;
extern lv_obj_t * ui_Label9;
void ui_event_ButtonConfigSave(lv_event_t * e);
extern lv_obj_t * ui_ButtonConfigSave;
extern lv_obj_t * ui_Label11;
void ui_event_ScreenBierFlowing(lv_event_t * e);
extern lv_obj_t * ui_ScreenBierFlowing;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_LabelInstructions;
extern lv_obj_t * ui_BarBierProgress;
extern lv_obj_t * ui_ButtonBierStart;
extern lv_obj_t * ui_Label45;
void ui_event_ButtonBierStart(lv_event_t * e);


void ButtonPinNumberClicked(lv_event_t * e);
void ButtonPinCancelClicked(lv_event_t * e);
void ButtonPinOKClicked(lv_event_t * e);

void ButtonOKPINClicked(lv_event_t * e);
void ButtonCancelPINClicked(lv_event_t * e);
void ButtonAboutOneClicked(lv_event_t * e);
void ButtonAboutTwoClicked(lv_event_t * e);
void ButtonAboutThreeClicked(lv_event_t * e);
void ButtonAboutConfigClicked(lv_event_t * e);

void ButtonConfigDoneClicked(lv_event_t *e);
void ButtonConfigCancelClicked(lv_event_t *e);

void ButtonMainBackClicked(lv_event_t * e);
void ButtonMainEnterPINClicked(lv_event_t * e);

void ButtonScreenBierFlowingClicked(lv_event_t * e);
void ButtonBierStartClicked(lv_event_t * e);


LV_IMG_DECLARE(ui_img_bitcointaps256);    // Bitcoin Taps logo
LV_IMG_DECLARE(ui_img_instructions);    // Bitcoin Taps logo


// The font was created with the following command
// lv_font_conv --bpp 1 --size 18 --font Ubuntu-BoldItalic.ttf -o ui_font_UbuntuBoldItalic.c --format lvgl --symbols 'ABCDEFGHIBCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_$!*.% ' --no-prefilter
// The reference in the header of the result file was replaced by #include "ui.h"
LV_FONT_DECLARE(ui_font_UbuntuBoldItalic);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

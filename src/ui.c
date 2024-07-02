#include "ui.h"
#include "ui_helpers.h"
#include <stdio.h>

#define STR1(x)  #x
#define STR(x)  STR1(x)    

#define BUTTON_ANIMATE_TIME 400

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_ScreenAbout;
lv_obj_t * ui_PanelAboutHeader;
lv_obj_t * ui_LabelAboutHeader;
lv_obj_t * ui_ImageAbout;
lv_obj_t * ui_LabelAboutStatus;
lv_obj_t * ui_PanelAboutMessage;
lv_obj_t * ui_LabelAboutMessage;
void ui_event_PanelAboutHeader(lv_event_t * e);
void ui_event_ButtonAboutOne(lv_event_t * e);
void ui_event_ButtonAboutTwo(lv_event_t * e);
void ui_event_ButtonAboutThree(lv_event_t * e);
lv_obj_t * ui_ScreenMain;
lv_obj_t * ui_PanelHeaderMain;
lv_obj_t * ui_LabelHeaderMain;
void ui_event_ButtonMainAbout(lv_event_t * e);
lv_obj_t * ui_ButtonMainAbout;
lv_obj_t * ui_Label18;
void ui_event_ButtonMainEnterPIN(lv_event_t * e);
lv_obj_t * ui_ButtonMainEnterPIN;
lv_obj_t * ui_LabelMainEnterPIN;
lv_obj_t * ui_ScreenPin;
lv_obj_t * ui_LabelPINValue;
lv_obj_t * ui_PanelPin;
lv_obj_t * ui_LabelPinPanel;
lv_obj_t * ui_PanelMainMessage;
lv_obj_t * ui_LabelMainMessage;
lv_obj_t * ui_QrcodeLnurl;
void ui_event_ButtonNumber(lv_event_t * e);
lv_obj_t * ui_ButtonPin1;
lv_obj_t * ui_LabelPin1;
lv_obj_t * ui_ButtonPin2;
lv_obj_t * ui_LabelPin2;
lv_obj_t * ui_ButtonPin3;
lv_obj_t * ui_LabelPin3;
lv_obj_t * ui_ButtonPin4;
lv_obj_t * ui_LabelPin4;
lv_obj_t * ui_ButtonPin5;
lv_obj_t * ui_LabelPin5;
lv_obj_t * ui_ButtonPin6;
lv_obj_t * ui_LabelPin6;
lv_obj_t * ui_ButtonPin7;
lv_obj_t * ui_LabelPin7;
lv_obj_t * ui_ButtonPin8;
lv_obj_t * ui_LabelPin8;
lv_obj_t * ui_ButtonPin9;
lv_obj_t * ui_LabelPin9;
void ui_event_ButtonPINCancel(lv_event_t * e);
lv_obj_t * ui_ButtonPINCancel;
lv_obj_t * ui_LabelPINCancel;
lv_obj_t * ui_ButtonPin0;
lv_obj_t * ui_LabelPin0;
void ui_event_ButtonPinOK(lv_event_t * e);
lv_obj_t * ui_ButtonPinOK;
lv_obj_t * ui_LabelPinOK;
lv_obj_t * ui_ScreenConfig;
lv_obj_t * ui_PanelConfig;
lv_obj_t * ui_LabelConfigPanel;
lv_obj_t * ui_LabelConfigSSID;
lv_obj_t * ui_LabelConfigWifiPassword;
lv_obj_t * ui_LabelConfigLNbitsHost;
lv_obj_t * ui_LabelConfigDeviceID;
lv_obj_t * ui_Label14;
void ui_event_TextAreaConfigSSID(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigSSID;
void ui_event_TextAreaWifiPassword(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigWifiPassword;
void ui_event_TextAreaConfigLNbitsHost(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigLNbitsHost;
void ui_event_TextAreaConfigDeviceID(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigDeviceID;
void ui_event_ButtonConfigTuner(lv_event_t * e);
lv_obj_t * ui_ButtonConfigTuner;
lv_obj_t * ui_DropdownConfigPaymentMode;

lv_obj_t * ui_DropdownConfigControlMode;
lv_obj_t * ui_LabelConfigPaymentMode;
lv_obj_t * ui_LabelConfigSwitchMode;
lv_obj_t * ui_LabelConfigControlMode;
lv_obj_t * ui_LabelConfigTuner;
void ui_event_ButtonConfigConnect(lv_event_t * e);
lv_obj_t * ui_ButtonConfigConnect;
lv_obj_t * ui_LabelConfigDeviceID;
void ui_event_ButtonPIN(lv_event_t * e);
lv_obj_t * ui_ButtonPIN;
lv_obj_t * ui_LabelConfigPIN;
lv_obj_t * ui_LabelConfigStatus;
void ui_event_ButtonConfigDone(lv_event_t * e);
lv_obj_t * ui_ButtonConfigDone;
lv_obj_t * ui_LabelConfigDone;
void ui_event_ButtonConfigCancel(lv_event_t * e);
lv_obj_t * ui_ButtonConfigCancel;
lv_obj_t * ui_LabelConfigCancel;
lv_obj_t * ui_PanelConfigPIN;
lv_obj_t * ui_LabelConfigPINCurrent;
lv_obj_t * ui_LabelConfigPINNew;
lv_obj_t * ui_LabelConfigPINRepeat;
void ui_event_TextAreaConfigPINCurrent(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigPINCurrent;
void ui_event_TextAreaConfigPINRepeat(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigPINRepeat;
void ui_event_TextAreaConfigPINNew(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigPINNew;
void ui_event_ButtonConfigPINOK(lv_event_t * e);
lv_obj_t * ui_ButtonConfigPINOK;
lv_obj_t * ui_LabelConfigButtonPINOK;
void ui_event_ButtonConfigPINCancel(lv_event_t * e);
lv_obj_t * ui_ButtonConfigPINCancel;
lv_obj_t * ui_LabelConfigButtonPINCancel;
lv_obj_t * ui_LabelConfigRSSI;
lv_obj_t * ui_LabelConfigPaymentMode;
lv_obj_t * ui_LabelConfigRSSIValue;
lv_obj_t * ui_LabelConfigPINMessage;
void ui_event_KeyboardConfig(lv_event_t * e);
lv_obj_t * ui_KeyboardConfig;
lv_obj_t * ui_KeyboardConfig;
lv_obj_t * ui_ScreenConfigAdvanced;
lv_obj_t * ui_PanelHeaderConfig;
void ui_event_ButtonConfigBack(lv_event_t * e);
lv_obj_t * ui_ButtonConfigBack;
void ui_event_ButtonConfigUpdate(lv_event_t * e);
lv_obj_t * ui_ButtonConfigUpdate;
lv_obj_t * ui_LabelConfigUpdate;
lv_obj_t * ui_LabelConfigServo;
void ui_event_TextAreaConfigServoClosed(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigServoClosed;
void ui_event_TextAreaConfigServoOpen(lv_event_t * e);
lv_obj_t * ui_TextAreaConfigServoOpen;
lv_obj_t * ui_Label7;
void ui_event_ButtonConfigServoClose(lv_event_t * e);
lv_obj_t * ui_ButtonConfigServoClose;
lv_obj_t * ui_LabelConfigServoClose;
void ui_event_ButtonConfigServoOpen(lv_event_t * e);
lv_obj_t * ui_ButtonConfigServoOpen;
lv_obj_t * ui_LabelConfigServoOpen;
void ui_event_ScreenBierFlowing(lv_event_t * e);
lv_obj_t * ui_ScreenBierFlowing;
lv_obj_t * ui_Image3;
lv_obj_t * ui_LabelInstructions;
lv_obj_t * ui_BarBierProgress;
lv_obj_t * ui_ButtonBierStart;
lv_obj_t * ui_LabelBierStart;
void ui_event_ButtonBierStart(lv_event_t * e);

// Admin screen
lv_obj_t * ui_ScreenAdmin;
lv_obj_t * ui_PanelAdminHeader;
lv_obj_t * ui_LabelAdminHeader;
lv_obj_t * ui_LabelAdminVersion;
lv_obj_t * ui_LabelAdminServerVersion;
lv_obj_t * ui_LabelAdminBranding;
lv_obj_t * ui_LabelAdminWiFiStatus;
lv_obj_t * ui_LabelAdminWebSocketStatus;
lv_obj_t * ui_ButtonAdminConfig;
lv_obj_t * ui_LabelAdminConfig;
lv_obj_t * ui_ButtonAdminCancel;
lv_obj_t * ui_LabelAdminCancel;
lv_obj_t * ui_ButtonAdminFree;
lv_obj_t * ui_LabelAdminFree;
lv_obj_t * ui_ButtonAdminOpen;
lv_obj_t * ui_LabelAdminOpen;
lv_obj_t * ui_ButtonAdminClose;
lv_obj_t * ui_LabelAdminClose;
void ui_event_ButtonAdminConfig(lv_event_t * e);
void ui_event_ButtonAdminCancel(lv_event_t * e);
void ui_event_ButtonAdminFree(lv_event_t * e);
void ui_event_ButtonAdminClose(lv_event_t * e);
void ui_event_ButtonAdminOpen(lv_event_t * e);

// About screen
lv_obj_t * ui_ButtonAboutOne;
lv_obj_t * ui_ButtonAboutTwo;
lv_obj_t * ui_ButtonAboutThree;
lv_obj_t * ui_LabelAboutOne;
lv_obj_t * ui_LabelAboutTwo;
lv_obj_t * ui_LabelAboutThree;
lv_anim_t ui_AnimateAboutOne;
lv_anim_t ui_AnimateAboutTwo;
lv_anim_t ui_AnimateAboutThree;

// Tap screen
lv_anim_t ui_AnimateBierStart;


///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_ButtonAboutOne(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAboutOneClicked(e);
    }
}

void ui_event_ButtonAboutTwo(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAboutTwoClicked(e);
    }
}

void ui_event_ButtonAboutThree(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAboutThreeClicked(e);
    }
}

void ui_event_PanelAboutHeader(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        PanelAboutHeaderClicked(e);
    }
}

void ui_event_ButtonMainAbout(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        //_ui_screen_change(ui_ScreenAbout, LV_SCR_LOAD_ANIM_NONE, 0, 0);
        ButtonMainBackClicked(e);
    }
}

void ui_event_ButtonMainEnterPIN(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        //_ui_screen_change(ui_ScreenAbout, LV_SCR_LOAD_ANIM_NONE, 0, 0);
        ButtonMainEnterPINClicked(e);
    }
}


void ui_event_ButtonNumber(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonPinNumberClicked(e);
    }
}
void ui_event_ButtonPINCancel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonPinCancelClicked(e);
    }
}
void ui_event_ButtonPinOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonPinOKClicked(e);
    }
}

void ui_event_TextAreaConfigServoOpen(lv_event_t * e) 
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_NUMBER);
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigServoOpen);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

void ui_event_TextAreaConfigServoClosed(lv_event_t * e) 
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_NUMBER);
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigServoClosed);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}


void ui_event_TextAreaConfigSSID(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_TEXT_LOWER);
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigSSID);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_TextAreaWifiPassword(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_TEXT_LOWER);
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigWifiPassword);
    }
}
void ui_event_TextAreaConfigLNbitsHost(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigLNbitsHost);
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_TEXT_LOWER);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_TextAreaConfigDeviceID(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigDeviceID);
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_TEXT_LOWER);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

/*void ui_event_ButtonConfigTuner(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonConfigTunerClicked(e);
    }
}
*/

/*void ui_event_ButtonConfigConnect(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        ButtonConfigConnectClicked(e);
    }
}*/

void ui_event_ButtonPIN(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_PanelConfigPIN, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_ButtonConfigDone(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_PanelConfigPIN, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        ButtonConfigDoneClicked(e);
    }
}

void ui_event_ButtonConfigCancel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_PanelConfigPIN, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        ButtonConfigCancelClicked(e);
    }
}

void ui_event_ButtonConfigUpdate(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_PanelConfigPIN, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        ButtonConfigUpdateClicked(e);
    }
}


void ui_event_TextAreaConfigPINCurrent(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigPINCurrent);
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_NUMBER);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_TextAreaConfigPINRepeat(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigPINRepeat);
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_NUMBER);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_TextAreaConfigPINNew(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_keyboard_set_target(ui_KeyboardConfig,  ui_TextAreaConfigPINNew);
        lv_keyboard_set_mode(ui_KeyboardConfig, LV_KEYBOARD_MODE_NUMBER);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_ButtonConfigPINOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonOKPINClicked(e);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_ButtonConfigPINCancel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonCancelPINClicked(e);
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}


void ui_event_KeyboardConfig(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_READY) {
        _ui_flag_modify(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_ButtonConfigBack(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_ScreenConfig, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
}

void ui_event_ScreenBierFlowing(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonScreenBierFlowingClicked(e);
    }
}

void ui_event_ButtonBierStart(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonBierStartClicked(e);
    }
}

/// Admin Screen events
void ui_event_ButtonAdminConfig(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAdminConfigClicked(e);
    }
}

void ui_event_ButtonAdminCancel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAdminCancelClicked(e);
    }
}

void ui_event_ButtonAdminOpen(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAdminOpenClicked(e);
    }
}

void ui_event_ButtonAdminClose(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAdminCloseClicked(e);
    }
}

void ui_event_ButtonAdminFree(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        ButtonAdminFreeClicked(e);
    }
}

// Generic callbacks
static void ui_AnimateButtonCallback(void *var, int32_t v)
{
    lv_obj_set_size((lv_obj_t *)var, v, v);
}


///////////////////// SCREENS ////////////////////
void ui_ScreenAbout_screen_init(void)
{
    ui_ScreenAbout = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenAbout, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenAbout, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenAbout, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelAboutHeader = lv_obj_create(ui_ScreenAbout);
#ifdef DISPLAY_WIDTH
    lv_obj_set_width(ui_PanelAboutHeader, DISPLAY_WIDTH);
#endif
#ifdef LCD_WIDTH
    lv_obj_set_width(ui_PanelAboutHeader, LCD_WIDTH);
#endif
    lv_obj_set_height(ui_PanelAboutHeader, 50);
    lv_obj_clear_flag(ui_PanelAboutHeader, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PanelAboutHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelAboutHeader, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelAboutHeader, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelAboutHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAboutHeader = lv_label_create(ui_PanelAboutHeader);
    lv_obj_set_width(ui_LabelAboutHeader, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAboutHeader, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAboutHeader, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAboutHeader, BB_NAME);
    lv_obj_set_style_text_color(ui_LabelAboutHeader, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAboutHeader, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAboutHeader, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_ImageAbout = lv_img_create(ui_ScreenAbout);

#ifdef BRANDING_BITCOINTAPS
    lv_img_set_src(ui_ImageAbout, &ui_img_bitcointaps256);  // BitcoinTaps logo
#endif
#ifdef BRANDING_BEER
    lv_img_set_src(ui_ImageAbout, &ui_img_kanhetal256);  // Kan het Al
#endif

    lv_obj_set_width(ui_ImageAbout, LV_SIZE_CONTENT);   /// 256
    lv_obj_set_height(ui_ImageAbout, LV_SIZE_CONTENT);    /// 256
    lv_obj_set_y(ui_ImageAbout, -50);
    lv_obj_set_align(ui_ImageAbout, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageAbout, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImageAbout, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelAboutStatus = lv_label_create(ui_ScreenAbout);
    lv_obj_set_width(ui_LabelAboutStatus, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAboutStatus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelAboutStatus, 0);
    lv_obj_set_y(ui_LabelAboutStatus, -20);
    lv_obj_set_align(ui_LabelAboutStatus, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_LabelAboutStatus, "");
    lv_obj_set_style_text_color(ui_LabelAboutStatus, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAboutStatus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAboutStatus, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonAboutOne = lv_btn_create(ui_ScreenAbout);
    lv_obj_set_width(ui_ButtonAboutOne, 100);
    lv_obj_set_height(ui_ButtonAboutOne, 100);
    lv_obj_set_align(ui_ButtonAboutOne, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_x(ui_ButtonAboutOne, 0);
    lv_obj_set_y(ui_ButtonAboutOne, -60);
    lv_obj_add_flag(ui_ButtonAboutOne, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAboutOne, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAboutOne, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAboutOne, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_ButtonAboutOne,LV_OBJ_FLAG_HIDDEN);
    
    ui_LabelAboutOne = lv_label_create(ui_ButtonAboutOne);
    lv_obj_set_width(ui_LabelAboutOne, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAboutOne, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAboutOne, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAboutOne, "");
    lv_obj_set_style_text_color(ui_LabelAboutOne, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAboutOne, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAboutOne, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_anim_init(&ui_AnimateAboutOne);
    lv_anim_set_var(&ui_AnimateAboutOne, ui_ButtonAboutOne);
    lv_anim_set_values(&ui_AnimateAboutOne,90,95);
    lv_anim_set_time(&ui_AnimateAboutOne,BUTTON_ANIMATE_TIME);
    lv_anim_set_playback_delay(&ui_AnimateAboutOne,0);
    lv_anim_set_playback_time(&ui_AnimateAboutOne,BUTTON_ANIMATE_TIME);
    lv_anim_set_repeat_delay(&ui_AnimateAboutOne,0);
    lv_anim_set_repeat_count(&ui_AnimateAboutOne, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_exec_cb(&ui_AnimateAboutOne, ui_AnimateButtonCallback);


    ui_ButtonAboutTwo = lv_btn_create(ui_ScreenAbout);
    lv_obj_set_width(ui_ButtonAboutTwo, 100);
    lv_obj_set_height(ui_ButtonAboutTwo, 100);
    lv_obj_set_align(ui_ButtonAboutTwo, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_x(ui_ButtonAboutTwo, 0);
    lv_obj_set_y(ui_ButtonAboutTwo, -60);
    lv_obj_add_flag(ui_ButtonAboutTwo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAboutTwo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAboutTwo, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAboutTwo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_ButtonAboutTwo,LV_OBJ_FLAG_HIDDEN);

    ui_LabelAboutTwo = lv_label_create(ui_ButtonAboutTwo);
    lv_obj_set_width(ui_LabelAboutTwo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAboutTwo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAboutTwo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAboutTwo, "");
    lv_obj_set_style_text_color(ui_LabelAboutTwo, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAboutTwo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAboutTwo, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_anim_init(&ui_AnimateAboutTwo);
    lv_anim_set_var(&ui_AnimateAboutTwo, ui_ButtonAboutTwo);
    lv_anim_set_values(&ui_AnimateAboutTwo,90,95);
    lv_anim_set_time(&ui_AnimateAboutTwo,BUTTON_ANIMATE_TIME);
    lv_anim_set_playback_delay(&ui_AnimateAboutTwo,0);
    lv_anim_set_playback_time(&ui_AnimateAboutTwo,BUTTON_ANIMATE_TIME);
    lv_anim_set_repeat_delay(&ui_AnimateAboutTwo,0);
    lv_anim_set_repeat_count(&ui_AnimateAboutTwo, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_exec_cb(&ui_AnimateAboutTwo, ui_AnimateButtonCallback);

    ui_ButtonAboutThree = lv_btn_create(ui_ScreenAbout);
    lv_obj_set_width(ui_ButtonAboutThree, 100);
    lv_obj_set_height(ui_ButtonAboutThree, 100);
    lv_obj_set_align(ui_ButtonAboutThree, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_x(ui_ButtonAboutThree, 0);
    lv_obj_set_y(ui_ButtonAboutThree, -60);
    lv_obj_add_flag(ui_ButtonAboutThree, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAboutThree, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAboutThree, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAboutThree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_ButtonAboutThree,LV_OBJ_FLAG_HIDDEN);

    ui_LabelAboutThree = lv_label_create(ui_ButtonAboutThree);
    lv_obj_set_width(ui_LabelAboutThree, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAboutThree, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAboutThree, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAboutThree, "");
    lv_obj_set_style_text_color(ui_LabelAboutThree, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAboutThree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAboutThree, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_anim_init(&ui_AnimateAboutThree);
    lv_anim_set_var(&ui_AnimateAboutThree, ui_ButtonAboutThree);
    lv_anim_set_values(&ui_AnimateAboutThree,90,95);
    lv_anim_set_time(&ui_AnimateAboutThree,BUTTON_ANIMATE_TIME);
    lv_anim_set_playback_delay(&ui_AnimateAboutThree,0);
    lv_anim_set_playback_time(&ui_AnimateAboutThree,BUTTON_ANIMATE_TIME);
    lv_anim_set_repeat_delay(&ui_AnimateAboutThree,0);
    lv_anim_set_repeat_count(&ui_AnimateAboutThree, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_exec_cb(&ui_AnimateAboutThree, ui_AnimateButtonCallback);


    ui_PanelAboutMessage = lv_obj_create(ui_ScreenAbout);
    lv_obj_set_width(ui_PanelAboutMessage, 240);
    lv_obj_set_height(ui_PanelAboutMessage, 100);
    lv_obj_clear_flag(ui_PanelAboutMessage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_align(ui_PanelAboutMessage, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_PanelAboutMessage, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelAboutMessage, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelAboutMessage, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelAboutMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_PanelAboutMessage,LV_OBJ_FLAG_HIDDEN);

    ui_LabelAboutMessage = lv_label_create(ui_PanelAboutMessage);
    lv_obj_set_width(ui_LabelAboutMessage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAboutMessage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAboutMessage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAboutMessage, "CREATING INVOICE");
    lv_obj_set_style_text_color(ui_LabelAboutMessage, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAboutMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAboutMessage, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_add_event_cb(ui_ButtonAboutOne, ui_event_ButtonAboutOne, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonAboutTwo, ui_event_ButtonAboutTwo, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonAboutThree, ui_event_ButtonAboutThree, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PanelAboutHeader, ui_event_PanelAboutHeader, LV_EVENT_ALL, NULL);

}
void ui_ScreenMain_screen_init(void)
{
    ui_ScreenMain = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenMain, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelHeaderMain = lv_obj_create(ui_ScreenMain);
    lv_obj_set_width(ui_PanelHeaderMain, 320);
    lv_obj_set_height(ui_PanelHeaderMain, 50);
    lv_obj_clear_flag(ui_PanelHeaderMain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PanelHeaderMain, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelHeaderMain, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelHeaderMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelHeaderMain, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelHeaderMain = lv_label_create(ui_PanelHeaderMain);
    lv_obj_set_width(ui_LabelHeaderMain, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelHeaderMain, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelHeaderMain, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelHeaderMain, "PAY FOR YOUR DRINK");
    lv_obj_set_style_text_color(ui_LabelHeaderMain, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelHeaderMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelHeaderMain, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonMainAbout = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_ButtonMainAbout, 120);
    lv_obj_set_height(ui_ButtonMainAbout, 50);
    lv_obj_set_x(ui_ButtonMainAbout, 0);
    lv_obj_set_y(ui_ButtonMainAbout, -10);
    lv_obj_set_align(ui_ButtonMainAbout, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_ButtonMainAbout, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonMainAbout, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonMainAbout, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonMainAbout, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label18 = lv_label_create(ui_ButtonMainAbout);
    lv_obj_set_width(ui_Label18, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label18, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label18, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label18, "CANCEL");
    lv_obj_set_style_text_color(ui_Label18, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label18, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label18, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonMainEnterPIN = lv_btn_create(ui_ScreenMain);
    lv_obj_set_width(ui_ButtonMainEnterPIN, 120);
    lv_obj_set_height(ui_ButtonMainEnterPIN, 50);
    lv_obj_set_x(ui_ButtonMainEnterPIN, -70);
    lv_obj_set_y(ui_ButtonMainEnterPIN, -10);
    lv_obj_set_align(ui_ButtonMainEnterPIN, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_ButtonMainEnterPIN, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonMainEnterPIN, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonMainEnterPIN, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonMainEnterPIN, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_ButtonMainEnterPIN,LV_OBJ_FLAG_HIDDEN);

    ui_LabelMainEnterPIN = lv_label_create(ui_ButtonMainEnterPIN);
    lv_obj_set_width(ui_LabelMainEnterPIN, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelMainEnterPIN, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelMainEnterPIN, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelMainEnterPIN, "ENTER PIN");
    lv_obj_set_style_text_color(ui_LabelMainEnterPIN, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelMainEnterPIN, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelMainEnterPIN, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);


    // initialize the QR code
    lv_color_t bg_color = lv_color_hex(0xFFFFFF);
    lv_color_t fg_color = lv_color_hex(0x000000);
    ui_QrcodeLnurl = lv_qrcode_create(ui_ScreenMain,240,fg_color,bg_color);
    lv_obj_center(ui_QrcodeLnurl);
    lv_obj_set_pos(ui_QrcodeLnurl,0, -30);
    lv_obj_set_style_border_width(ui_QrcodeLnurl, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_QrcodeLnurl, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_QrcodeLnurl, LV_OBJ_FLAG_HIDDEN);

    ui_PanelMainMessage = lv_obj_create(ui_ScreenMain);
    lv_obj_set_y(ui_PanelMainMessage,140);
    lv_obj_set_width(ui_PanelMainMessage, 256);
    lv_obj_set_height(ui_PanelMainMessage, 50);
    lv_obj_clear_flag(ui_PanelMainMessage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_align(ui_PanelMainMessage, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_PanelMainMessage, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelMainMessage, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelMainMessage, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelMainMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_add_flag(ui_PanelMainMessage,LV_OBJ_FLAG_HIDDEN);

    ui_LabelMainMessage = lv_label_create(ui_PanelMainMessage);
    lv_obj_set_width(ui_LabelMainMessage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelMainMessage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelMainMessage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelMainMessage, "THIS IS A TEST");
    lv_obj_set_style_text_color(ui_LabelMainMessage, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelMainMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelMainMessage, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ButtonMainEnterPIN,ui_event_ButtonMainEnterPIN, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonMainAbout, ui_event_ButtonMainAbout, LV_EVENT_ALL, NULL);

}

void ui_ScreenPin_screen_init(void)
{
    ui_ScreenPin = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenPin, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenPin, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenPin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPINValue = lv_label_create(ui_ScreenPin);
    lv_obj_set_width(ui_LabelPINValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPINValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelPINValue, 0);
    lv_obj_set_y(ui_LabelPINValue, 80);
    lv_obj_set_align(ui_LabelPINValue, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_LabelPINValue, "ENTER PIN");
    lv_obj_set_style_text_color(ui_LabelPINValue, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPINValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_LabelPINValue, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_LabelPINValue, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelPINValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPINValue, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelPin = lv_obj_create(ui_ScreenPin);
    lv_obj_set_width(ui_PanelPin, 320);
    lv_obj_set_height(ui_PanelPin, 50);
    lv_obj_clear_flag(ui_PanelPin, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PanelPin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelPin, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelPin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelPin, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPinPanel = lv_label_create(ui_PanelPin);
    lv_obj_set_width(ui_LabelPinPanel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPinPanel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPinPanel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPinPanel, "ENTER PIN");
    lv_obj_set_style_text_color(ui_LabelPinPanel, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPinPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPinPanel, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin1 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin1, 80);
    lv_obj_set_height(ui_ButtonPin1, 80);
    lv_obj_set_x(ui_ButtonPin1, -90);
    lv_obj_set_y(ui_ButtonPin1, -80);
    lv_obj_set_align(ui_ButtonPin1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin1, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin1 = lv_label_create(ui_ButtonPin1);
    lv_obj_set_width(ui_LabelPin1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin1, "1");
    lv_obj_set_style_text_color(ui_LabelPin1, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin1, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin2 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin2, 80);
    lv_obj_set_height(ui_ButtonPin2, 80);
    lv_obj_set_x(ui_ButtonPin2, 0);
    lv_obj_set_y(ui_ButtonPin2, -80);
    lv_obj_set_align(ui_ButtonPin2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin2, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin2 = lv_label_create(ui_ButtonPin2);
    lv_obj_set_width(ui_LabelPin2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin2, "2");
    lv_obj_set_style_text_color(ui_LabelPin2, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin2, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin3 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin3, 80);
    lv_obj_set_height(ui_ButtonPin3, 80);
    lv_obj_set_x(ui_ButtonPin3, 90);
    lv_obj_set_y(ui_ButtonPin3, -80);
    lv_obj_set_align(ui_ButtonPin3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin3, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin3 = lv_label_create(ui_ButtonPin3);
    lv_obj_set_width(ui_LabelPin3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin3, "3");
    lv_obj_set_style_text_color(ui_LabelPin3, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin3, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin4 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin4, 80);
    lv_obj_set_height(ui_ButtonPin4, 80);
    lv_obj_set_x(ui_ButtonPin4, -90);
    lv_obj_set_y(ui_ButtonPin4, 10);
    lv_obj_set_align(ui_ButtonPin4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin4, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin4 = lv_label_create(ui_ButtonPin4);
    lv_obj_set_width(ui_LabelPin4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin4, "4");
    lv_obj_set_style_text_color(ui_LabelPin4, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin4, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin5 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin5, 80);
    lv_obj_set_height(ui_ButtonPin5, 80);
    lv_obj_set_x(ui_ButtonPin5, 0);
    lv_obj_set_y(ui_ButtonPin5, 10);
    lv_obj_set_align(ui_ButtonPin5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin5, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin5 = lv_label_create(ui_ButtonPin5);
    lv_obj_set_width(ui_LabelPin5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin5, "5");
    lv_obj_set_style_text_color(ui_LabelPin5, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin5, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin6 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin6, 80);
    lv_obj_set_height(ui_ButtonPin6, 80);
    lv_obj_set_x(ui_ButtonPin6, 90);
    lv_obj_set_y(ui_ButtonPin6, 10);
    lv_obj_set_align(ui_ButtonPin6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin6, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin6 = lv_label_create(ui_ButtonPin6);
    lv_obj_set_width(ui_LabelPin6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin6, "6");
    lv_obj_set_style_text_color(ui_LabelPin6, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin6, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin7 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin7, 80);
    lv_obj_set_height(ui_ButtonPin7, 80);
    lv_obj_set_x(ui_ButtonPin7, -90);
    lv_obj_set_y(ui_ButtonPin7, 100);
    lv_obj_set_align(ui_ButtonPin7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin7, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin7, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin7 = lv_label_create(ui_ButtonPin7);
    lv_obj_set_width(ui_LabelPin7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin7, "7");
    lv_obj_set_style_text_color(ui_LabelPin7, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin7, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin8 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin8, 80);
    lv_obj_set_height(ui_ButtonPin8, 80);
    lv_obj_set_x(ui_ButtonPin8, 0);
    lv_obj_set_y(ui_ButtonPin8, 100);
    lv_obj_set_align(ui_ButtonPin8, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin8, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin8, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin8 = lv_label_create(ui_ButtonPin8);
    lv_obj_set_width(ui_LabelPin8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin8, "8");
    lv_obj_set_style_text_color(ui_LabelPin8, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin8, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin9 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin9, 80);
    lv_obj_set_height(ui_ButtonPin9, 80);
    lv_obj_set_x(ui_ButtonPin9, 90);
    lv_obj_set_y(ui_ButtonPin9, 100);
    lv_obj_set_align(ui_ButtonPin9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin9, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin9, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin9 = lv_label_create(ui_ButtonPin9);
    lv_obj_set_width(ui_LabelPin9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin9, "9");
    lv_obj_set_style_text_color(ui_LabelPin9, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin9, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPINCancel = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPINCancel, 80);
    lv_obj_set_height(ui_ButtonPINCancel, 80);
    lv_obj_set_x(ui_ButtonPINCancel, -90);
    lv_obj_set_y(ui_ButtonPINCancel, 190);
    lv_obj_set_align(ui_ButtonPINCancel, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPINCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPINCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPINCancel, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPINCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPINCancel = lv_label_create(ui_ButtonPINCancel);
    lv_obj_set_width(ui_LabelPINCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPINCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPINCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPINCancel, "C");
    lv_obj_set_style_text_color(ui_LabelPINCancel, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPINCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPINCancel, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPin0 = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPin0, 80);
    lv_obj_set_height(ui_ButtonPin0, 80);
    lv_obj_set_x(ui_ButtonPin0, 0);
    lv_obj_set_y(ui_ButtonPin0, 190);
    lv_obj_set_align(ui_ButtonPin0, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPin0, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPin0, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPin0, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPin0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPin0 = lv_label_create(ui_ButtonPin0);
    lv_obj_set_width(ui_LabelPin0, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPin0, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPin0, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin0, "0");
    lv_obj_set_style_text_color(ui_LabelPin0, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin0, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonPinOK = lv_btn_create(ui_ScreenPin);
    lv_obj_set_width(ui_ButtonPinOK, 80);
    lv_obj_set_height(ui_ButtonPinOK, 80);
    lv_obj_set_x(ui_ButtonPinOK, 90);
    lv_obj_set_y(ui_ButtonPinOK, 190);
    lv_obj_set_align(ui_ButtonPinOK, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonPinOK, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPinOK, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPinOK, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPinOK, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelPinOK = lv_label_create(ui_ButtonPinOK);
    lv_obj_set_width(ui_LabelPinOK, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelPinOK, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelPinOK, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPinOK, "OK");
    lv_obj_set_style_text_color(ui_LabelPinOK, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPinOK, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPinOK, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ButtonPin1, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)1);
    lv_obj_add_event_cb(ui_ButtonPin2, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)2);
    lv_obj_add_event_cb(ui_ButtonPin3, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)3);
    lv_obj_add_event_cb(ui_ButtonPin4, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)4);
    lv_obj_add_event_cb(ui_ButtonPin5, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)5);
    lv_obj_add_event_cb(ui_ButtonPin6, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)6);
    lv_obj_add_event_cb(ui_ButtonPin7, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)7);
    lv_obj_add_event_cb(ui_ButtonPin8, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)8);
    lv_obj_add_event_cb(ui_ButtonPin9, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)9);
    lv_obj_add_event_cb(ui_ButtonPin0, ui_event_ButtonNumber, LV_EVENT_ALL, (void *)0);
    lv_obj_add_event_cb(ui_ButtonPINCancel, ui_event_ButtonPINCancel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonPinOK, ui_event_ButtonPinOK, LV_EVENT_ALL, NULL);

}
void ui_ScreenConfig_screen_init(void)
{
    ui_ScreenConfig = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenConfig, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenConfig, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenConfig, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigSSID = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigSSID, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigSSID, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigSSID, 10);
    lv_obj_set_y(ui_LabelConfigSSID, 15);
    lv_label_set_text(ui_LabelConfigSSID, "SSID");
    lv_obj_set_style_text_color(ui_LabelConfigSSID, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigSSID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigSSID, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaConfigSSID = lv_textarea_create(ui_ScreenConfig);
    lv_obj_set_width(ui_TextAreaConfigSSID, 240);
    lv_obj_set_height(ui_TextAreaConfigSSID, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_TextAreaConfigSSID, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_x(ui_TextAreaConfigSSID, -10);
    lv_obj_set_y(ui_TextAreaConfigSSID, 5);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigSSID, "Wi-Fi SSID");
    lv_textarea_set_one_line(ui_TextAreaConfigSSID, true);

    ui_LabelConfigWifiPassword = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigWifiPassword, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigWifiPassword, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigWifiPassword, 10);
    lv_obj_set_y(ui_LabelConfigWifiPassword, 60);
    lv_label_set_text(ui_LabelConfigWifiPassword, "Secret");
    lv_obj_set_style_text_color(ui_LabelConfigWifiPassword, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigWifiPassword, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigWifiPassword, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaConfigWifiPassword = lv_textarea_create(ui_ScreenConfig);
    lv_obj_set_width(ui_TextAreaConfigWifiPassword, 240);
    lv_obj_set_height(ui_TextAreaConfigWifiPassword, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_TextAreaConfigWifiPassword, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_x(ui_TextAreaConfigWifiPassword, -10);
    lv_obj_set_y(ui_TextAreaConfigWifiPassword, 50);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigWifiPassword, "Wi-Fi password");
    lv_textarea_set_one_line(ui_TextAreaConfigWifiPassword, true);
    lv_textarea_set_password_mode(ui_TextAreaConfigWifiPassword, true);

    ui_LabelConfigLNbitsHost = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigLNbitsHost, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigLNbitsHost, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigLNbitsHost, 10);
    lv_obj_set_y(ui_LabelConfigLNbitsHost, 105);
    lv_label_set_text(ui_LabelConfigLNbitsHost, "LNbits host");
    lv_obj_set_style_text_color(ui_LabelConfigLNbitsHost, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigLNbitsHost, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigLNbitsHost, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaConfigLNbitsHost = lv_textarea_create(ui_ScreenConfig);
    lv_obj_set_width(ui_TextAreaConfigLNbitsHost, 200);
    lv_obj_set_height(ui_TextAreaConfigLNbitsHost, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_TextAreaConfigLNbitsHost, -10);
    lv_obj_set_y(ui_TextAreaConfigLNbitsHost, 95);
    lv_obj_set_align(ui_TextAreaConfigLNbitsHost, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigLNbitsHost, "LNbits host");
    lv_textarea_set_one_line(ui_TextAreaConfigLNbitsHost, true);

    ui_LabelConfigDeviceID = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigDeviceID, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigDeviceID, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigDeviceID, 10);
    lv_obj_set_y(ui_LabelConfigDeviceID, 150);
    lv_label_set_text(ui_LabelConfigDeviceID, "Device ID");
    lv_obj_set_style_text_color(ui_LabelConfigDeviceID, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigDeviceID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigDeviceID, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaConfigDeviceID = lv_textarea_create(ui_ScreenConfig);
    lv_obj_set_width(ui_TextAreaConfigDeviceID, 200);
    lv_obj_set_height(ui_TextAreaConfigDeviceID, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_TextAreaConfigDeviceID, -10);
    lv_obj_set_y(ui_TextAreaConfigDeviceID, 140);
    lv_obj_set_align(ui_TextAreaConfigDeviceID, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigDeviceID, "Device ID");
    lv_textarea_set_one_line(ui_TextAreaConfigDeviceID, true);

    ui_LabelConfigServo = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigServo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigServo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigServo, 10);
    lv_obj_set_y(ui_LabelConfigServo, 195);
    lv_label_set_text(ui_LabelConfigServo, "Servo");
    lv_obj_set_style_text_color(ui_LabelConfigServo, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigServo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigServo, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaConfigServoClosed = lv_textarea_create(ui_ScreenConfig);
    lv_obj_set_width(ui_TextAreaConfigServoClosed, 100);
    lv_obj_set_height(ui_TextAreaConfigServoClosed, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_TextAreaConfigServoClosed, -10);
    lv_obj_set_y(ui_TextAreaConfigServoClosed, 185);
    lv_obj_set_align(ui_TextAreaConfigServoClosed, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigServoClosed, "--");
    lv_textarea_set_one_line(ui_TextAreaConfigServoClosed, true);

    ui_TextAreaConfigServoOpen = lv_textarea_create(ui_ScreenConfig);
    lv_obj_set_width(ui_TextAreaConfigServoOpen, 100);
    lv_obj_set_height(ui_TextAreaConfigServoOpen, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_TextAreaConfigServoOpen, -120);
    lv_obj_set_y(ui_TextAreaConfigServoOpen, 185);
    lv_obj_set_align(ui_TextAreaConfigServoOpen, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigServoOpen, "--");
    lv_textarea_set_one_line(ui_TextAreaConfigServoOpen, true);

    ui_ButtonPIN = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonPIN, 95);
    lv_obj_set_height(ui_ButtonPIN, 50);
    lv_obj_set_x(ui_ButtonPIN, 10);
    lv_obj_set_y(ui_ButtonPIN, 230);
    lv_obj_set_align(ui_ButtonPIN, LV_ALIGN_TOP_LEFT);
    lv_obj_add_flag(ui_ButtonPIN, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonPIN, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonPIN, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonPIN, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigPIN = lv_label_create(ui_ButtonPIN);
    lv_obj_set_width(ui_LabelConfigPIN, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigPIN, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigPIN, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigPIN, "PIN");
    lv_obj_set_style_text_color(ui_LabelConfigPIN, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigPIN, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigPIN, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonConfigServoClose = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonConfigServoClose, 95);
    lv_obj_set_height(ui_ButtonConfigServoClose, 50);
    lv_obj_set_x(ui_ButtonConfigServoClose, 0);
    lv_obj_set_y(ui_ButtonConfigServoClose, 230);
    lv_obj_set_align(ui_ButtonConfigServoClose, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_ButtonConfigServoClose, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigServoClose, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigServoClose, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigServoClose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigServoClose = lv_label_create(ui_ButtonConfigServoClose);
    lv_obj_set_width(ui_LabelConfigServoClose, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigServoClose, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigServoClose, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigServoClose, "CLOSE");
    lv_obj_set_style_text_color(ui_LabelConfigServoClose, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigServoClose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigServoClose, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonConfigServoOpen = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonConfigServoOpen, 95);
    lv_obj_set_height(ui_ButtonConfigServoOpen, 50);
    lv_obj_set_x(ui_ButtonConfigServoOpen, -10);
    lv_obj_set_y(ui_ButtonConfigServoOpen, 230);
    lv_obj_set_align(ui_ButtonConfigServoOpen, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_ButtonConfigServoOpen, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigServoOpen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigServoOpen, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigServoOpen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigServoOpen = lv_label_create(ui_ButtonConfigServoOpen);
    lv_obj_set_width(ui_LabelConfigServoOpen, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigServoOpen, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigServoOpen, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigServoOpen, "OPEN");
    lv_obj_set_style_text_color(ui_LabelConfigServoOpen, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigServoOpen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigServoOpen, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);






    ui_LabelConfigPaymentMode = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigPaymentMode, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigPaymentMode, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigPaymentMode, 10);
    lv_obj_set_y(ui_LabelConfigPaymentMode, 345);
    lv_label_set_text(ui_LabelConfigPaymentMode, "Payment mode");
    lv_obj_set_style_text_color(ui_LabelConfigPaymentMode, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigPaymentMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigPaymentMode, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Drop Down for Payment mode
    ui_DropdownConfigPaymentMode = lv_dropdown_create(ui_ScreenConfig);
    lv_dropdown_set_options(ui_DropdownConfigPaymentMode, "Online\nOffline\nAuto");
    lv_obj_set_width(ui_DropdownConfigPaymentMode, 170);
    lv_obj_set_height(ui_DropdownConfigPaymentMode, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DropdownConfigPaymentMode, -10);
    lv_obj_set_y(ui_DropdownConfigPaymentMode, 335);
    lv_obj_set_align(ui_DropdownConfigPaymentMode, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_DropdownConfigPaymentMode, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    // Label for control mode
    ui_LabelConfigControlMode = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigControlMode, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigControlMode, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigControlMode, 10);
    lv_obj_set_y(ui_LabelConfigControlMode, 390);
    lv_label_set_text(ui_LabelConfigControlMode, "Control mode");
    lv_obj_set_style_text_color(ui_LabelConfigControlMode, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigControlMode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigControlMode, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Drop Down for switching mode
    ui_DropdownConfigControlMode = lv_dropdown_create(ui_ScreenConfig);
    lv_dropdown_set_options(ui_DropdownConfigControlMode, "None\nServo, Time\nRelay, Time\nI2C Servo, Time\nI2C Relay, Time\nI2C Servo, Ticks\nI2C Relay, Ticks");
    lv_obj_set_width(ui_DropdownConfigControlMode, 170);
    lv_obj_set_height(ui_DropdownConfigControlMode, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DropdownConfigControlMode, -10);
    lv_obj_set_y(ui_DropdownConfigControlMode, 380);
    lv_obj_set_align(ui_DropdownConfigControlMode, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_DropdownConfigControlMode, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags


  /*  ui_ButtonConfigTuner = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonConfigTuner, 95);
    lv_obj_set_height(ui_ButtonConfigTuner, 50);
    lv_obj_set_x(ui_ButtonConfigTuner, 10);
    lv_obj_set_y(ui_ButtonConfigTuner, 285);
    lv_obj_add_flag(ui_ButtonConfigTuner, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigTuner, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigTuner, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigTuner, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
*/
 /*   ui_LabelConfigTuner = lv_label_create(ui_ButtonConfigTuner);
    lv_obj_set_width(ui_LabelConfigTuner, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigTuner, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigTuner, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigTuner, "TUNER");
    lv_obj_set_style_text_color(ui_LabelConfigTuner, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigTuner, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigTuner, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);
*/
/*    ui_ButtonConfigConnect = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonConfigConnect, 95);
    lv_obj_set_height(ui_ButtonConfigConnect, 50);
    lv_obj_set_x(ui_ButtonConfigConnect, -10);
    lv_obj_set_y(ui_ButtonConfigConnect, 285);
    lv_obj_set_align(ui_ButtonConfigConnect, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_ButtonConfigConnect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigConnect, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigConnect, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigConnect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigDeviceID = lv_label_create(ui_ButtonConfigConnect);
    lv_obj_set_width(ui_LabelConfigDeviceID, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigDeviceID, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigDeviceID, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigDeviceID, "CONNECT");
    lv_obj_set_style_text_color(ui_LabelConfigDeviceID, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigDeviceID, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigDeviceID, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);
*/


  











/*
    ui_LabelConfigRSSI = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigRSSI, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigRSSI, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigRSSI, 10);
    lv_obj_set_y(ui_LabelConfigRSSI, 350);
    lv_label_set_text(ui_LabelConfigRSSI, "RSSI");
    lv_obj_set_style_text_color(ui_LabelConfigRSSI, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigRSSI, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigRSSI, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigRSSIValue = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigRSSIValue, 210);
    lv_obj_set_height(ui_LabelConfigRSSIValue, 30);
    lv_obj_set_x(ui_LabelConfigRSSIValue, 100);
    lv_obj_set_y(ui_LabelConfigRSSIValue, 350);
    lv_label_set_text(ui_LabelConfigRSSIValue, "--");


    ui_Label14 = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label14, 10);
    lv_obj_set_y(ui_Label14, 390);
    lv_label_set_text(ui_Label14, "Status");
    lv_obj_set_style_text_color(ui_Label14, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label14, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

 
    ui_LabelConfigStatus = lv_label_create(ui_ScreenConfig);
    lv_obj_set_width(ui_LabelConfigStatus, 210);
    lv_obj_set_height(ui_LabelConfigStatus, 90);
    lv_obj_set_x(ui_LabelConfigStatus, 100);
    lv_obj_set_y(ui_LabelConfigStatus, 390);
    lv_label_set_text(ui_LabelConfigStatus, "--");

*/

    ui_ButtonConfigDone = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonConfigDone, 95);
    lv_obj_set_height(ui_ButtonConfigDone, 50);
    lv_obj_set_x(ui_ButtonConfigDone, -10);
    lv_obj_set_y(ui_ButtonConfigDone, -5);
    lv_obj_set_align(ui_ButtonConfigDone, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_ButtonConfigDone, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigDone, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigDone, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigDone, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigDone = lv_label_create(ui_ButtonConfigDone);
    lv_obj_set_width(ui_LabelConfigDone, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigDone, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigDone, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigDone, "DONE");
    lv_obj_set_style_text_color(ui_LabelConfigDone, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigDone, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigDone, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonConfigCancel = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonConfigCancel, 95);
    lv_obj_set_height(ui_ButtonConfigCancel, 50);
    lv_obj_set_x(ui_ButtonConfigCancel, 10);
    lv_obj_set_y(ui_ButtonConfigCancel, -5);
    lv_obj_set_align(ui_ButtonConfigCancel, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_ButtonConfigCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigCancel, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigCancel = lv_label_create(ui_ButtonConfigCancel);
    lv_obj_set_width(ui_LabelConfigCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigCancel, "CANCEL");
    lv_obj_set_style_text_color(ui_LabelConfigCancel, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigCancel, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonConfigUpdate = lv_btn_create(ui_ScreenConfig);
    lv_obj_set_width(ui_ButtonConfigUpdate, 95);
    lv_obj_set_height(ui_ButtonConfigUpdate, 50);
    lv_obj_set_x(ui_ButtonConfigUpdate, 0);
    lv_obj_set_y(ui_ButtonConfigUpdate, -5);
    lv_obj_set_align(ui_ButtonConfigUpdate, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_ButtonConfigUpdate, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigUpdate, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigUpdate, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigUpdate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigUpdate = lv_label_create(ui_ButtonConfigUpdate);
    lv_obj_set_width(ui_LabelConfigUpdate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigUpdate, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigUpdate, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigUpdate, "UPDATE");
    lv_obj_set_style_text_color(ui_LabelConfigUpdate, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigUpdate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigUpdate, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelConfigPIN = lv_obj_create(ui_ScreenConfig);
    lv_obj_set_width(ui_PanelConfigPIN, 256);
    lv_obj_set_height(ui_PanelConfigPIN, 256);
    lv_obj_set_x(ui_PanelConfigPIN, 0);
    lv_obj_set_y(ui_PanelConfigPIN, 70);
    lv_obj_set_align(ui_PanelConfigPIN, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_PanelConfigPIN, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_PanelConfigPIN, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelConfigPIN, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelConfigPIN, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelConfigPIN, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelConfigPIN, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelConfigPIN, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigPINCurrent = lv_label_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_LabelConfigPINCurrent, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigPINCurrent, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigPINCurrent, 0);
    lv_obj_set_y(ui_LabelConfigPINCurrent, 10);
    lv_label_set_text(ui_LabelConfigPINCurrent, "Current");

    ui_LabelConfigPINNew = lv_label_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_LabelConfigPINNew, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigPINNew, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigPINNew, 0);
    lv_obj_set_y(ui_LabelConfigPINNew, 60);
    lv_label_set_text(ui_LabelConfigPINNew, "New");

    ui_LabelConfigPINRepeat = lv_label_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_LabelConfigPINRepeat, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigPINRepeat, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigPINRepeat, 0);
    lv_obj_set_y(ui_LabelConfigPINRepeat, 110);
    lv_label_set_text(ui_LabelConfigPINRepeat, "Repeat");

    ui_TextAreaConfigPINCurrent = lv_textarea_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_TextAreaConfigPINCurrent, 150);
    lv_obj_set_height(ui_TextAreaConfigPINCurrent, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_align(ui_TextAreaConfigPINCurrent, LV_ALIGN_TOP_RIGHT);
    lv_textarea_set_accepted_chars(ui_TextAreaConfigPINCurrent, "0123456789");
    lv_textarea_set_max_length(ui_TextAreaConfigPINCurrent, 6);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigPINCurrent, "Current PIN");
    lv_textarea_set_one_line(ui_TextAreaConfigPINCurrent, true);
    lv_textarea_set_password_mode(ui_TextAreaConfigPINCurrent, true);
    lv_obj_set_style_text_font(ui_TextAreaConfigPINCurrent, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaConfigPINRepeat = lv_textarea_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_TextAreaConfigPINRepeat, 150);
    lv_obj_set_height(ui_TextAreaConfigPINRepeat, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_TextAreaConfigPINRepeat, 0);
    lv_obj_set_y(ui_TextAreaConfigPINRepeat, 100);
    lv_obj_set_align(ui_TextAreaConfigPINRepeat, LV_ALIGN_TOP_RIGHT);
    if("0123456789" == "") lv_textarea_set_accepted_chars(ui_TextAreaConfigPINRepeat, NULL);
    else lv_textarea_set_accepted_chars(ui_TextAreaConfigPINRepeat, "0123456789");
    lv_textarea_set_max_length(ui_TextAreaConfigPINRepeat, 6);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigPINRepeat, "Confirm PIN");
    lv_textarea_set_one_line(ui_TextAreaConfigPINRepeat, true);
    lv_textarea_set_password_mode(ui_TextAreaConfigPINRepeat, true);
    lv_obj_set_style_text_font(ui_TextAreaConfigPINRepeat, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextAreaConfigPINNew = lv_textarea_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_TextAreaConfigPINNew, 150);
    lv_obj_set_height(ui_TextAreaConfigPINNew, LV_SIZE_CONTENT);    /// 70
    lv_obj_set_x(ui_TextAreaConfigPINNew, 0);
    lv_obj_set_y(ui_TextAreaConfigPINNew, 50);
    lv_obj_set_align(ui_TextAreaConfigPINNew, LV_ALIGN_TOP_RIGHT);
    if("0123456789" == "") lv_textarea_set_accepted_chars(ui_TextAreaConfigPINNew, NULL);
    else lv_textarea_set_accepted_chars(ui_TextAreaConfigPINNew, "0123456789");
    lv_textarea_set_max_length(ui_TextAreaConfigPINNew, 6);
    lv_textarea_set_placeholder_text(ui_TextAreaConfigPINNew, "New PIN");
    lv_textarea_set_one_line(ui_TextAreaConfigPINNew, true);
    lv_textarea_set_password_mode(ui_TextAreaConfigPINNew, true);
    lv_obj_set_style_text_font(ui_TextAreaConfigPINNew, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonConfigPINOK = lv_btn_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_ButtonConfigPINOK, 100);
    lv_obj_set_height(ui_ButtonConfigPINOK, 50);
    lv_obj_set_align(ui_ButtonConfigPINOK, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_ButtonConfigPINOK, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigPINOK, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigPINOK, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigPINOK, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigButtonPINOK = lv_label_create(ui_ButtonConfigPINOK);
    lv_obj_set_width(ui_LabelConfigButtonPINOK, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigButtonPINOK, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigButtonPINOK, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigButtonPINOK, "OK");
    lv_obj_set_style_text_color(ui_LabelConfigButtonPINOK, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigButtonPINOK, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigButtonPINOK, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonConfigPINCancel = lv_btn_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_ButtonConfigPINCancel, 100);
    lv_obj_set_height(ui_ButtonConfigPINCancel, 50);
    lv_obj_set_align(ui_ButtonConfigPINCancel, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_ButtonConfigPINCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonConfigPINCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonConfigPINCancel, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonConfigPINCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigButtonPINCancel = lv_label_create(ui_ButtonConfigPINCancel);
    lv_obj_set_width(ui_LabelConfigButtonPINCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigButtonPINCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelConfigButtonPINCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelConfigButtonPINCancel, "CANCEL");
    lv_obj_set_style_text_color(ui_LabelConfigButtonPINCancel, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelConfigButtonPINCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelConfigButtonPINCancel, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelConfigPINMessage = lv_label_create(ui_PanelConfigPIN);
    lv_obj_set_width(ui_LabelConfigPINMessage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelConfigPINMessage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelConfigPINMessage, 0);
    lv_obj_set_y(ui_LabelConfigPINMessage, -60);
    lv_obj_set_align(ui_LabelConfigPINMessage, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_LabelConfigPINMessage, "");

    ui_KeyboardConfig = lv_keyboard_create(ui_ScreenConfig);
    lv_obj_set_width(ui_KeyboardConfig, 320);
    lv_obj_set_height(ui_KeyboardConfig, 150);
    lv_obj_add_flag(ui_KeyboardConfig, LV_OBJ_FLAG_HIDDEN);     /// Flags

    // config events
    lv_obj_add_event_cb(ui_TextAreaConfigSSID, ui_event_TextAreaConfigSSID, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaConfigWifiPassword, ui_event_TextAreaWifiPassword, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaConfigLNbitsHost, ui_event_TextAreaConfigLNbitsHost, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaConfigDeviceID, ui_event_TextAreaConfigDeviceID, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaConfigServoClosed, ui_event_TextAreaConfigServoClosed, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaConfigServoOpen, ui_event_TextAreaConfigServoOpen, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_KeyboardConfig, ui_event_KeyboardConfig, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_ButtonPIN, ui_event_ButtonPIN, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui_ButtonConfigDone, ui_event_ButtonConfigDone, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonConfigCancel, ui_event_ButtonConfigCancel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonConfigUpdate, ui_event_ButtonConfigUpdate, LV_EVENT_ALL, NULL);

    // PIN change panel events
    lv_obj_add_event_cb(ui_TextAreaConfigPINCurrent, ui_event_TextAreaConfigPINCurrent, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaConfigPINRepeat, ui_event_TextAreaConfigPINRepeat, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TextAreaConfigPINNew, ui_event_TextAreaConfigPINNew, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonConfigPINOK, ui_event_ButtonConfigPINOK, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonConfigPINCancel, ui_event_ButtonConfigPINCancel, LV_EVENT_ALL, NULL);


}

void ui_ScreenBierFlowing_screen_init(void)
{
    ui_ScreenBierFlowing = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenBierFlowing, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenBierFlowing, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenBierFlowing, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image3 = lv_img_create(ui_ScreenBierFlowing);
    lv_img_set_src(ui_Image3, &ui_img_instructions);
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);   /// 256
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);    /// 256
    lv_obj_set_y(ui_Image3, 20);
    lv_obj_set_align(ui_Image3, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_LabelInstructions = lv_label_create(ui_ScreenBierFlowing);
    lv_obj_set_width(ui_LabelInstructions, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelInstructions, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelInstructions, LV_ALIGN_TOP_MID);
    lv_obj_set_y(ui_LabelInstructions, 300);
    lv_label_set_text(ui_LabelInstructions, "HOLD UNDER THE TAP\nTILT GLASS SLIGHTLY");
    lv_obj_set_style_text_color(ui_LabelInstructions, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructions, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructions, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonBierStart = lv_btn_create(ui_ScreenBierFlowing);
    lv_obj_set_width(ui_ButtonBierStart, 90);
    lv_obj_set_height(ui_ButtonBierStart,90);
    lv_obj_set_x(ui_ButtonBierStart, 0);
    lv_obj_set_y(ui_ButtonBierStart, -50);
    lv_obj_set_align(ui_ButtonBierStart, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_ButtonBierStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonBierStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonBierStart, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonBierStart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelBierStart = lv_label_create(ui_ButtonBierStart);
    lv_obj_set_width(ui_LabelBierStart, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelBierStart, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelBierStart, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelBierStart, "TAP");
    lv_obj_set_style_text_color(ui_LabelBierStart, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelBierStart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelBierStart, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_anim_init(&ui_AnimateBierStart);
    lv_anim_set_var(&ui_AnimateBierStart, ui_ButtonBierStart);
    lv_anim_set_values(&ui_AnimateBierStart,90,95);
    lv_anim_set_time(&ui_AnimateBierStart,BUTTON_ANIMATE_TIME);
    lv_anim_set_playback_delay(&ui_AnimateBierStart,0);
    lv_anim_set_playback_time(&ui_AnimateBierStart,BUTTON_ANIMATE_TIME);
    lv_anim_set_repeat_delay(&ui_AnimateBierStart,0);
    lv_anim_set_repeat_count(&ui_AnimateBierStart, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_exec_cb(&ui_AnimateBierStart, ui_AnimateButtonCallback);

    ui_BarBierProgress = lv_bar_create(ui_ScreenBierFlowing);
    lv_bar_set_range(ui_BarBierProgress,0,TAPPROGRESS_STEPS);
    lv_bar_set_value(ui_BarBierProgress, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_BarBierProgress, 260);
    lv_obj_set_height(ui_BarBierProgress, 20);
    lv_obj_set_x(ui_BarBierProgress, 0);
    lv_obj_set_y(ui_BarBierProgress, -70);
    lv_obj_set_align(ui_BarBierProgress, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(ui_BarBierProgress, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BarBierProgress, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BarBierProgress, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BarBierProgress, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_BarBierProgress, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui_BarBierProgress,LV_OBJ_FLAG_HIDDEN);

    lv_obj_set_style_bg_color(ui_BarBierProgress, lv_color_hex(BB_BGCOLOR), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BarBierProgress, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ButtonBierStart, ui_event_ButtonBierStart, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenBierFlowing, ui_event_ScreenBierFlowing, LV_EVENT_ALL, NULL);

}

void ui_ScreenAdmin_screen_init(void)
{
    ui_ScreenAdmin = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenAdmin, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ScreenAdmin, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenAdmin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelAdminHeader = lv_obj_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_PanelAdminHeader, 320);
    lv_obj_set_height(ui_PanelAdminHeader, 50);
    lv_obj_clear_flag(ui_PanelAdminHeader, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_PanelAdminHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_PanelAdminHeader, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelAdminHeader, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelAdminHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminHeader = lv_label_create(ui_PanelAdminHeader);
    lv_obj_set_width(ui_LabelAdminHeader, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminHeader, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAdminHeader, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAdminHeader, "Administration");
    lv_obj_set_style_text_color(ui_LabelAdminHeader, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminHeader, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminHeader, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminVersion = lv_label_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_LabelAdminVersion, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminVersion, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelAdminVersion, 10);
    lv_obj_set_y(ui_LabelAdminVersion, 70);
    lv_label_set_text_fmt(ui_LabelAdminVersion, "Firmware version: %s",STR(FIRMWARE_VERSION));
    lv_obj_set_style_text_color(ui_LabelAdminVersion, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminVersion, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminVersion, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminServerVersion = lv_label_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_LabelAdminServerVersion, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminServerVersion, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelAdminServerVersion, 10);
    lv_obj_set_y(ui_LabelAdminServerVersion, 100);
    lv_label_set_text(ui_LabelAdminServerVersion, "");
    lv_obj_set_style_text_color(ui_LabelAdminServerVersion, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminServerVersion, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminServerVersion, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminBranding = lv_label_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_LabelAdminBranding, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminBranding, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelAdminBranding, 10);
    lv_obj_set_y(ui_LabelAdminBranding, 130);
    lv_label_set_text(ui_LabelAdminBranding, "");
    lv_obj_set_style_text_color(ui_LabelAdminBranding, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminBranding, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminBranding, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminWiFiStatus = lv_label_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_LabelAdminWiFiStatus, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminWiFiStatus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelAdminWiFiStatus, 10);
    lv_obj_set_y(ui_LabelAdminWiFiStatus, 160);
    lv_label_set_text(ui_LabelAdminWiFiStatus, "WiFi Status: ");
    lv_obj_set_style_text_color(ui_LabelAdminWiFiStatus, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminWiFiStatus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminWiFiStatus, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminWebSocketStatus = lv_label_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_LabelAdminWebSocketStatus, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminWebSocketStatus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelAdminWebSocketStatus, 10);
    lv_obj_set_y(ui_LabelAdminWebSocketStatus, 190);
    lv_label_set_text(ui_LabelAdminWebSocketStatus, "WebSocket Status: ");
    lv_obj_set_style_text_color(ui_LabelAdminWebSocketStatus, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminWebSocketStatus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminWebSocketStatus, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_ButtonAdminOpen = lv_btn_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_ButtonAdminOpen, 145);
    lv_obj_set_height(ui_ButtonAdminOpen, 70);
    lv_obj_set_x(ui_ButtonAdminOpen, 10);
    lv_obj_set_y(ui_ButtonAdminOpen, 220);
    lv_obj_set_align(ui_ButtonAdminOpen, LV_ALIGN_TOP_LEFT);
    lv_obj_add_flag(ui_ButtonAdminOpen, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAdminOpen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAdminOpen, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAdminOpen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminOpen = lv_label_create(ui_ButtonAdminOpen);
    lv_obj_set_width(ui_LabelAdminOpen, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminOpen, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAdminOpen, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAdminOpen, "OPEN");
    lv_obj_set_style_text_color(ui_LabelAdminOpen, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminOpen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminOpen, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonAdminClose = lv_btn_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_ButtonAdminClose, 145);
    lv_obj_set_height(ui_ButtonAdminClose, 70);
    lv_obj_set_x(ui_ButtonAdminClose, -10);
    lv_obj_set_y(ui_ButtonAdminClose, 220);
    lv_obj_set_align(ui_ButtonAdminClose, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_ButtonAdminClose, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAdminClose, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAdminClose, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAdminClose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminClose = lv_label_create(ui_ButtonAdminClose);
    lv_obj_set_width(ui_LabelAdminClose, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminClose, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAdminClose, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAdminClose, "CLOSE");
    lv_obj_set_style_text_color(ui_LabelAdminClose, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminClose, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminClose, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonAdminFree = lv_btn_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_ButtonAdminFree, 300);
    lv_obj_set_height(ui_ButtonAdminFree, 70);
    lv_obj_set_x(ui_ButtonAdminFree, 10);
    lv_obj_set_y(ui_ButtonAdminFree, 300);
    lv_obj_set_align(ui_ButtonAdminFree, LV_ALIGN_TOP_LEFT);
    lv_obj_add_flag(ui_ButtonAdminFree, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAdminFree, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAdminFree, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAdminFree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminFree = lv_label_create(ui_ButtonAdminFree);
    lv_obj_set_width(ui_LabelAdminFree, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminFree, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAdminFree, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAdminFree, "FREE");
    lv_obj_set_style_text_color(ui_LabelAdminFree, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminFree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminFree, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_ButtonAdminConfig = lv_btn_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_ButtonAdminConfig, 100);
    lv_obj_set_height(ui_ButtonAdminConfig, 50);
    lv_obj_set_x(ui_ButtonAdminConfig, 10);
    lv_obj_set_y(ui_ButtonAdminConfig, -10);
    lv_obj_set_align(ui_ButtonAdminConfig, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_ButtonAdminConfig, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAdminConfig, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAdminConfig, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAdminConfig, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminConfig = lv_label_create(ui_ButtonAdminConfig);
    lv_obj_set_width(ui_LabelAdminConfig, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminConfig, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAdminConfig, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAdminConfig, "CONFIG");
    lv_obj_set_style_text_color(ui_LabelAdminConfig, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminConfig, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminConfig, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_ButtonAdminCancel = lv_btn_create(ui_ScreenAdmin);
    lv_obj_set_width(ui_ButtonAdminCancel, 100);
    lv_obj_set_height(ui_ButtonAdminCancel, 50);
    lv_obj_set_x(ui_ButtonAdminCancel, -10);
    lv_obj_set_y(ui_ButtonAdminCancel, -10);
    lv_obj_set_align(ui_ButtonAdminCancel, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_ButtonAdminCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonAdminCancel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonAdminCancel, lv_color_hex(BB_BGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonAdminCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelAdminCancel = lv_label_create(ui_ButtonAdminCancel);
    lv_obj_set_width(ui_LabelAdminCancel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAdminCancel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelAdminCancel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAdminCancel, "DONE");
    lv_obj_set_style_text_color(ui_LabelAdminCancel, lv_color_hex(BB_FGCOLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAdminCancel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAdminCancel, &ui_font_UbuntuBoldItalic, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_add_event_cb(ui_ButtonAdminConfig, ui_event_ButtonAdminConfig, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonAdminCancel, ui_event_ButtonAdminCancel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonAdminOpen, ui_event_ButtonAdminOpen, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonAdminClose, ui_event_ButtonAdminClose, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonAdminFree, ui_event_ButtonAdminFree, LV_EVENT_ALL, NULL);
}


void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
#ifdef ESP32_3248S035C
    lv_disp_set_rotation(dispp, LV_DISP_ROT_180);
#endif

    lv_disp_set_theme(dispp, theme);
    ui_ScreenAbout_screen_init();
    // ui_ScreenMain_screen_init();
    // ui_ScreenPin_screen_init();
    // //ui_ScreenConfig_screen_init();
    // ui_ScreenBierFlowing_screen_init();
    lv_disp_load_scr(ui_ScreenAbout);
}

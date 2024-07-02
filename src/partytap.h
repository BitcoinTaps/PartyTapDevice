#ifndef _PARTYTAP_H_
#define _PARTYTAP_H_

#include <Arduino.h>
#include <tapconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PAYMENT_PIN_LEN 3  // The length in digits of the payment pin

extern String payment_pin;

extern TapConfig tapConfig;

void configureSwitches();

void tapStop();

void tapOpen(int i);

void tapClose(int i);

void beerStart();

void wantBierClicked(int item);

void expireInvoice();

void myDelay(uint32_t ms);

void restartTap();

void startFirmwareUpdate();

#ifdef __cplusplus
}
#endif


#endif
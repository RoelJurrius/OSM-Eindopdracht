#ifndef led_h
#define led_h

#include <stdbool.h>

#define ledRedSensor1 4
#define ledRedSensor2 5
#define ledGreenReset 6
#define ledYellowRequest 7

#define ledPulseMs 500UL

void ledsInit(void);

void ledRed1Set(bool on);
void ledRed2Set(bool on);

void ledGreenPulseStart(unsigned long nowMs);
void ledYellowPulseStart(unsigned long nowMs);
void ledsUpdate(unsigned long nowMs);

#endif
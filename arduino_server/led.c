#include "led.h"
#include <Arduino.h>

static bool greenPulseActive = false;
static bool yellowPulseActive = false;

static unsigned long greenPulseStartMs = 0UL;
static unsigned long yellowPulseStartMs = 0UL;

static void ledGreenOn(void);
static void ledGreenOff(void);

static void ledYellowOn(void);
static void ledYellowOff(void);

static void ledsAllOn(void);
static void ledsAllOff(void);

void ledsInit(void) {
  pinMode(ledRedSensor1, OUTPUT);
  pinMode(ledRedSensor2, OUTPUT);
  pinMode(ledGreenReset, OUTPUT);
  pinMode(ledYellowRequest, OUTPUT);

  ledsAllOff();
}

void ledRed1Set(bool on) {
  digitalWrite(ledRedSensor1, on ? HIGH : LOW);
}

void ledRed2Set(bool on) {
  digitalWrite(ledRedSensor2, on ? HIGH : LOW);
}

void ledGreenOn(void) {
  digitalWrite(ledGreenReset, HIGH);
}

void ledGreenOff(void) {
  digitalWrite(ledGreenReset, LOW);
  greenPulseActive = false;
}

void ledYellowOn(void) {
  digitalWrite(ledYellowRequest, HIGH);
}

void ledYellowOff(void) {
  digitalWrite(ledYellowRequest, LOW);
  yellowPulseActive = false;
}

void ledsAllOn(void) {
  digitalWrite(ledRedSensor1, HIGH);
  digitalWrite(ledRedSensor2, HIGH);
  digitalWrite(ledGreenReset, HIGH);
  digitalWrite(ledYellowRequest, HIGH);
}

void ledsAllOff(void) {
  digitalWrite(ledRedSensor1, LOW);
  digitalWrite(ledRedSensor2, LOW);
  digitalWrite(ledGreenReset, LOW);
  digitalWrite(ledYellowRequest, LOW);

  greenPulseActive = false;
  yellowPulseActive = false;
}

void ledGreenPulseStart(unsigned long nowMs) {
  greenPulseActive = true;
  greenPulseStartMs = nowMs;
  ledGreenOn();
}

void ledYellowPulseStart(unsigned long nowMs) {
  yellowPulseActive = true;
  yellowPulseStartMs = nowMs;
  ledYellowOn();
}

void ledsUpdate(unsigned long nowMs) {
  if (greenPulseActive &&
      (nowMs - greenPulseStartMs) >= ledPulseMs) {
    digitalWrite(ledGreenReset, LOW);
    greenPulseActive = false;
  }

  if (yellowPulseActive &&
      (nowMs - yellowPulseStartMs) >= ledPulseMs) {
    digitalWrite(ledYellowRequest, LOW);
    yellowPulseActive = false;
  }
}
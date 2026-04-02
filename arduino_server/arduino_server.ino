#include <Ethernet.h>

extern "C" {
#include "cserver.h"
#include "sensor_mock.h"
#include "led.h"
}

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10, 1, 200, 21);

EthernetServer server(80);
EthernetClient httpClient;

const int interruptPin = 2;
volatile bool interruptTriggered = false;

int clientAvailable() {
  return httpClient.connected() && httpClient.available();
}

char clientRead() {
  return httpClient.read();
}

char clientPeek() {
  return httpClient.peek();
}

void handleResetInterrupt() {
  interruptTriggered = true;
}

void updateRedLeds() {
  ledRed1Set(sensorBufferIsFull(SENSORID1));
  ledRed2Set(sensorBufferIsFull(SENSORID2));
}

void setup() {
  Serial.begin(9600);

  Ethernet.begin(mac, ip);
  server.begin();

  randomSeed(analogRead(A0));

  sensorsInit();
  ledsInit();

  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin),
                  handleResetInterrupt, RISING);

  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  unsigned long nowMs = millis();

  sensorsUpdate(nowMs);
  ledsUpdate(nowMs);
  updateRedLeds();

  if (interruptTriggered) {
    interruptTriggered = false;
    sensorsInterruptReset();
    ledGreenPulseStart(nowMs);
    updateRedLeds();
    Serial.println("interrupt reset uitgevoerd");
  }

  httpClient = server.available();

  if (httpClient) {
    Serial.println("new client");
    ledYellowPulseStart(nowMs);

    struct stream stream = {clientAvailable, clientPeek, clientRead};
    const char* response = handleResponse(stream);
    Serial.println(response);
    httpClient.print(response);

    delay(1);
    httpClient.stop();
    Serial.println("client disconnected");
  }
}
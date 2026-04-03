#include <Ethernet.h>
#include <string.h>
#include <stdio.h>

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

static char requestBuffer[256];
static size_t requestLength = 0;
static size_t requestIndex = 0;

static const unsigned long REQUEST_TIMEOUT_MS = 1000UL;

int bufferedAvailable() {
  return requestIndex < requestLength;
}

char bufferedRead() {
  if (requestIndex < requestLength) {
    char c = requestBuffer[requestIndex];
    requestIndex++;
    return c;
  }
  return '\0';
}

char bufferedPeek() {
  if (requestIndex < requestLength) {
    return requestBuffer[requestIndex];
  }
  return '\0';
}

void handleResetInterrupt() {
  interruptTriggered = true;
}

void updateRedLeds() {
  ledRed1Set(sensorBufferIsFull(SENSORID1));
  ledRed2Set(sensorBufferIsFull(SENSORID2));
}

int parseContentLength(const char* request) {
  const char* header = strstr(request, "Content-Length:");
  if (header == NULL) {
    return 0;
  }

  header += 15;
  while (*header == ' ') {
    header++;
  }

  return atoi(header);
}

bool requestComplete(void) {
  char* headerEnd = strstr(requestBuffer, "\r\n\r\n");
  if (headerEnd == NULL) {
    return false;
  }

  size_t headerSize = (size_t)(headerEnd - requestBuffer) + 4U;
  int contentLength = parseContentLength(requestBuffer);

  if (contentLength < 0) {
    return false;
  }

  return requestLength >= headerSize + (size_t)contentLength;
}

bool readClientRequest(EthernetClient& client) {
  unsigned long startMs = millis();
  requestLength = 0;
  requestIndex = 0;
  requestBuffer[0] = '\0';

  while (client.connected() && (millis() - startMs) < REQUEST_TIMEOUT_MS) {
    while (client.available()) {
      char c = (char)client.read();

      if (requestLength + 1U >= sizeof(requestBuffer)) {
        return false;
      }

      requestBuffer[requestLength] = c;
      requestLength++;
      requestBuffer[requestLength] = '\0';

      startMs = millis();

      if (requestComplete()) {
        return true;
      }
    }
  }

  return requestComplete();
}

void sendBasicResponse(EthernetClient& client,
                       int statusCode,
                       const char* statusText) {
  client.print("HTTP/1.0 ");
  client.print(statusCode);
  client.print(" ");
  client.print(statusText);
  client.print("\r\n");
  client.print("Connection: close\r\n");
  client.print("\r\n");
}

void sendNumericResponse(EthernetClient& client,
                         int statusCode,
                         const char* statusText,
                         double value) {
  char body[32];
  dtostrf((double)value, 0, 1, body); dtostrf((double)value, 0, 1, body);  // snprintf met %.1f gaf op AVR-Arduino '?' i.p.v. een correcte float-string

  client.print("HTTP/1.0 ");
  client.print(statusCode);
  client.print(" ");
  client.print(statusText);
  client.print("\r\n");
  client.print("Connection: close\r\n");
  client.print("Content-Length: ");
  client.print(strlen(body));
  client.print("\r\n");
  client.print("\r\n");
  client.print(body);
}

void sendResponseFromHandler(EthernetClient& client) {
  struct stream stream = {bufferedAvailable,
                          bufferedPeek,
                          bufferedRead};

  struct response response = handleRequest(stream);

  switch (response.code) {
    case OK_200_GET_AVG:
      sendNumericResponse(client, 200, "OK",
                          response.get_avg);
      break;

    case OK_200_GET_STDEV:
      sendNumericResponse(client, 200, "OK",
                          response.get_stdev);
      break;

    case OK_200_GET_ACTUAL:
      sendNumericResponse(client, 200, "OK",
                          response.get_actual);
      break;

    case CREATED_201_PUT_MODE_ACTIVE:
    case CREATED_201_PUT_MODE_PASSIVE:
    case CREATED_201_PUT_CBUFFSIZE:
    case CREATED_201_POST_MEASUREMENT:
    case CREATED_201_DELETE_MEASUREMENTS:
      sendBasicResponse(client, 201, "Created");
      break;

    case NOT_FOUND_404:
      sendBasicResponse(client, 404, "Not Found");
      break;

    case BAD_REQUEST_400:
    default:
      sendBasicResponse(client, 400, "Bad Request");
      break;
  }
}

bool isRootHealthCheck(void) {
  return strcmp(requestBuffer,
                "GET / HTTP/1.0\r\n\r\n") == 0;
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

    if (readClientRequest(httpClient)) {
      Serial.println("request received:");
      Serial.println(requestBuffer);

      if (isRootHealthCheck()) {
        sendBasicResponse(httpClient, 200, "OK");
      } else {
        sendResponseFromHandler(httpClient);
      }
    } else {
      Serial.println("invalid or incomplete request");
      sendBasicResponse(httpClient, 400, "Bad Request");
    }

    delay(1);
    httpClient.stop();
    Serial.println("client disconnected");
  }
}
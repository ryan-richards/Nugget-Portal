#include "Arduino.h"

#pragma once

class WifiControl {
public:
    WifiControl();
    static void startSoftAccessPoint(const char *ssid, const char *password, const IPAddress &localIP, const IPAddress &gatewayIP);
};


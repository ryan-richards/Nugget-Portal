// Buttons.cpp

#include "Buttons.h"
#include <Bounce2.h>
#include "Vars.h"
#include "Screen.h"
#include "WifiControl.h"

Bounce b = Bounce();

const int buttonPins[] = {up_btn, dn_btn, lt_btn, rt_btn};
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);

Bounce buttons[numButtons];
int currentSSIDIndex = 0;  // Initialize the current SSID index to 0
const char* activeAP = nullptr; // Store the currently active AP SSID

// Define the ssids array with actual SSID values
const char* ssids[numSSIDs] = {
    "Guest_Wifi",
    "Starbucks_Wifi",
    "BelfastWiFi",
    "Costa_Free_WiFi",
    "Customer_WiFi"
};

Buttons::Buttons() {
}

void Buttons::setupButtons() {
  for (int i = 0; i < numButtons; i++) {
    buttons[i].attach(buttonPins[i], INPUT_PULLUP);
    buttons[i].interval(5); // Adjust the debounce interval if needed
  }
}

void Buttons::updateButtons() {
  for (int i = 0; i < numButtons; i++) {
    buttons[i].update();

    // Check if a button was pressed (fell)
    if (buttons[i].fell()) {
      switch (i) {
        case 0: // Button 0 (up_btn) was pressed
          // Example: send the selected SSID to the startSoftAccessPoint function
          if (currentSSIDIndex >= 0 && currentSSIDIndex < numSSIDs) {
            Screen::displayStartingAP(2);
            const char *selectedSSID = ssids[currentSSIDIndex];
            WifiControl::startSoftAccessPoint(selectedSSID, NULL, localIP, gatewayIP);
            activeAP = selectedSSID; // Update the active AP
            updateScreenWithActiveSSID();
            Screen::displayWaitingForVictim();
          }
          break;
        case 1: // Button 1 (dn_btn) was pressed
          // Add your logic for the "down" button here
          // Example: perform an action for the "down" button
          Screen::displayWaitingForVictim();
          break;
        case 2: // Button 2 (lt_btn) was pressed
          // Add your logic for the "left" button here
          // Example: cycle to the previous SSID
          currentSSIDIndex = (currentSSIDIndex - 1 + numSSIDs) % numSSIDs;
          updateScreenWithActiveSSID();
          break;
        case 3: // Button 3 (rt_btn) was pressed
          // Add your logic for the "right" button here
          // Example: cycle to the next SSID
          currentSSIDIndex = (currentSSIDIndex + 1) % numSSIDs;
          updateScreenWithActiveSSID();
          break;
      }
    }
  }
}

void Buttons::updateScreenWithActiveSSID() {
  Screen::updateSectionText(ssids[currentSSIDIndex]);
}

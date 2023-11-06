#include "Arduino.h"

#pragma once

class Screen {
public:
    Screen();
    static void initDisplay();
    static void displayWaitingForVictim();
    static void displayCredsFound(String username, String password);
    static void displaySplash(uint8_t sec);
    static void updateSectionText(const char* newText);

private:
    static const char* sectionText;
};

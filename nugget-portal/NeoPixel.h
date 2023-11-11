#ifndef NeoPixel_h
#define NeoPixel_h

#include <Arduino.h>

class NeoPixel {
public:
  NeoPixel();
  static void setupNeoPixel();
  static void setNeoPixelColour(String colour);
};

#endif
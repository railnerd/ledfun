#include "Arduino.h"

struct Pixel {
  byte r,g,b;
};


void InitPixels(int clockPin,int dataPin);
void SendPixels(int nPixels, struct Pixel * pixels);

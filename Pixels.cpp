#include "Pixels.h"

int _clockPin,_dataPin;

void InitPixels(int clockPin,int dataPin)
{
  _clockPin = clockPin;
  _dataPin = dataPin;

  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void Send32Data(unsigned long data)
{
  int bits=32;

  while (bits--)
  {
    digitalWrite(_clockPin, LOW);
    digitalWrite(_dataPin, (data & 0x80000000) ? HIGH : LOW);
    delayMicroseconds(20); 
    digitalWrite(_clockPin, HIGH);
    delayMicroseconds(20);   
    data <<= 1;
  }
}

void SendRGBPixel(byte r, byte g, byte b)
{
  unsigned long int rgbCode = 0xc0000000;            // 31-30: 1,1
  rgbCode |= (unsigned long int) (~b & 0xc0) << 22;  // 29-28: !B7,!B6
  rgbCode |= (unsigned long int) (~g & 0xc0) << 20;  // 27-26: !G7,!G6
  rgbCode |= (unsigned long int) (~r & 0xc0) << 18;  // 25-24: !R7,!R6
  rgbCode |= (unsigned long int) b << 16;
  rgbCode |= (unsigned long int) g << 8;
  rgbCode |= (unsigned long int) r;
  Send32Data(rgbCode);
}


void SendPixels(int nPixels, struct Pixel * pixels) {
  Send32Data(0);
  for (int i=0; i<nPixels; i++) {
    SendRGBPixel(pixels[i].r,pixels[i].g,pixels[i].b);
  }
  Send32Data(0);
}


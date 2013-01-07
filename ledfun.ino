#include "Pixels.h"
#include "Signals.h"

enum {
  CLKPIN = 2,
  DATAPIN = 3
};

void setup()  {
  InitPixels(CLKPIN,DATAPIN);
}

Pixel pixels[4] = {
    GREEN,YELLOW,RED,LUNAR
};

enum {
  DARK_STATE=0,
  FADEIN_STATE,
  ON_STATE,
  FADEOUT_STATE,
};

int state = ON_STATE;
int timer = 0;

void loop()
{
  SendPixels(4,pixels);

  switch (state) {

  case FADEIN_STATE:
    if (pixels[1].r < 64) {
      pixels[1].r += 16;
      pixels[1].g += 16;
    } 
    else {
      pixels[1].r = 64;
      pixels[1].g = 64;
      state = ON_STATE;
    }
    timer = 40;
    break;

  case FADEOUT_STATE:
    if (pixels[1].r > 4) {
      pixels[1].r -= 4;
      pixels[1].g -= 4;
    } 
    else {
      pixels[1].r = 0;
      pixels[1].g = 0;
      state = DARK_STATE;
    }
    timer = 50;
    break;

  case DARK_STATE:
    if ((timer--) == 0) {
      state = FADEIN_STATE;
    }
    break;

  case ON_STATE:
    if ((timer--) == 0) {
      state = FADEOUT_STATE;
    }
    break;
  }
}


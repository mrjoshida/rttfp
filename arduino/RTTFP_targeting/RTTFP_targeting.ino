#include <noise.h>
#include <Adafruit_GFX.h>
#include <Adafruit_CompositeVideo.h>

Adafruit_NTSC40x24 display; // NTSC 40x24 currently the only supported type

uint8_t loc = 0;
uint8_t width = 0;
uint8_t width2 = 20;
uint8_t height;
uint8_t height2;

void setup() {
  if(!display.begin()) for(;;);   // Initialize display; halt on failure
}

void loop() {
  display.fillScreen(0);
  display.drawLine(0, 0, 20, 12, 255);
  display.drawLine(0, 24, 20, 12, 255);
  display.drawLine(40, 0, 20, 12, 255);
  display.drawLine(40, 24, 20, 12, 255);
  display.drawLine(loc, 0, loc, 24, 255);
  display.drawLine(40 - loc, 0, 40 - loc, 24, 255);

  height = map(width, 0, 40, 0, 24);
  display.drawRect(20 - (width/ 2), 12 - (height / 2), width, height, 255);
  width++;
  if (width > 40) {
    width = 0;
  }

  height2 = map(width2, 0, 40, 0, 24);
  display.drawRect(20 - (width2/ 2), 12 - (height2 / 2), width2, height2, 255);
  width2++;
  if (width2 > 40) {
    width2 = 0;
  }
  
  loc++;
  if (loc > 20) {
    loc = 0;
  }
  delay(100);                     // Wait 1/10 sec
  
}

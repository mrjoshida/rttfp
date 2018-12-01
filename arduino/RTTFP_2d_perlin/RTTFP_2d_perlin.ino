#include <noise.h>
#include <Adafruit_GFX.h>
#include <Adafruit_CompositeVideo.h>

#define PIN A8

uint8_t x_off = random(0, 1000);
uint8_t y_off = random(0, 1000);

Adafruit_NTSC40x24 display; // NTSC 40x24 currently the only supported type

void setup() {
  if(!display.begin()) for(;;);   // Initialize display; halt on failure
}

void loop() {
  // display.fillScreen(0);          // Clear display
  for (uint8_t x = 0; x < 40; x++) {
    for (uint8_t y = 0; y < 24; y++) {
      display.drawPixel(x, y, inoise8(x_off + x, y_off + y));
    }
  }
  y_off += 0.05;
  delay(100);                     // Wait 1/10 sec
  
}

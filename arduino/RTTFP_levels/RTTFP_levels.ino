#include <noise.h>
#include <Adafruit_GFX.h>
#include <Adafruit_CompositeVideo.h>

#define PIN A8

uint8_t radius = 8;


Adafruit_NTSC40x24 display; // NTSC 40x24 currently the only supported type

void setup() {
  if(!display.begin()) for(;;);   // Initialize display; halt on failure
}

void loop() {
  display.fillScreen(0);          // Clear display
  display.setCursor(4, 4);        // Inset slightly to avoid overscan area
  uint8_t level = map(inoise8(millis()), 0, 255, 0, 24);
  display.setCursor(2, 2);
  display.print(level);
  display.fillRect(5, 24 - level, 5, level, 255);
  display.fillCircle(25, 12, radius, 255);
  radius--;
  if (radius <= 0) {
    radius = 8;
  }
  delay(100);                     // Wait 1/10 sec
  
}

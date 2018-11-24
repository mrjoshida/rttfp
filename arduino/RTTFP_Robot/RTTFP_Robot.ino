#include "FastLED.h"
#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 16
#define LEFTBUTTON 4
#define RIGHTBUTTON 5
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CRGB center[10];

uint8_t mode = 0;

void setup() {
  pinMode(LEFTBUTTON, INPUT);
  pinMode(RIGHTBUTTON, INPUT);
  FastLED.addLeds<NEOPIXEL, 0>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 2>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 3>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 10>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 9>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 6>(leds[5], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 17>(center, 10);
}

void loop() {
  if (digitalRead(LEFTBUTTON)) {
    mode = 0;
  }
  if (digitalRead(RIGHTBUTTON)) {
    mode = 1;
  }

  if (mode == 0) {
    // This outer loop will go over each strip, one at a time
    for(int x = 0; x < NUM_STRIPS; x++) {
      // This inner loop will go over each led in the current strip, one at a time
      for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
        leds[x][i] = CRGB::Red;
        FastLED.show();
        leds[x][i] = CRGB::Black;
        delay(100);
      }
    }
  } else if (mode == 1) {
      for(int dot = 0; dot < 10; dot++) { 
          center[dot] = CRGB::Blue;
          FastLED.show();
          // clear this led for the next time around the loop
          center[dot] = CRGB::Black;
          delay(30);
      }
  }
}

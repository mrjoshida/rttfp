#include <CircularBuffer.h>
#include "FastLED.h"
#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 16
#define LEFTBUTTON 4
#define RIGHTBUTTON 19
#define TOGGLE 21
#define DELAY 30

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
CRGB center[10];

CircularBuffer<uint8_t, 10> stack;

uint8_t mode = 1;
uint8_t error_pos = 0;
uint8_t center_pos = 0;
long previousMillis;
int elapsed;

void setup() {
  pinMode(LEFTBUTTON, INPUT);
  pinMode(RIGHTBUTTON, INPUT);
  pinMode(TOGGLE, INPUT);
  attachInterrupt(digitalPinToInterrupt(LEFTBUTTON), change_mode, CHANGE);
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
    mode = 1;
    FastLED.clear();
  }
  if (digitalRead(RIGHTBUTTON)) {
    mode = -1;
    FastLED.clear();
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > DELAY) {
    previousMillis = currentMillis;
    if (mode == 1) {
      normal_mode();
    } else {
      error_mode();
    }
  }
}

void change_mode() {
  mode *= -1;
}

void normal_mode() {
  FastLED.clear();
  if (stack.isFull()) {
    uint8_t old = stack.shift();
  }
  uint8_t i = random8(NUM_STRIPS * NUM_LEDS_PER_STRIP);
  stack.push(i);
  for (i = 0; i < stack.size(); i++) {
    set_led(i, CHSV(map(stack[i], 0, NUM_STRIPS * NUM_LEDS_PER_STRIP, 0, 255),255,255));
  }
  //for (i = 0; i < 10; i++) {
  center[center_pos] = CHSV(127, 255, 255);
  //}
  FastLED.show();
  center_pos = (center_pos + 1) % 10;
}

void error_mode() {
  FastLED.clear();
  uint8_t i;
  for (i = 0; i < NUM_STRIPS; i++) {
    for (uint8_t j = 0; j <= error_pos; j++) {
      leds[i][j] = CHSV(0, 255, map(j, 0, error_pos, 0, 255));
    }
  }
  uint8_t brightness = map(error_pos, 0, NUM_LEDS_PER_STRIP, 255, 0);
  for (i = 0; i < 10; i++) {
    center[i] = CHSV(0, 255, brightness);
  }
  FastLED.show();
  error_pos = (error_pos + 1) % NUM_LEDS_PER_STRIP;
}

CRGB set_led(uint8_t i, CRGB color) {
  uint8_t y = stack[i] / NUM_STRIPS;
  uint8_t x = stack[i] % NUM_STRIPS;
  return leds[x][y] = color;
}


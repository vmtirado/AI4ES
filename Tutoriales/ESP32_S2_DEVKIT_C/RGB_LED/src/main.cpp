#include <Arduino.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"

// put function declarations here:
#define LEDS_COUNT 1
#define LEDS_PIN 18
#define CHANNEL 0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL);
void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.setBrightness(15);
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.setLedColorData(0,0,0,255);
  delay(500);
  strip.setLedColorData(0,255,0,0);
  
}

// put function definitions here: 
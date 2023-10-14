#include <Arduino.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"
// put function declarations here:

#define LEDS_COUNT 1
#define LEDS_PIN 18
#define CHANNEL 0
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL);

int delay_ms=500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(15);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){
    char data[64];
    int bytesRead= Serial.readBytesUntil('\n', data, sizeof(data)-1);
    data[bytesRead]='\0'; // Terminator character

    Serial.print("data: ");
    Serial.println(data);

    int delay_rate =atoi(data);

    if(delay_rate>0){
      delay_ms= delay_rate;
    }

  }

  strip.setLedColorData(0,0,0,255);
  delay(delay_ms);
  strip.setLedColorData(0,255,0,0);
  delay(delay_ms);

}


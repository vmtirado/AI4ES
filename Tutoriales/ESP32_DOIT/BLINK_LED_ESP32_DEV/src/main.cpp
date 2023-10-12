#include <Arduino.h>

// put function declarations here:
#define LED 2
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED,LOW);
}

// put function definitions here:
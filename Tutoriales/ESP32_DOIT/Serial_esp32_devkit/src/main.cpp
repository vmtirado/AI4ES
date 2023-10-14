#include <Arduino.h>
// put function declarations here:


#define LED 2

int delay_ms=500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED,OUTPUT);

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

  digitalWrite(LED,HIGH);
  delay(delay_ms);
  digitalWrite(LED,LOW);

  delay(delay_ms);

}


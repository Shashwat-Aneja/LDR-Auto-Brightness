/*
  LDR Auto-Brightness Controller (v1.1)
  -------------------------------------
  Automatically adjusts LED brightness based on ambient light using an
  LDR sensor. A low-pass filter prevents small ADC fluctuations from
  causing visible brightness flicker.
*/

#include "BrightnessFilter.h"

// Pin Definitions
const int ldrPin = A0;
const int ledPin = 9;

// Sensor and output values
int sensorValue = 0;
int brightness = 0;
BrightnessFilter brightnessFilter(0.2f);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  Serial.println("LDR Auto-Brightness System Ready");
  Serial.println("Reading: LDR Input | Output: LED Brightness");
}

void loop() {
  sensorValue = analogRead(ldrPin);
  brightness = brightnessFilter.update(sensorValue);

  analogWrite(ledPin, brightness);

  Serial.print("LDR: ");
  Serial.print(sensorValue);
  Serial.print(" | Filtered: ");
  Serial.print(brightnessFilter.filteredSensorValue(), 1);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  delay(100);
}

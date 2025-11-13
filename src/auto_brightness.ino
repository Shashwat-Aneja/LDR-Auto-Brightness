/*
  LDR Auto-Brightness Controller (v1.0)
  -------------------------------------
  Automatically adjusts LED brightness based on ambient light using an 
  LDR sensor. Demonstrates analog sensing, PWM output, and smooth brightness
  control. Designed as a small embedded-systems project for academic use.
*/

// Pin Definitions
const int ldrPin = A0;     // Analog input from LDR voltage divider
const int ledPin = 9;      // PWM output for LED brightness (D9 supports PWM)

// Variables
int sensorValue = 0;       // Raw LDR reading (0–1023)
int brightness = 0;        // PWM value (0–255)

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  Serial.println("LDR Auto-Brightness System Ready");
  Serial.println("Reading: LDR Input | Output: LED Brightness");
}

void loop() {
  // Read LDR value
  sensorValue = analogRead(ldrPin);

  // Convert 0–1023 to 0–255 PWM range
  brightness = map(sensorValue, 0, 1023, 255, 0);
  // (In bright light: high input → dim LED; In darkness: low input → bright LED)

  // Apply brightness to LED
  analogWrite(ledPin, brightness);

  // Debug information
  Serial.print("LDR: ");
  Serial.print(sensorValue);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  delay(100);
}

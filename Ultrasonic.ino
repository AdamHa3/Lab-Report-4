#include <LiquidCrystal.h>   // LCD library for 16x2 displays

// Ultrasonic sensor pins
const int Trig = 8;          // Trigger pin sends the ultrasonic pulse
const int Echo = 9;          // Echo pin receives the reflected pulse

// LCD pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Creating the LCD object with the wiring I chose
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variables for time and distance calculations
float distance, duration;

void setup() {
  Serial.begin(9600);        // For debugging through Serial Monitor

  pinMode(Trig, OUTPUT);     // Trigger pin must be an output
  pinMode(Echo, INPUT);      // Echo pin listens for the pulse

  lcd.begin(16, 2);          // Initialize LCD as 16x2
}

void loop() {

  // ---- Send Ultrasonic Pulse ----
  digitalWrite(Trig, LOW);    // Make sure trigger is LOW before pulse
  delayMicroseconds(2);       // Small delay to stabilize
  digitalWrite(Trig, HIGH);   // Send a 10µs pulse
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // Turn trigger off

  // ---- Measure Echo Time ----
  duration = pulseIn(Echo, HIGH);   // Measure how long the echo pin stays HIGH

  // ---- Convert Time to Distance ----
  // Distance = (time / 2) * speed of sound (0.0343 cm/µs)
  distance = (duration / 2) * 0.0343;

  // ---- Check if Distance is Valid ----
  if (distance >= 400 || distance <= 2) {
    lcd.clear();                  // Clear LCD
    lcd.setCursor(0, 0);          // Top-left corner
    lcd.print("Out of range");    // Object too close or too far
  }

  else {
    lcd.clear();                  // Clear previous reading

    lcd.setCursor(0, 0);          // First line
    lcd.print("Distance = ");

    lcd.setCursor(0, 1);          // Second line (corrected from row 2)
    lcd.print(distance);          // Show the calculated distance
    lcd.print(" cm");             // Add units

    lcd.print("       ");         // Extra spaces to erase leftover characters
    delay(100);                   // Small delay to prevent flickering
  }

  delay(500);                     // Update every half second
}

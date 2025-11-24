lcd/*
  My Ohm Meter Project
  ----------------------------
  What this program does:
    - Reads the voltage from a voltage divider
    - Calculates the unknown resistance using Ohm’s law
    - Shows the value on a 16x2 LCD
    - Uses a custom Ω symbol that I created myself

  Wiring for my LCD:
    RS → 12
    EN → 11
    D4 → 5
    D5 → 4
    D6 → 3
    D7 → 2
    RW → GND
    VSS → GND
    VCC → +5V
    VO → middle pin of contrast potentiometer

  Voltage Divider:
      +5V
       |
       R_known (10kΩ)
       |
      A0  ← I measure voltage here
       |
       R_unknown (this is the resistor I want to measure)
       |
      GND
*/

#include <LiquidCrystal.h>   // LCD library for 16x2 displays

// LCD pin assignments (makes wiring easier to understand)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Creating the LCD object using my chosen pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Custom 5x8 Ω character for the LCD
byte omega[8] = {
  0b00000,  // Row 1 (empty)
  0b01110,  // Row 2 (top curve)
  0b10001,  // Row 3 (sides)
  0b10001,  // Row 4
  0b10001,  // Row 5
  0b01010,  // Row 6 (legs)
  0b11011,  // Row 7 (feet)
  0b00000   // Row 8 (empty)
};

// My known resistor value in the voltage divider (10kΩ)
const float R_known = 10000.0;

void setup() {
  lcd.begin(16, 2);          // Setting up my LCD as a 16x2 screen
  lcd.createChar(0, omega);  // Saving Ω symbol in memory slot 0
}

void loop() {

  // Reading the analog input from A0 (0–1023 range)
  int sensorValue = analogRead(A0);

  // Converting the ADC value to an actual voltage
  float Vout = sensorValue * (5.0 / 1023.0);

  // Calculating current through the known resistor
  float I = (5.0 - Vout) / R_known;

  // Using Ohm’s Law: R = V / I
  float R_unknown = Vout / I;

  // I check for impossible values (to avoid dividing by zero)
  if (I == 0) {
    lcd.clear();                   // Wipe the screen
    lcd.setCursor(0, 0);           // Start at top-left
    lcd.print("Ohm Meter Ready!"); // Small startup message
    delay(1000);                   // Pause so I can read it

    // Simple scrolling animation for fun
    for (int i = 0; i < 38; i++) {
      lcd.scrollDisplayRight();
      delay(150);
    }
  }

  else {
    lcd.clear();                   // Clear screen for the new reading

    lcd.setCursor(0, 0);           // Top line
    lcd.print("Resistance:");      // Just a label

    lcd.setCursor(0, 1);           // Second line
    lcd.print(R_unknown, 2);       // Show value with 2 decimals
    lcd.write(byte(0));            // Print my custom Ω symbol
    lcd.print("      ");           // Padding so old digits get erased

    delay(500);                    // Slow down updates so the display doesn’t flicker
  }
}

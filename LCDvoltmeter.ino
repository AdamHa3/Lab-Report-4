/*
  My LCD Voltage Display Project
  ------------------------------------------------------------
  What this program does:
    - Uses a 16x2 LCD through the LiquidCrystal library.
    - Reads an analog voltage from pin A0.
    - Converts the raw analog value into an actual voltage.
    - Shows both the voltage and the elapsed time on the LCD.

  LCD Wiring I am using:
    RS  → 12
    EN  → 11
    D4  → 5
    D5  → 4
    D6  → 3
    D7  → 2
    RW  → GND
    VSS → GND
    VCC → +5V
    VO  → middle pin of 10k potentiometer (contrast control)

  The 10k Potentiometer:
    - One side to +5V
    - One side to GND
    - Middle terminal to LCD VO pin

  Purpose:
    - Practice using the LCD.
    - Practice reading analog values.
    - Practice displaying formatted data in real time.
*/

#include <LiquidCrystal.h>   // Library that controls LCD screens using the HD44780 chipset

// Pin mapping from Arduino to my LCD display
const int rs = 12;   // Register Select pin (tells LCD what type of data is sent)
const int en = 11;   // Enable pin (LCD reads data when this pin pulses)
const int d4 = 5;    // Data pins for 4-bit communication
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

// Creating the LCD object using the pins I chose above
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);        // Tell the LCD that it has 16 columns and 2 rows
  Serial.begin(9600);      // Open serial communication for optional debugging
}

void loop() {

  // Move cursor to the first line, first column
  lcd.setCursor(0, 0);

  // Read the analog value coming from A0 (0 → 1023)
  int rawValue = analogRead(A0);

  // Convert the raw ADC reading into a real-world voltage (based on 5V reference)
  float voltage = rawValue * (5.0 / 1023.0);

  // Print voltage on the LCD's first line
  lcd.print(voltage);

  // Print the same value in the Serial Monitor (helpful for debugging)
  Serial.print("Voltage = ");
  Serial.println(voltage);

  // Move cursor to second line
  lcd.setCursor(0, 1);

  // Print uptime (in seconds) since Arduino started running
  lcd.print(millis() / 1000);
}

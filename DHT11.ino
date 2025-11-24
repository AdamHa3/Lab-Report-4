// I’m using the DHT library to read temperature & humidity
#include <DHT.h>

// Library for controlling the 16x2 LCD display
#include <LiquidCrystal.h>

// Pin where I connected the DHT11 data pin
#define DHTPIN 2

// I’m specifying that my sensor is a DHT11 model
#define DHTTYPE DHT11

// Creating the DHT sensor object with the pin and sensor type
DHT dht(DHTPIN, DHTTYPE);

// Setting up the LCD pins in the order: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);       // Starting my 16x2 LCD display
  dht.begin();            // Initializing the DHT11 sensor
  lcd.print("DHT11 Sensor"); // Startup message so I know it's running
  delay(2000);            // Giving myself time to read the message
  lcd.clear();            // Clearing screen before starting readings
}

void loop() {

  // Reading humidity value from the DHT11
  float humidity = dht.readHumidity();

  // Reading temperature (Celsius) from the DHT11
  float temp = dht.readTemperature();

  // If the sensor gives invalid readings, I handle it here
  if (isnan(humidity) || isnan(temp)) {
    lcd.clear();           // Clear the LCD so the message is obvious
    lcd.print("Read Error!"); // Let myself know something went wrong
    delay(1000);           // Short delay before trying again
    return;                // Skip the rest of the loop due to error
  }

  // ---- Displaying temperature on first line ----
  lcd.setCursor(0, 0);     // Move to top-left of the LCD
  lcd.print("Temp: ");     // Label
  lcd.print(temp);         // Actual temperature value
  lcd.print(" C");         // Celsius unit

  // ---- Displaying humidity on second line ----
  lcd.setCursor(0, 1);     // Move to the second line
  lcd.print("Hum:  ");     // Label
  lcd.print(humidity);     // Actual humidity value
  lcd.print(" %");         // Percent unit

  delay(1000);             // Update readings every second
}

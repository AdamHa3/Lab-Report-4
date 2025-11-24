/*
  My Servo Control with Potentiometer
  ------------------------------------------------------------
  What this sketch does:
    - Reads a potentiometer connected to A0.
    - Converts the analog value to an angle from 0° to 180°.
    - Sends that angle to a servo motor on pin 9.
    - Prints the raw ADC reading to the Serial Monitor.
*/

#include <Servo.h>   // Library that lets me control hobby servos

// Creating a servo object so I can control the motor
Servo myservo;

// The potentiometer is connected to analog pin A0
int SensorValue = A0;

// Will store the raw analog reading
int val;

// Will store the converted angle value
float angle;

void setup() {
  myservo.attach(9);   // Connect the servo signal wire to pin 9
  Serial.begin(9600);  // Start the serial monitor for debugging
}

void loop() {

  // Read the voltage from the potentiometer (0 to 1023)
  val = analogRead(SensorValue);

  // Convert the ADC range (rough range of your pot) into 0–180 degrees
  angle = map(val, 210, 600, 0, 180);

  // Move the servo to the angle I calculated
  myservo.write(angle);

  // Small delay to make the servo move smoothly
  delay(15);

  // Debugging output so I can see what value the pot is reading
  Serial.print("Bitvalue = ");
  Serial.println(val);
}

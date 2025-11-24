// I'm using the Servo library to control a standard hobby servo
#include <Servo.h>

// Creating a servo object that I will use to control the motor
Servo myservo;

// The potentiometer is connected to analog pin A0
int potpin = A0;

// This variable will store the raw reading from the potentiometer
int val;

void setup() {
  myservo.attach(9);   // I connect the servo signal wire to pin 9 on the Arduino
}

void loop() {

  // Reading the potentiometer value (0 to 1023 range from the ADC)
  val = analogRead(potpin);

  // Converting (mapping) the 0–1023 value into a servo-friendly 0–180 degrees
  val = map(val, 0, 1023, 0, 180);

  // Sending the angle to the servo so it moves to the new position
  myservo.write(val);

  // Small delay to prevent the servo from jittering and give it time to move
  delay(15);
}

/*
PWM Breathing LED 

A **breathing LED** is an LED that smoothly fades in and out — just like how you breathe in and out slowly. 
This effect is often seen on power buttons or ambient lighting.

*/

// Define the LED pin
#define LED_PIN 12

void setup() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Fade in
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(LED_PIN, brightness);  // Set brightness level (0–255)
    delay(10);  // Wait to control breathing speed
  }

  // Fade out
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(LED_PIN, brightness);
    delay(10);
  }
}
  
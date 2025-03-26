// Make the LED Blink

// Set LED pin
int led_pin = 12;

void setup() {
  pinMode(led_pin, OUTPUT);  // Set pin as output
}

void loop() {
  digitalWrite(led_pin, HIGH); // Turn on LED
  delay(1000);                 // Wait 1 second
  digitalWrite(led_pin, LOW);  // Turn off LED
  delay(1000);                 // Wait 1 second
}
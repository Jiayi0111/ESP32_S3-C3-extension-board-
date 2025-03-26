/*
Ultrasonic Ranging Module HC - SR04
https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf

measures the distance to an object using an ultrasonic sensor (like HC-SR04) 
and prints the result to the Serial Monitor via UART.
*/


// Define pins for the ultrasonic sensor
#define TRIG 13
#define ECHO 14

void setup()
{
  // Initialize Serial communication at 9600 baud rate
  Serial.begin(9600);

  // Set pin modes for the ultrasonic sensor
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  // Clear the TRIG pin
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  // Send a 10-microsecond HIGH pulse to TRIG pin
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read the echo time in microseconds
  float time = pulseIn(ECHO, HIGH);

  // Calculate the distance in cm
  float distance = time * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait before taking another measurement
  delay(100);
}

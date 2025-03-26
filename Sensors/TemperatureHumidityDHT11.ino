/*
  reads temperature and humidity data from a DHT11 sensor
  connected to GPIO14 and prints the readings to the Serial Monitor via UART.

  - Uses the DHT library
  - Outputs humidity (%) and temperature (°C) every 2 seconds

  learn more about DHT11
  https://www.electronicwings.com/sensors-modules/dht11
*/

#include "DHT.h"

// Define the DHT sensor pin and type
#define DHTPIN 14
#define DHTTYPE DHT11

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT Sensor Test"));

  dht.begin();
}

void loop() {
  // Read humidity
  float humid = dht.readHumidity();
  // Read temperature in Celsius
  float temp = dht.readTemperature();

  // Print the readings to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.print("%  Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  delay(2000); // Wait 2 seconds before next reading
}

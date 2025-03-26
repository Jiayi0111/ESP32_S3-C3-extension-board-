// LMT87 Temperature Sensor
// Datasheet： https://www.ti.com/product/LMT87
#define SENSOR_PIN 32

void setup() {
  Serial.begin(115200);

  // Basic ADC config
  analogReadResolution(12);
  analogSetPinAttenuation(SENSOR_PIN, ADC_11db);
}

void loop() {
  int adcValue = analogRead(SENSOR_PIN);
  float voltage = adcValue * (3.3 / 4095.0) * 1000.0;
  float temperatureC = (2145.0 - voltage) / 11.0 + 25.0;

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" mV | Temp: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(1000);
}

# 🧪 ESP32 Analog Input with LMT87 Temperature Sensor 

In this tutorial, you’ll learn how to **read analog temperature data from the LMT87 sensor** using the **ESP32’s ADC (Analog-to-Digital Converter)**, and convert it into a readable Celsius temperature.

---

## 🔌 Analog vs Digital Signals

| Feature        | Analog                       | Digital                    |
|----------------|------------------------------|----------------------------|
| Type of Signal | Continuous (e.g., 0–3.3V)     | Discrete (e.g., 0V or 3.3V) |
| Example Sensor | LMT87 (temperature sensor)    | Button, PIR motion sensor   |
| ESP32 GPIO     | ADC pins (e.g., GPIO 32–39)   | All GPIOs                  |
| Function Used  | `analogRead()`                | `digitalRead()`            |

- **Analog** signals represent **gradual** changes in voltage. You use these when reading sensors like light sensors, potentiometers, and temperature sensors.
- **Digital** signals are either **HIGH (1)** or **LOW (0)** — like on/off switches.

🛠️ ESP32 supports **12-bit ADC** (0–4095) and up to **18 analog input pins**, making it ideal for precise sensor applications.


---

## ADC Channels on ESP32
ESP32 has **2 ADCs**: ADC1 and ADC2.

| GPIO | ADC | Notes              |
|------|-----|--------------------|
| 32   | ADC1| Recommended         |
| 33   | ADC1| Recommended         |
| 34–39| ADC1| Input only (no pullups) |
| 0, 2, 4, 12–15 | ADC2 | Avoid when WiFi is active

> ⚠️ **Avoid using ADC2 pins when using WiFi**, as they are shared with the radio.

## 📊 Wiring Diagram

| LMT87 Pin | Connect to |
|-----------|------------|
| VOUT      | GPIO 32 (Analog input on ESP32) |
| GND       | GND on ESP32 |
| VDD       | 3.3V on ESP32 |

> ⚠️ Power the LMT87 with **3.3V only**, not 5V.

---

## 🔍 How the LMT87 Sensor Works

The **LMT87** is a precision analog temperature sensor. Its output voltage **decreases as the temperature increases**.

| Temperature | Output Voltage |
|-------------|----------------|
| 0°C         | ~1.863V        |
| 25°C        | ~1.626V        |
| 50°C        | ~1.400V        |
| 75°C        | ~1.185V        |

We’ll use the simplified formula below:

```
Temperature (°C) = (2145 - millivolts) / 11 + 25
```

---

## 🧾 Arduino Code

```cpp
#define SENSOR_PIN 32  // GPIO connected to LMT87 VOUT

void setup() {
  Serial.begin(115200);

  // Configure ADC
  analogReadResolution(12);                // 12-bit ADC: 0~4095
  analogSetPinAttenuation(SENSOR_PIN, ADC_11db);  // 0~3.3V input range
}

void loop() {
  int adcValue = analogRead(SENSOR_PIN);
  float voltage = adcValue * (3.3 / 4095.0) * 1000.0; // mV
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
```

---

## 🧪 Sample Output

```
ADC: 1980 | Voltage: 1594.0 mV | Temp: 56.4 °C
ADC: 1875 | Voltage: 1509.1 mV | Temp: 63.6 °C
```

---

## 🛠️ Tuning the Formula

The LMT87’s behavior is **non-linear**, especially at extreme temperatures. For better accuracy:

- Use the **[LMT87 datasheet](https://www.ti.com/product/LMT87)**’s voltage-vs-temperature graph
- Calibrate using real measurements if possible
- Use a **lookup table** or **polynomial fit** for best results

---

## 🚀 Advanced Analog Functions on ESP32

Here are **all available analog tuning functions** you can use with ESP32:

### 📏 1. `analogReadResolution(resolution)`
Set the resolution of analogRead:

| Value | Range     |
|-------|-----------|
| 9     | 0–511     |
| 10    | 0–1023    |
| 11    | 0–2047    |
| 12    | 0–4095 (default) |

```cpp
analogReadResolution(12);
```

---

### 📐 2. `analogSetWidth(width)`
Same as above. Usually interchangeable.

```cpp
analogSetWidth(12);  // 12-bit resolution
```

---

### 🔁 3. `analogSetCycles(cycles)`
Sets the number of ADC clock cycles per sample.  
Range: 1 to 255. Default is **8**.

```cpp
analogSetCycles(16);  // More cycles = more accurate, slower
```

---

### 📊 4. `analogSetSamples(samples)`
Sets how many samples to average per reading.  
Increases accuracy/sensitivity.

```cpp
analogSetSamples(8);
```

---

### ⏱️ 5. `analogSetClockDiv(div)`
Sets the clock divider for ADC.  
Default is **1**, Range: 1–255.

```cpp
analogSetClockDiv(4);  // Slower = more stable
```

---

### 📉 6. `analogSetAttenuation(atten)`
Sets the attenuation (voltage range) **for all ADC pins**:

| Attenuation | Voltage Range | Notes |
|-------------|----------------|-------|
| `ADC_0db`   | ~0–800 mV       | Most accurate |
| `ADC_2_5db` | ~0–1.1 V        | |
| `ADC_6db`   | ~0–1.35 V       | |
| `ADC_11db`  | ~0–3.3 V        | Default |

```cpp
analogSetAttenuation(ADC_11db);
```

---

### 🔧 7. `analogSetPinAttenuation(pin, atten)`
Set attenuation **per pin** (instead of all):

```cpp
analogSetPinAttenuation(32, ADC_11db);
```

---

### 📎 8. `adcAttachPin(pin)`
Attach pin to ADC system (helpful if mode conflicts exist):

```cpp
adcAttachPin(32);
```

---

### 🔄 9. `adcStart(pin), adcBusy(pin), adcEnd(pin)`
Manual control over ADC conversion (for advanced use):

```cpp
adcAttachPin(32);
adcStart(32);

while (adcBusy(32)) {
  // wait for conversion
}

int value = adcEnd(32);  // Read ADC result
```


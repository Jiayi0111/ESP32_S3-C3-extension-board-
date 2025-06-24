## 🌤️ **Smart Curtain Control System**

This project integrates local temperature sensing, live weather data from the internet, servo motor control, and a TFT display to **automatically open or close a curtain** depending on environmental conditions.

---

## ⚙️ **Main Features**

| Feature                     | Description                                                                                 |
| --------------------------- | ------------------------------------------------------------------------------------------- |
| **WiFi connectivity**       | Connects to a WiFi network to fetch real-time weather data from OpenWeatherMap API.         |
| **Temperature sensing**     | Uses an analog temperature sensor (LMT87) to read the local ambient temperature.            |
| **Weather API integration** | Fetches current temperature, weather conditions, and wind speed for Singapore.              |
| **Servo motor control**     | Controls a curtain via a servo motor that opens or closes it smoothly in steps.             |
| **TFT screen display**      | Shows local temperature, API temperature, weather condition, wind speed, and system status. |
| **LED status indicator**    | A green LED lights up when the curtain system is active.                                    |

---

## 🔌 **Hardware and Pin Mapping**

| Component             | Purpose                   | Pin                   |
| --------------------- | ------------------------- | --------------------- |
| ESP32                 | Microcontroller           | -                     |
| Servo motor           | Controls curtain movement | GPIO 21               |
| Green LED             | System status indicator   | GPIO 22               |
| LMT87 sensor          | Local temperature sensing | GPIO 32               |
| TFT display (ILI9341) | UI display                | CS: 15, DC: 2, RST: 4 |

---

## 🧠 **How It Works (Main Logic)**

Every 5 seconds, the ESP32 performs the following steps:

1. **Reads local temperature** from the LMT87 sensor.
2. **Fetches weather data** (temperature, wind speed, weather type) from OpenWeatherMap API.
3. **Displays** the data on the TFT screen.
4. **Decides** whether to open the curtain based on:

   * Local temperature > 28°C
   * API-reported temperature > 28°C
   * Wind speed < 5.0 m/s

If all conditions are met, the system:

* Rotates the servo to open the curtain.
* Turns on the green LED.
* Updates the TFT display to show `ACTIVE`.

If not, it:

* Rotates the servo in reverse to close the curtain.
* Turns off the LED.
* Updates the TFT display to show `STANDBY`.

---

## 🧪 **Temperature Conversion Logic**

The LMT87 analog sensor output is converted to Celsius using:

```cpp
voltage = analogRead * (3.3 / 4095.0) * 1000.0;
temperature = (2145.0 - voltage) / 11.0 + 25.0;
```

This is based on the LMT87's analog voltage-to-temperature characteristic.

---

## 📺 **TFT Display Interface**

The screen shows:

* **Local Temperature** (from sensor)
* **API Temperature** (from OpenWeatherMap)
* **Weather Description** (e.g., “Clear”, “Rain”, etc.)
* **Wind Speed**
* **System Status** (either "ACTIVE" or "STANDBY")

---

## 🌐 **API Data Format Example (OpenWeatherMap)**

The API call returns JSON like:

```json
{
  "main": {
    "temp": 300.15
  },
  "weather": [{
    "main": "Clear"
  }],
  "wind": {
    "speed": 3.5
  }
}
```

The ESP32 extracts and converts this to usable information.

---

## ✅ **Summary of Accomplishments**

* Implemented reliable WiFi reconnection logic.
* Integrated OpenWeatherMap API for live data.
* Designed smooth servo-based curtain control with safety checks (wind).
* Built a clean TFT graphical UI.
* Combined hardware and software to create a responsive, real-time automation system.



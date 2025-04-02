
## 🖼️ ESP32 SPI Display Tutorial – Using ILI9341 with SPI

In this tutorial, you will learn how to use **SPI communication** on ESP32 to control a colorful **TFT LCD screen** (ILI9341). This is a common 240x320 resolution display that supports full graphics, colors, and text output.

---

### 🧠 Principle: What is SPI?

**SPI (Serial Peripheral Interface)** is a high-speed communication protocol used by microcontrollers to talk to peripherals like displays, memory, sensors, and more using **4 main wires**:

| Line | Function |
|------|----------|
| MOSI | Master Out Slave In (data from ESP32 to display) |
| MISO | Master In Slave Out (data from display to ESP32 – often unused for displays) |
| SCK  | Serial Clock (synchronizes data transfer) |
| CS   | Chip Select (enables specific device) |

### ✅ SPI Key Features:
- Full-duplex: supports **send and receive simultaneously**
- Faster than I²C
- Supports multiple devices via **individual CS (chip select) pins**
- Master–slave architecture (ESP32 is master)

### 🧠 SPI in Real Life

Think of SPI like a fast conversation between a boss (ESP32) and workers (TFT, SD card, etc). Each worker only listens when the boss selects them using their CS pin.

---

## ⚙️ Circuit Connection

Here’s a common wiring scheme for the **ILI9341 TFT display** with ESP32:

| Display Pin | Function       | Connect to ESP32 |
|-------------|----------------|------------------|
| VCC         | Power supply   | 3.3V             |
| GND         | Ground         | GND              |
| CS          | Chip Select    | GPIO **15**      |
| RESET       | Reset          | GPIO **4**       |
| DC/RS       | Data/Command   | GPIO **2**       |
| SDI/MOSI    | SPI Data In    | GPIO **23**      |
| SCK         | SPI Clock      | GPIO **18**      |
| LED         | Backlight      | 3.3V (or PWM)    |

> 📌 You only need **MOSI**, **SCK**, and **CS/DC/RST** for display communication — MISO is not used for ILI9341.

---

## 🧪 Code: Display Temperature and Status via SPI TFT

Here’s a minimal and working example that draws dummy weather info onto the TFT screen:

```cpp
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Define SPI TFT pins
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  drawMainUI();

  // Dummy data
  float dummyLocalTemp = 30.5;
  float dummyApiTemp = 29.8;
  String dummyWeather = "Clouds";
  float dummyWind = 3.2;
  String dummyStatus = "ACTIVE";

  updateDisplay(dummyLocalTemp, dummyApiTemp, dummyWeather, dummyWind);
  updateStatusArea(dummyStatus.c_str(), ILI9341_GREEN);
}

void loop() {
  // Nothing here
}

// UI Layout
void drawMainUI() {
  tft.setTextSize(2);
  tft.setCursor(20, 10);
  tft.println("Curtain Motor 4002D");
  tft.drawFastHLine(0, 35, 240, ILI9341_WHITE);
  
  tft.setTextSize(1);
  tft.setCursor(10, 45);  tft.print("Local Temp:");
  tft.setCursor(10, 65);  tft.print("API Temp:");
  tft.setCursor(10, 85);  tft.print("Weather:");
  tft.setCursor(10, 105); tft.print("Wind Speed:");
  tft.setCursor(10, 125); tft.print("Status:");
}

// Data Display
void updateDisplay(float localTemp, float apiTemp, String weather, float windSpeed) {
  tft.fillRect(100, 45, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 45);  tft.print(localTemp, 1); tft.print(" C");

  tft.fillRect(100, 65, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 65);  tft.print(apiTemp, 1);  tft.print(" C");

  tft.fillRect(100, 85, 140, 15, ILI9341_BLACK);
  tft.setCursor(100, 85);  tft.print(weather);

  tft.fillRect(100, 105, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 105); tft.print(windSpeed, 1); tft.print(" m/s");
}

void updateStatusArea(const char* text, uint16_t color) {
  tft.fillRect(100, 125, 100, 15, ILI9341_BLACK);
  tft.setTextColor(color);
  tft.setCursor(100, 125);
  tft.print(text);
  tft.setTextColor(ILI9341_WHITE);
}
```

---

## 🔍 How It Works

| Function | Explanation |
|----------|-------------|
| `Adafruit_ILI9341 tft(CS, DC, RST)` | Create a TFT object using defined SPI pins |
| `tft.begin()` | Initializes SPI and TFT display |
| `tft.setRotation()` | Sets the screen orientation (0–3) |
| `tft.fillScreen(color)` | Clears screen with given color |
| `tft.setCursor(x, y)` | Moves text cursor to (x, y) position |
| `tft.print()` | Prints text at cursor |
| `tft.fillRect(x, y, w, h, color)` | Clears area before updating text |
| `tft.drawFastHLine()` | Draws horizontal line |

---

## 🧰 Using SPI with Multiple Devices

SPI allows multiple devices to share the same **MOSI**, **MISO**, and **SCK** lines, but each one must have a **unique CS (Chip Select)**.

Example setup:
- TFT → CS = GPIO 15
- SD Card → CS = GPIO 5

You switch between them by pulling one CS low at a time.

---

### 📚 Useful Libraries

| Library | Purpose |
|---------|---------|
| `Adafruit_GFX.h` | Graphics drawing (used by many Adafruit displays) |
| `Adafruit_ILI9341.h` | Controls the ILI9341 TFT via SPI |
| `SPI.h` | Arduino’s SPI communication library |

---

## 🛠 SPI Pin Remapping on ESP32

ESP32 allows flexible pin mapping. You can remap SPI using:
```cpp
SPI.begin(SCK, MISO, MOSI, CS);
```
Or let the Adafruit library handle it with defaults.

> ⚠️ Be careful with MISO/MOSI confusion:  
> MOSI = Master Out → Slave In = ESP32 to screen

---

### 📦 What Happens Behind the Scenes

- The `SPI.h` library manages clock speed, data mode, and chip select
- `Adafruit_ILI9341` uses SPI to send pixel/command data to the screen
- `Adafruit_GFX` gives you higher-level text and shape drawing functions




---

### 📚 Further Reading

- 🔗 [Adafruit ILI9341 GitHub](https://github.com/adafruit/Adafruit_ILI9341)
- 🔗 [ESP32 SPI Docs (Arduino)](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/spi.html)
- 🔗 [Adafruit GFX Library Guide](https://learn.adafruit.com/adafruit-gfx-graphics-library)
- 🔗 [SPI Basics by SparkFun](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi)


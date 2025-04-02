
## 🖥️ ESP32 I2C Display Tutorial – Using OLED and LCD 1602 with I2C

In this tutorial, you will learn how to use **I2C communication** on ESP32 to control two commonly used displays:

- 🧾 **LCD 1602 with I2C backpack**  
- 📺 **SH1106 128x64 OLED display**

We'll also explain what I2C is, how it works, and how to connect multiple devices using just **two wires**.

---

### 🧠 Principle: What is I2C?

**I²C (Inter-Integrated Circuit)** is a communication protocol that allows microcontrollers like the ESP32 to talk to multiple peripherals (like sensors or displays) using **only two wires**:

| Line | Function |
|------|----------|
| SDA  | Serial Data Line (data transfer) |
| SCL  | Serial Clock Line (sync the data transfer) |

### ✅ I2C Key Features:
- 2-wire interface: **SDA** & **SCL**
- Each device has a **unique address**
- Supports multiple devices on one bus (multi-slave)
- Master–slave architecture (ESP32 is master)

### 🧠 I2C in Real Life

Think of I2C like a school classroom:
- The **ESP32** is the teacher (master)
- The **OLED and LCD** are students (slaves), each with their own **ID (address)**
- The teacher (ESP32) calls on each student by ID and asks them to speak (SDA) when the teacher claps (SCL)

> ⛓️ This shared communication saves GPIO pins and makes I2C great for expanding your system.

---

## ⚙️ Circuit Connection

| Device         | SDA Pin | SCL Pin | I2C Address |
|----------------|---------|---------|-------------|
| OLED Display   | GPIO 19 | GPIO 20 | `0x3C`      |
| LCD1602 Display| GPIO 19 | GPIO 20 | `0x27`      |

> 📝 On ESP32 DevKit, default I2C pins are typically **SDA = 21**, **SCL = 22**  
> But you can define any two GPIOs using `Wire.begin(SDA, SCL);`

---

## 🧪 Code: Display "Hello World" on OLED and LCD

Here’s a full working example to test both I2C displays:

```cpp
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <LiquidCrystal_I2C.h>

// Define I2C pins for ESP32 S3 (customizable)
const int SDAPin = 19;
const int SCLPin = 20;

// OLED Setup
#define oled_address 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G oled_display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// LCD1602 Setup
#define lcd_address 0x27
#define CHAR_NUM 16
#define LINE_NUM 2
LiquidCrystal_I2C lcd_display(lcd_address, CHAR_NUM, LINE_NUM);

void setup() {
  Serial.begin(9600);

  // Initialize I2C bus
  Wire.begin(SDAPin, SCLPin);

  // LCD init
  lcd_display.init();
  lcd_display.clear();
  lcd_display.backlight();

  lcd_display.setCursor(2, 0);
  lcd_display.print("LCD Display");

  lcd_display.setCursor(2, 1);
  lcd_display.print("at 0x27");

  // OLED init
  delay(250); // Power up delay
  oled_display.begin(oled_address, true);
  oled_display.display();
  delay(2000);

  oled_display.clearDisplay();
  oled_display.setTextSize(2);
  oled_display.setTextColor(SH110X_WHITE);
  oled_display.setCursor(0, 0);
  oled_display.println("OLED");

  oled_display.setCursor(0, 18);
  oled_display.println("Display1");

  oled_display.setCursor(0, 36);
  oled_display.println("at 0x3C");

  oled_display.display();
}

void loop() {
  // Nothing here – everything is shown in setup
}
```

---

## 🔍 How It Works

| Part | Explanation |
|------|-------------|
| `Wire.begin(SDA, SCL);` | Initialize I2C bus with custom pins |
| `Adafruit_SH1106G.begin(address)` | Starts OLED display at I2C address 0x3C |
| `LiquidCrystal_I2C.init()` | Starts LCD display at I2C address 0x27 |
| `setCursor()` | Moves the print position |
| `print()` | Prints text on screen |
| `display()` | Sends the OLED buffer to screen |

---

### 🛠 How to Scan I2C Devices

If you're unsure which address your display is using, upload this I2C scanner:

```cpp
#include <Wire.h>

void setup() {
  Wire.begin(19, 20); // SDA, SCL
  Serial.begin(115200);
  Serial.println("Scanning I2C...");

  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at 0x");
      Serial.println(i, HEX);
    }
  }
}

void loop() {}
```



---

### 📦 Organizing Arduino Libraries: `.h` and `.cpp` Files

In Arduino development, libraries like `LiquidCrystal_I2C` are usually made up of two files:

| File Type | Purpose |
|-----------|---------|
| `.h` (Header file) | Contains **declarations** of classes, functions, constants, and variables |
| `.cpp` (Source file) | Contains **actual implementations** of the functions declared in `.h` |

### 🧠 Why Use `.h` and `.cpp`?

This modular structure makes your code:
- Easier to **organize**
- More **readable**
- More **reusable** across projects

### 🗂 How to Add a Custom Library Manually

If you're not installing through the Library Manager, you can:

1. Download the `LiquidCrystal_I2C.h` and `LiquidCrystal_I2C.cpp` files  
2. Create a new Arduino sketch (e.g. `MyLCDTest.ino`)  
3. Save your sketch to a folder — Arduino will create one automatically  
4. Place both `.h` and `.cpp` files **inside that folder**

Now in your `.ino` file, you can simply use:
```cpp
#include "LiquidCrystal_I2C.h"
```

> ⚠️ If you use angle brackets like `#include <LiquidCrystal_I2C.h>`, Arduino looks in the global libraries folder. If you use quotes `""`, it looks in your sketch folder first.

---

## 🧰 LiquidCrystal_I2C Function Overview

After including the library, here are the most commonly used functions:

| Function | Description |
|----------|-------------|
| `LiquidCrystal_I2C(addr, cols, rows)` | Constructor to create LCD object. e.g. `0x27`, `16`, `2` |
| `init()` | Initializes the LCD |
| `clear()` | Clears the screen |
| `home()` | Moves cursor to top-left |
| `backlight()` / `noBacklight()` | Turns backlight on/off |
| `print()` | Prints text on the LCD |
| `setCursor(col, row)` | Moves the cursor to position (starting from 0,0) |
| `leftToRight()` / `rightToLeft()` | Sets text display direction |
| `cursor()` / `noCursor()` | Shows/hides cursor |
| `blink()` / `noBlink()` | Makes the cursor blink or not |
| `display()` / `noDisplay()` | Turns screen on/off (content remains) |

---

## 📘 Example Usage Recap

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2); // Address 0x27, 16 columns, 2 rows

void setup() {
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the backlight
  lcd.setCursor(0, 0); // Move cursor to top-left
  lcd.print("Hello!");
}
```

This will display "Hello!" on the first line of your LCD.

---


### 📚 Useful Resources

- 🔗 [I2C Wiki (SparkFun)](https://learn.sparkfun.com/tutorials/i2c/all)
- 🔗 [ESP32 Arduino Wire Library Docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/i2c.html)
- 🔗 [Adafruit SH110X OLED GitHub](https://github.com/adafruit/Adafruit_SH110X)
- 🔗 [LiquidCrystal_I2C Library GitHub](https://github.com/johnrickman/LiquidCrystal_I2C)


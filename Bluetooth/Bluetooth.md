

## 🔵 ESP32 Bluetooth Tutorial – Classic SPP vs BLE (Bluetooth Low Energy)

In this tutorial, you'll learn how to use **both Classic Bluetooth (SPP)** and **BLE (Bluetooth Low Energy)** with your ESP32 to wirelessly communicate with a smartphone or computer.

You’ll understand the **difference between SPP and BLE**, when to use each, and how to build simple programs to **send and receive data wirelessly** using both methods.

---

### 🧠 Principle: What is Bluetooth?

Bluetooth is a wireless technology standard that allows devices to exchange data over short distances. ESP32 supports **two Bluetooth protocols**:

| Bluetooth Type | Description | Use Case |
|----------------|-------------|----------|
| 🔵 **Classic Bluetooth (SPP)** | Works like a virtual serial port | Debugging, terminal communication |
| 🟦 **Bluetooth Low Energy (BLE)** | Efficient, low-power, event-driven | Sensors, mobile apps, fitness devices |

---

### 🧠 SPP vs BLE (Quick Comparison)

| Feature | Classic Bluetooth (SPP) | BLE (Bluetooth Low Energy) |
|--------|--------------------------|-----------------------------|
| Power Consumption | 🔋 Higher | ⚡ Very low |
| Communication Style | Stream-based (Serial-like) | Event-based (GATT Services/Characteristics) |
| Supported on iPhone | ❌ No | ✅ Yes |
| Easy to use for Serial | ✅ Yes | ❌ Requires GATT structure |
| Best For | Terminals, debug, data logs | Mobile apps, sensors, low-power devices |

> 📌 Use **SPP for simplicity and fast testing** (on Android only), and use **BLE for battery-friendly, cross-platform communication.**

---

## 🧪 Part 1: Classic Bluetooth (SPP) Example – Serial Communication

### 📲 Use Case: Send and receive text with phone (Android only)

### 🔧 Circuit: None needed (optional: connect LED to GPIO 2)

```cpp
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_SPP_Device");  // Bluetooth name
  pinMode(2, OUTPUT);
  Serial.println("Classic Bluetooth SPP started!");
}

void loop() {
  if (SerialBT.available()) {
    String received = SerialBT.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(received);
    
    SerialBT.print("Echo: ");
    SerialBT.println(received);

    if (received == "ON") digitalWrite(2, HIGH);
    if (received == "OFF") digitalWrite(2, LOW);
  }
}
```

### ✅ Test With:
- Android App: **Serial Bluetooth Terminal**  
- Pair with `ESP32_SPP_Device`, then connect and send commands like `ON`, `OFF`

---

## 🧪 Part 2: Bluetooth Low Energy (BLE) Example – GATT Server

### 📲 Use Case: Send data to iPhone or Android BLE app

### 🔧 Circuit: Optional LED on GPIO 2

```cpp
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic* pCharacteristic;
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("BLE Client Connected");
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("BLE Client Disconnected");
  }
};

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  BLEDevice::init("ESP32_BLE_Device");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService("180F");  // Battery Service UUID
  pCharacteristic = pService->createCharacteristic(
                      "2A19",  // Battery Level characteristic
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setValue("Hello from ESP32!");
  pService->start();

  pServer->getAdvertising()->start();
  Serial.println("BLE advertising started!");
}

void loop() {
  if (deviceConnected) {
    pCharacteristic->setValue("Updated at " + String(millis()));
    pCharacteristic->notify();
    delay(2000);
  }
}
```

### ✅ Test With:
- Android/iOS App: **nRF Connect** or **LightBlue**
- Connect to `ESP32_BLE_Device`, discover service `180F`, read/write `2A19`

---

## 🔍 How It Works

| Function | Classic SPP | BLE |
|----------|-------------|-----|
| `SerialBT.begin(name)` | Starts Bluetooth Serial | — |
| `BLEDevice::init()` | — | Initializes BLE stack |
| `SerialBT.readString()` | Reads from Bluetooth | — |
| `pCharacteristic->setValue()` | — | Sets value for BLE characteristic |
| `pCharacteristic->notify()` | — | Pushes updated value to client |

---

## 🛠 When to Use Which?

| Goal | Use This |
|------|-----------|
| Quickly test Bluetooth with Android | ✅ Classic SPP |
| Send sensor data to iPhone | ✅ BLE |
| Create a mobile app with BLE scanner | ✅ BLE |
| Serial-style debug monitor | ✅ SPP |
| Build a low-power fitness band or beacon | ✅ BLE |

---

## 📚 Useful Resources

- 🔗 [ESP32 Classic Bluetooth GitHub (SPP)](https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial)
- 🔗 [ESP32 BLE Arduino Examples](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE/examples)
- 🔗 [Serial Bluetooth Terminal App (Android)](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal)
- 🔗 [nRF Connect App (iOS/Android)](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-mobile)


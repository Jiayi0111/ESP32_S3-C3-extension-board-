# 🌐 ESP32 Wi-Fi Basics

The **ESP32** comes with built-in Wi-Fi, making it one of the most powerful and popular microcontrollers for IoT applications. In this tutorial, you'll learn how Wi-Fi works on ESP32 and how to connect it to a router using the Arduino IDE.


Connecting to Wi-Fi is something we do daily—just enter a **Wi-Fi SSID and password**, and your device is online. In the **Internet of Things (IoT)**, Wi-Fi is a key player, and **ESP32** makes it easy to build connected devices thanks to its **built-in Wi-Fi module**.

Smart homes, weather stations, and cloud-connected sensors are just a few examples of where Wi-Fi plays a vital role.

---

## 🔄 ESP32 Wi-Fi Modes

ESP32 supports two main Wi-Fi modes:

| Mode      | Description |
|-----------|-------------|
| **STA (Station)** | ESP32 connects to your home router like a phone or laptop. This is the most common mode. |
| **AP (Access Point)** | ESP32 creates its own Wi-Fi hotspot. Other devices can connect to it directly, but it won’t have internet access unless bridged. |

> 🔸 **Use STA mode** when you want ESP32 to connect to the internet via your router.

---

## 🔧 Hardware Setup

You don’t need any external Wi-Fi module. Just use an ESP32 development board and a **USB cable** to connect it to your computer.


---

## 🧾 Wi-Fi Functions in Arduino

Here are the most useful Wi-Fi functions from the **ESP32 WiFi library**:

### 🔌 `WiFi.begin(ssid, password)`
Connect to a Wi-Fi network.

```cpp
WiFi.begin("yourSSID", "yourPASSWORD");
```

### 🔌 `WiFi.disconnect()`
Disconnect from the current Wi-Fi network.

### 📶 `WiFi.status()`
Check connection status. Returns:

- `WL_CONNECTED` – Connected to Wi-Fi  
- `WL_DISCONNECTED` – Not connected  
- `WL_IDLE_STATUS` – Idle  
- `WL_NO_SSID_AVAIL` – Network not found

### 🌐 `WiFi.localIP()`
Returns the **local IP address** assigned by the router.

### 🔎 `WiFi.macAddress()`
Returns the **MAC address** of the ESP32.

### 📡 `WiFi.scanNetworks()`
Scans for available Wi-Fi networks. Returns the number of networks found.

### 📋 `WiFi.SSID(index)`
Returns the SSID of the network at the given index from scan results.

### 📈 `WiFi.RSSI(index)`
Returns the signal strength (RSSI) of the scanned network at the given index.

---

## 🧪 Example Code: Connect to Router

```cpp
#include <WiFi.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Do something with the connection
}
```

---

## 🛰️ Bonus: Scan Nearby Networks

```cpp
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Scanning...");

  int networks = WiFi.scanNetworks();
  for (int i = 0; i < networks; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" dBm)");
  }
}

void loop() {}
```

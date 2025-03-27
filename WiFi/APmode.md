# 📡 ESP32 Access Point (AP) Mode 

In this section, you’ll learn how to turn your **ESP32 into a Wi-Fi hotspot** (Access Point), allowing phones, tablets, or computers to **connect directly to the ESP32** without needing a router.

---

## 📡 What is AP Mode?

**AP (Access Point)** mode allows the ESP32 to **create its own Wi-Fi network**, just like a router.

Devices (like your phone or laptop) can **connect directly** to the ESP32’s Wi-Fi network without needing an internet connection.

| AP Mode Feature      | Description                       |
|----------------------|------------------------------------|
| Network Creator      | ESP32 creates its own SSID         |
| Internet Required?   | ❌ No (but local communication is possible) |
| Common Use Case      | Offline control panels, configuration UI, local device setup |

---

## 💡 When to Use AP Mode

Use AP mode when:

- There's **no router available** (e.g., outdoor or portable systems)
- You want to create a **local control page or config interface**
- You need a **direct connection** between ESP32 and a user device

---

## ⚙️ ESP32 AP Mode Features

- Create custom SSID and password  
- Control max number of clients  
- Get ESP32’s own IP address  
- Host web server without internet

---

## 🧾 Example Code: Create a Wi-Fi Hotspot

```cpp
#include <WiFi.h>

const char* ssid = "ESP32-AccessPoint";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  // Start AP mode
  WiFi.softAP(ssid, password);

  // Show info
  Serial.println("Access Point Started!");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Put code here to serve a page or read data from connected clients
}
```

---

## 📲 Connecting to the ESP32 Hotspot

1. Open Wi-Fi settings on your phone/laptop  
2. Look for a network named **ESP32-AccessPoint**  
3. Connect using password: `12345678`  
4. Open a browser and go to **192.168.4.1** (default IP of ESP32 AP)

---

## 🌐 Bonus: Host a Web Page in AP Mode

Here’s how to send a simple HTML page to clients:

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-AP";
const char* password = "esp32pass";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from ESP32 AP Mode</h1>");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
```

Now when devices connect to your ESP32 hotspot and visit `192.168.4.1`, they’ll see:



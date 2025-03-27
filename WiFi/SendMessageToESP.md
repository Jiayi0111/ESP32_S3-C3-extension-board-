## 📲 ESP32 AP Mode with Input Form: Send Text from Phone to Serial Monitor

In this part, you’ll create a web form hosted by your ESP32 in **Access Point (AP) mode**. When you type something on your phone or laptop and hit **Send**, the ESP32 will receive it and print it to the **Serial Console**.

We’ll use this basic HTML form:

```html
<form action="/submit" method="GET">
  <input type="text" name="message" placeholder="Type something">
  <input type="submit" value="Send to ESP32">
</form>
```

ESP32 will handle `/submit?message=YourTextHere` and extract the value.

---

## 🧾 Example Code

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-InputAP";
const char* password = "12345678";

WebServer server(80);

// HTML Page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>Send Message to ESP32</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
    <h2>ESP32 Message Sender</h2>
    <form action="/submit" method="GET">
      <input type="text" name="message" placeholder="Type something" />
      <input type="submit" value="Send to ESP32" />
    </form>
  </body>
</html>
)rawliteral";

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleSubmit() {
  if (server.hasArg("message")) {
    String msg = server.arg("message");
    Serial.print("Received: ");
    Serial.println(msg);
    server.send(200, "text/html", "<h2>Message received!</h2><a href='/'>Go Back</a>");
  } else {
    server.send(400, "text/html", "No message received.");
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);

  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
}
```

1. Upload the code to ESP32  
2. Open Serial Monitor at **115200 baud**  
3. Connect your phone to the Wi-Fi network:  
   - **SSID**: ESP32-InputAP  
   - **Password**: 12345678  
4. Open your browser and go to: **http://192.168.4.1**  
5. Type something into the form and click **Send to ESP32**  
6. Open Serial Monitor – you’ll see:

```
Received: Hello ESP32!
```

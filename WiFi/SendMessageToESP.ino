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

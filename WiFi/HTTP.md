## 🌐 ESP32 HTTP GET Request – Fetching Data from the Internet 

In this tutorial, you’ll learn how to use your **ESP32** to connect to the internet, **send HTTP GET requests**, and **retrieve data from a web server**. This is useful for APIs like weather, cryptocurrency, air quality, news, and many others.

---

### 🧠 What is an HTTP GET Request?

An HTTP GET request is like typing a website URL into your browser and hitting enter. Your ESP32 does the same — it contacts a server, asks for data, and reads the response.

Example:
```
GET https://jsonplaceholder.typicode.com/posts/1
```
This asks the server for the first post’s content in JSON format.

---

### 🔌 Step 1: ESP32 Code to Perform HTTP GET

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  // Optional for JSON parsing

// WiFi credentials
const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";

// Target URL (JSONPlaceholder API is a public mock API)
const String requestURL = "https://jsonplaceholder.typicode.com/posts/1";

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    fetchData();
  } else {
    Serial.println("\nWiFi connection failed.");
  }
}

void loop() {
  // Optional: Repeat fetch every X seconds
}

// Function to fetch data from the server
void fetchData() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected.");
    return;
  }

  HTTPClient http;
  http.begin(requestURL);  // Start request

  int httpCode = http.GET();  // Send GET

  if (httpCode > 0) {
    Serial.printf("HTTP GET code: %d\n", httpCode);

    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();  // Get response
      Serial.println("=== Server Response ===");
      Serial.println(payload);
      Serial.println("=======================");

      // Optional: parse JSON if response is JSON
      DynamicJsonDocument doc(1024);
      DeserializationError err = deserializeJson(doc, payload);
      if (!err) {
        String title = doc["title"];
        Serial.print("Parsed Title: ");
        Serial.println(title);
      } else {
        Serial.println("Failed to parse JSON.");
      }
    }
  } else {
    Serial.printf("GET request failed. Error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();  // End connection
}
```

---

### 📤 Example Output

```
Connecting to WiFi...
WiFi connected!
HTTP GET code: 200
=== Server Response ===
{
  "userId": 1,
  "id": 1,
  "title": "sunt aut facere repellat provident occaecati...",
  "body": "quia et suscipit\nsuscipit..."
}
=======================
Parsed Title: sunt aut facere repellat provident occaecati...
```

---

### ✅ Key Functions Explained

| Function | Purpose |
|----------|---------|
| `WiFi.begin(ssid, password)` | Connect to WiFi |
| `http.begin(url)` | Set up a GET request |
| `http.GET()` | Send the request to the server |
| `http.getString()` | Read the response as a string |
| `deserializeJson()` | Parse JSON into readable data |
| `http.end()` | Clean up connection |

---

### 🧪 Try With Other Public APIs

You can replace the `requestURL` with any of the following:
- 🧭 OpenWeatherMap: `http://api.openweathermap.org/data/2.5/weather?q=London&appid=your_api_key`
- 💸 CoinGecko (crypto): `https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd`
- 📊 JSONPlaceholder (fake data): `https://jsonplaceholder.typicode.com/users/2`
- 🌫 AQICN Air Quality: `https://api.waqi.info/feed/singapore/?token=your_token`

---

### 📚 References

- 🔗 [HTTPClient (ESP32 Arduino Docs)](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html#httpclient)
- 🔗 [ArduinoJson Docs](https://arduinojson.org/v6/doc/)
- 🔗 [Public APIs Directory](https://github.com/public-apis/public-apis)
- 🔗 [JSONPlaceholder API](https://jsonplaceholder.typicode.com/)

---

## 📡 Bonus: ESP32 Weather Fetching via OpenWeatherMap API 
### 🔧 Step 1: Create OpenWeatherMap API Key

1. Go to [https://openweathermap.org/](https://openweathermap.org/)  
2. Sign up for a free account  
3. Navigate to **API keys** in your profile  
4. Copy the key (it will look like `89f24b816539cfebae9e138139346ca1`)



### 🔌 Step 2: Connect ESP32 to WiFi and Fetch Weather

Upload the following code to your ESP32 using the Arduino IDE:

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";

// OpenWeatherMap config
const String API_KEY = "your_api_key";  // Replace with your key
const String CITY = "Singapore";

// Global variables
String lastWeatherCondition = "";
float lastWindSpeed = 0.0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    float temp = getWeatherTempFromAPI();
    if (!isnan(temp)) {
      Serial.print("Current temperature in ");
      Serial.print(CITY);
      Serial.print(": ");
      Serial.print(temp);
      Serial.println(" °C");
    } else {
      Serial.println("Failed to get temperature.");
    }
  } else {
    Serial.println("\nWiFi connection failed.");
  }
}

void loop() {
  // This example only fetches once in setup()
}

// Function to fetch weather from OpenWeatherMap API
float getWeatherTempFromAPI() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Cannot fetch weather data.");
    return NAN;
  }

  HTTPClient http;
  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "&units=metric&appid=" + API_KEY;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    lastWeatherCondition = doc["weather"][0]["main"].as<String>();
    lastWindSpeed = doc["wind"]["speed"].as<float>();
    float temperature = doc["main"]["temp"].as<float>();

    // Serial print for testing
    Serial.println("=== Weather API Data ===");
    Serial.print("Condition: ");
    Serial.println(lastWeatherCondition);
    Serial.print("Wind Speed: ");
    Serial.print(lastWindSpeed);
    Serial.println(" m/s");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.println("========================");

    http.end();
    return temperature;
  }

  Serial.print("HTTP GET failed, code: ");
  Serial.println(httpCode);
  http.end();
  return NAN;
}
```


### 📤 Serial Output Example

After uploading, open **Serial Monitor** (baud 115200), and you'll see:

```
Connecting to WiFi...
WiFi connected!
=== Weather API Data ===
Condition: Clouds
Wind Speed: 2.4 m/s
Temperature: 30.5 °C
========================
Current temperature in Singapore: 30.5 °C
```


### 📌 Notes
- `units=metric` ensures the temperature is returned in Celsius.
- `lastWeatherCondition` and `lastWindSpeed` are stored globally for reuse.
- Use `DynamicJsonDocument doc(1024);` to hold the parsed JSON data.
- Use `deserializeJson()` to parse the server response.



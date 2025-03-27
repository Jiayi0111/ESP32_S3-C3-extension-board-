#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi 配置
const char* ssid = "GoodLuck";        // <-- 修改为你的WiFi名
const char* password = "11111000";      // <-- 修改为你的WiFi密码

// 天气 API 配置
const String API_KEY = "89f24b816539cfebae9e138139346ca1";  // <-- 替换为你自己的API key
const String CITY = "Singapore";

// 全局变量
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
  // 不做循环，只跑一次
}

// 获取天气信息函数
float getWeatherTempFromAPI() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Cannot fetch weather data.");
    return NAN;
  }

  HTTPClient http;
  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "&appid=" + API_KEY;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    lastWeatherCondition = doc["weather"][0]["main"].as<String>();
    lastWindSpeed = doc["wind"]["speed"].as<float>();
    float temperature = doc["main"]["temp"].as<float>() - 273.15; // Kelvin to Celsius

    // UART 打印
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

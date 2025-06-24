#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// === 配置区 ===
const char* ssid = "didididing";
const char* password = "20001028";
const String API_KEY = "89f24b816539cfebae9e138139346ca1";
const String CITY = "Singapore";
const float TEMP_THRESHOLD = 28.0;   // 温度阈值(℃)
const float WIND_THRESHOLD = 5.0;    // 风速阈值(m/s)

// === 引脚定义 ===
#define SERVO_PIN     21    // 舵机信号
#define LED_PIN       22    // 绿色LED
#define SENSOR_PIN    32    // 温度传感器
#define TFT_CS        15    // TFT片选
#define TFT_DC        2     // TFT数据/命令
#define TFT_RST       4     // TFT复位

// === 对象初始化 ===
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
Servo myServo;

// === 全局变量 ===
int currentAngle = 0;
bool systemActive = false;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 5000;
String lastWeatherCondition = "";
float lastWindSpeed = 0.0;

void setup() {
  Serial.begin(115200);
  
  // 初始化硬件
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // 初始化TFT
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  drawMainUI();
  
  // 初始化舵机
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 500, 2400);
  myServo.write(0);
  
  // 初始化传感器
  analogReadResolution(12);
  analogSetPinAttenuation(SENSOR_PIN, ADC_11db);
  
  // 连接WiFi
  connectToWiFi();
}

void loop() {
  // WiFi重连
  if (WiFi.status() != WL_CONNECTED && millis() - lastUpdateTime > 10000) {
    connectToWiFi();
  }

  // 主控制循环
  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();
    
    // 读取数据
    float localTemp = readLMT87Temp();
    float apiTemp = getWeatherTempFromAPI();
    
    // 更新显示
    updateDisplay(localTemp, apiTemp);
    
    // 核心控制逻辑
    bool shouldActivate = (localTemp > TEMP_THRESHOLD && 
                          (!isnan(apiTemp) && apiTemp > TEMP_THRESHOLD)) && 
                         (lastWindSpeed < WIND_THRESHOLD);
    
    if (shouldActivate && !systemActive) {
      activateSystem(true);
    } else if (!shouldActivate && systemActive) {
      activateSystem(false);
    }
  }
}

// === 系统控制函数 ===
void activateSystem(bool activate) {
  systemActive = activate;
  
  if (activate) {
    // 开启系统
    digitalWrite(LED_PIN, HIGH);
    rotateServo(15, 12, 200); // 正向旋转15°×10次
    updateStatusArea("ACTIVE", ILI9341_GREEN);
  } else {
    // 关闭系统
    rotateServo(-15, 12, 200); // 反向旋转复位
    digitalWrite(LED_PIN, LOW);
    updateStatusArea("STANDBY", ILI9341_RED);
  }
}

void rotateServo(int angleStep, int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    currentAngle += angleStep;
    currentAngle = constrain(currentAngle, 0, 180);
    myServo.write(currentAngle);
    delay(delayTime);
  }
}

// === 显示函数 ===
void drawMainUI() {
  tft.setTextSize(2);
  tft.setCursor(20, 10);
  tft.println("Curtain Motor 4002D");
  tft.drawFastHLine(0, 35, 240, ILI9341_WHITE);
  
  tft.setTextSize(1);
  tft.setCursor(10, 45);
  tft.print("Local Temp:");
  tft.setCursor(10, 65);
  tft.print("API Temp:");
  tft.setCursor(10, 85);
  tft.print("Weather:");
  tft.setCursor(10, 105);
  tft.print("Wind Speed:");
  tft.setCursor(10, 125);
  tft.print("Status:");
}

void updateDisplay(float localTemp, float apiTemp) {
  // 温度
  tft.fillRect(100, 45, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 45);
  tft.print(localTemp, 1);
  tft.print(" C");
  
  tft.fillRect(100, 65, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 65);
  tft.print(isnan(apiTemp) ? "--" : String(apiTemp, 1) + " C");
  
  // 天气
  tft.fillRect(100, 85, 140, 15, ILI9341_BLACK);
  tft.setCursor(100, 85);
  tft.print(lastWeatherCondition);
  
  // 风速（严格只显示数值）
  tft.fillRect(100, 105, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 105);
  tft.print(lastWindSpeed, 1);
  tft.print(" m/s");
}

void updateStatusArea(const char* text, uint16_t color) {
  tft.fillRect(100, 125, 100, 15, ILI9341_BLACK);
  tft.setTextColor(color);
  tft.setCursor(100, 125);
  tft.print(text);
  tft.setTextColor(ILI9341_WHITE);
}

// === 传感器和WiFi函数 ===
float readLMT87Temp() {
  int raw = analogRead(SENSOR_PIN);
  float voltage = raw * (3.3 / 4095.0) * 1000.0;
  return (2145.0 - voltage) / 11.0 + 25.0;
}

float getWeatherTempFromAPI() {
  if (WiFi.status() != WL_CONNECTED) return NAN;
  
  HTTPClient http;
  http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "&appid=" + API_KEY);
  
  if (http.GET() == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    
    lastWeatherCondition = doc["weather"][0]["main"].as<String>();
    lastWindSpeed = doc["wind"]["speed"].as<float>();
    return doc["main"]["temp"].as<float>() - 273.15;
  }
  
  http.end();
  return NAN;
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting WiFi...");
  for (int i = 0; i < 10; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi Connected!");
      return;
    }
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Failed!");
}
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// TFT 引脚定义
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

// TFT 对象初始化
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  
  // 初始化 TFT 屏幕
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  drawMainUI();

  // 用模拟值更新屏幕显示
  float dummyLocalTemp = 30.5;
  float dummyApiTemp = 29.8;
  String dummyWeather = "Clouds";
  float dummyWind = 3.2;
  String dummyStatus = "ACTIVE";

  updateDisplay(dummyLocalTemp, dummyApiTemp, dummyWeather, dummyWind);
  updateStatusArea(dummyStatus.c_str(), ILI9341_GREEN);
}

void loop() {
  // 无需循环
}

// 主界面 UI 绘制
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

// 更新显示内容
void updateDisplay(float localTemp, float apiTemp, String weather, float windSpeed) {
  tft.fillRect(100, 45, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 45);
  tft.print(localTemp, 1);
  tft.print(" C");
  
  tft.fillRect(100, 65, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 65);
  tft.print(apiTemp, 1);
  tft.print(" C");
  
  tft.fillRect(100, 85, 140, 15, ILI9341_BLACK);
  tft.setCursor(100, 85);
  tft.print(weather);
  
  tft.fillRect(100, 105, 100, 15, ILI9341_BLACK);
  tft.setCursor(100, 105);
  tft.print(windSpeed, 1);
  tft.print(" m/s");
}

// 状态栏显示
void updateStatusArea(const char* text, uint16_t color) {
  tft.fillRect(100, 125, 100, 15, ILI9341_BLACK);
  tft.setTextColor(color);
  tft.setCursor(100, 125);
  tft.print(text);
  tft.setTextColor(ILI9341_WHITE);
}

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For Kuriosity expanison board
//#define TFT_CS2 15
//#define TFT_CS3 33
//#define TFT_CS4 5
//#define TFT_MISO 19
//#define TFT_MOSI 23
//#define TFT_CLK 18
//#define TFT_RST 27
//#define TFT_DC 4


// For ESP32 DevKit C 
#define TFT_CS2 15
#define TFT_CS3 33 // Touch
#define TFT_CS4 5 // SD
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_CLK 18
#define TFT_RST 4
#define TFT_DC 2

// For ESP32-C3 DevKit C 
//#define TFT_CS2 3
//#define TFT_CS3 18 // Touch
//#define TFT_CS4 19 // SD
//#define TFT_MISO 2
//#define TFT_MOSI 7
//#define TFT_CLK 6
//#define TFT_RST 4
//#define TFT_DC 5


// For ESP32-S3 DevKit C 
// #define TFT_CS2 40
// #define TFT_CS3 41 // Touch
// #define TFT_CS4 42 // SD
// #define TFT_MISO 37
// #define TFT_MOSI 35
// #define TFT_CLK 36
// #define TFT_RST 21
// #define TFT_DC 2



Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS2, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  
  Serial.println(F("Benchmark                Time (microseconds)"));
  delay(10);

  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);

  Serial.println(F("Done!"));

}

unsigned long testText() {
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(1);
  tft.println("Hello World!");
  
  tft.setTextColor(ILI9341_YELLOW); 
  tft.setTextSize(2);
  tft.println("EE4002D Project 211");
  
  tft.setTextColor(ILI9341_RED);    
  tft.setTextSize(3);
  tft.println("LCD ILI9431");
  
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(4);
  tft.println("SPI Test");
  
  return micros() - start;
}

void loop(void) {

}

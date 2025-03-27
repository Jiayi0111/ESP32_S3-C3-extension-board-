// Testing OLED Display and LCD 1602 Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <LiquidCrystal_I2C.h>

// ESP32 DevKitC Configurations
// const int SDAPin = 21;  // SDA Pin
// const int SCLPin = 22; // SCL Pin

// ESP32 C3-DevKitC Configurations
//const int SDAPin = 0;  // SDA Pin
//const int SCLPin = 1; // SCL Pin

// ESP32 S3-DevKitC Configurations
const int SDAPin = 19;  // SDA Pin
const int SCLPin = 20; // SCL Pin

// Defining OLED I2C Address & Specifications & Initialization
#define oled_address 0x3c // OLED I2C Address
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1
Adafruit_SH1106G oled_display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Initialization

// Defining LCD I2C Address & Specifications & Initialization
#define lcd_address 0x27 // LCD I2C Address
#define CHAR_NUM 16 // Number of characters in each line of LCD
#define LINE_NUM 2 // Number of lines in LCD
LiquidCrystal_I2C lcd_display(lcd_address,CHAR_NUM,LINE_NUM); //Initialization


void setup()   {

  Serial.begin(9600);
  Wire.begin(SDAPin, SCLPin);

  // Setting up LCD
  lcd_display.init();
  lcd_display.clear();
  lcd_display.backlight();

  // text display tests on LCD
  lcd_display.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd_display.print("LCD Display");
  
  lcd_display.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd_display.print("at 0x27");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.

  // Adafruit splashscreen
  delay(250); // wait for the OLED to power up
  oled_display.begin(oled_address, true); // Address 0x3C default 
  oled_display.display();
  delay(2000);

  // text display tests on OLED
  oled_display.clearDisplay();
  oled_display.setTextSize(2);
  oled_display.setTextColor(SH110X_WHITE);
  oled_display.setCursor(0, 0);
  oled_display.println("OLED");

  oled_display.setCursor(0, 18);
  oled_display.println("Display1");

  oled_display.setCursor(0, 36);
  oled_display.println("at 0x3C");
  
  oled_display.display();
}


void loop() {

}

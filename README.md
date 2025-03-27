

# Developing ESP32 with Arduino

**Click the 🔧 icon to access the Arduino code.**



## Getting Started with ESP32: Your Ultimate Beginner's Guide

- [Getting Started with ESP32: Your Ultimate Beginner's Guide](Get_started/Get_Started.md)
  - [Setting Up Arduino for ESP32](Get_started/ArduinoEnvironment.md)
  - [Arduino Code Basics](Get_started/ArduinoUnderstanding.md)
  - [Understanding Arduino Syntax](Get_started/ArduinoSyntax.md)
  
  for better understanding [Sturcuture of ArduinoIDE or comapre ARduino IDE with ESP-IDE 还没写，有空就写]()


## GPIO Output

- [Light Up and Blink an LED](GPIO_Output_Arduino/LED_blink.md) [🔧](GPIO_Output_Arduino/led_blink.ino)
- [Running Light Experiment](GPIO_Output_Arduino/LED_RunningLight.md) [🔧](GPIO_Output_Arduino/led_RunningLight.ino)
- [PWM Breathing LED](GPIO_Output_Arduino/LED_PWM.md) [🔧](GPIO_Output_Arduino/led_PWM.ino)



## GPIO Input

- ### Digital Input
- [GPIO Digital Input: Using a Button with ESP32](GPIO_Input_Arduino/button_input.md) [🔧](GPIO_Input_Arduino/button_input.ino)
- [Button Debouncing](GPIO_Input_Arduino/Button_Debouncing.md) [🔧](GPIO_Input_Arduino/button_debouncing.ino)

- ### Analog Input
- [ESP32 Analog Input with LMT87 Temperature Sensor](GPIO_Input_Arduino/analog_input.md) [🔧](GPIO_Input_Arduino/analog_input.ino)



## Interrupt Handling
- *(Content not available yet)*



## I2C
- *(Content not available yet)*


## SPI
- *(Content not available yet)*

## Bluetooth Connection
- *(Content not available yet)* [🔧]()

## WiFi Connection

- [ESP32 Wi-Fi Basics](WiFi/ConnectWiFi.md) [🔧](WiFi/ConnectWifi.ino)
- [ESP32 Access Point (AP) Mode](WiFi/APmode.md) [🔧](WiFi/APmode.md) [🔧](WiFi/WebPage_withAPmode.ino)
- [Send Text from Phone to ESP32](WiFi/SendMessageToESP.md) [🔧](WiFi/SendMessageToESP.ino)


## 所有exmample需要加一下解释和datasheet
## Sensor Examples

- [Temperature and Humidity Sensor DHT22 🔧](Sensors/TemperatureHumidityDHT22.ino)
- [Temperature Sensor LMT87 🔧](Sensors/TemperatureLMT87.ino)
- [Ultrasonic Ranging Module HC-SR04 🔧](Sensors/UltrasonicRangingModuleHC-SR04.ino)
- [Infrared Transistor SFH4855 （暂时没有.ino） 🔧]()
- *(Additional sensor examples coming soon)*


## Display Examples

- [LCD ILI9341 Resistive Touch Display 🔧](Diaplay\TFT_display_Test.ino)
- [LCD1602 Display 🔧](Diaplay\LCD1602_Test.ino)
- [SH1106 OLED Display 🔧](Diaplay\oled_lcd_test.ino)
- [LCD ILI9341 display 🔧](Diaplay\lcd_ili9431_test.ino)

## Other comonents' example
- [Diaplay pics in SD card 🔧](SDcard\ESP32_SDcard_jpeg.ino)
- [SG90 Micro Servo Motor (下周做)]() 
- [Buzzer Module(下周做)]() 
- [MOT-BRU-012 DC Motor (等JX回来)]()
- [Relay Modules (MOD-REL-004 and MOD-REL-012)(等JX回来)]()
- [L298N Dual H-Bridge Motor Driver (等JX回来)]()

## Demo Projects

- *(Content not available yet)*
- *(Content not available yet)*

---

## GO Advanced with ESP-IDF and FreeRTOS

### Setting Up Development Environment
- [Go to part 1.0 - Setting Up Development Environment](Setting-up-Development-Enviroment/Setting-Up-Development-Environment.md)
  - [part 1.0.1 Installing Multiple Versions of ESP‐IDF](Setting-up-Development-Enviroment/InstallingMultipleVersionsofESP‐IDF.md)

### Hello World (Write, Compile & Flash)
- [Go to part 1.1 - Hello_world](Setting-up-Development-Enviroment/Hello_world.md)
  - [part 1.1.1 Understanding Basic Project Structure](Setting-up-Development-Enviroment/BasicProjectStructure.md)
  - [part 1.1.2 Using Flash Download Tool to Flash ESP32 Firmware](Setting-up-Development-Enviroment/UsingFlashDownloadTooltoFlash.md)

### GPIO with ESP-IDF
- [Go to part 2.1 - GPIO](GPIO_ESP_IDE/GPIO_key_input.md)
  - [part 2.1.0 ESP32 Blink Example](GPIO_ESP_IDE/blink_3led.md)
  - [part 2.1.1 ESP32 GPIO_example Breakdown](GPIO_ESP_IDE/ESP32_GPIO_example.md)


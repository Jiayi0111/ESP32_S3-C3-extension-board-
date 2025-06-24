# Developing ESP32 with Arduino

**Click the 🔧 icon to access the Arduino code.**



## Getting Started with ESP32

- [Getting Started with ESP32: Your Ultimate Beginner's Guide](Get_started/Get_Started.md)

## Our Super Convenient Hardware
- [Introduction to Expansion Board](Hardware/ee4002d-guide-main/Hardware.md)

## Getting Started with Arduino
  - [Setting Up Arduino for ESP32](Get_started/ArduinoEnvironment.md)
  - [Arduino Code Basics](Get_started/ArduinoUnderstanding.md)
  - [Understanding Arduino Syntax](Get_started/ArduinoSyntax.md)

  for better understanding [Structure of Arduino IDE or compare Arduino IDE with ESP-IDE (coming soon)]()

## GPIO Output

- [Light Up and Blink an LED](GPIO_Output_Arduino/LED_blink.md) [🔧](GPIO_Output_Arduino/led_blink.ino)
- [Running Light Experiment](GPIO_Output_Arduino/LED_RunningLight.md) [🔧](GPIO_Output_Arduino/led_RunningLight.ino)
- [PWM Breathing LED](GPIO_Output_Arduino/LED_PWM.md) [🔧](GPIO_Output_Arduino/led_PWM.ino)

## GPIO Input

### Digital Input
- [GPIO Digital Input: Using a Button with ESP32](GPIO_Input_Arduino/button_input.md) [🔧](GPIO_Input_Arduino/button_input.ino)
- [Button Debouncing](GPIO_Input_Arduino/Button_Debouncing.md) [🔧](GPIO_Input_Arduino/button_debouncing.ino)

### Analog Input
- [ESP32 Analog Input with LMT87 Temperature Sensor](GPIO_Input_Arduino/analog_input.md) [🔧](GPIO_Input_Arduino/analog_input.ino)

## Interrupt Handling

- [Interrupt Handling: How to Use External Interrupts](InterruptHandling/interrupthandling.md) [🔧](InterruptHandling/interrupthandling.ino)

## I2C
- [ESP32 I2C Display Tutorial – Using OLED and LCD 1602 with I2C](I2C/I2C.md)
[🔧](Diaplay/LCD1602_Test.ino)[🔧](Diaplay/lcd_ili9431_test.ino)

## SPI
- [ESP32 SPI Display Tutorial – Using ILI9341 with SPI](SPI/SPI.md) [🔧](Diaplay/TFT_display_Test.ino)

## Bluetooth Connection
- [ESP32 Bluetooth Tutorial – Classic SPP vs BLE](Bluetooth/Bluetooth.md) [🔧](Bluetooth/bluetooth.ino)

## WiFi Connection

- [ESP32 Wi-Fi Basics](WiFi/ConnectWiFi.md) [🔧](WiFi/ConnectWifi.ino)
- [ESP32 Access Point (AP) Mode](WiFi/APmode.md) [🔧](WiFi/APmode.md) [🔧](WiFi/WebPage_withAPmode.ino)
- [Send Text from Phone to ESP32](WiFi/SendMessageToESP.md) [🔧](WiFi/SendMessageToESP.ino)

## Sensor Examples

### Custom 1-Wire
- [Temperature and Humidity Sensor DHT22 🔧](Sensors/TemperatureHumidityDHT22.ino)

### Analog (ADC)
- [Temperature Sensor LMT87 🔧](Sensors/TemperatureLMT87.ino)
- [Infrared Transistor SFH4855🔧]()

### GPIO (Trigger & Echo)
- [Ultrasonic Ranging Module HC-SR04 🔧](Sensors/UltrasonicRangingModuleHC-SR04.ino)

### I2S
- [INMP441 Omnidirectional Microphone](OtherExamples/bluetoothspeaker.ino)
- *(Additional sensor examples coming soon)*

## Display Examples

- [LCD ILI9341 Resistive Touch Display 🔧](Diaplay/TFT_display_Test.ino)
- [LCD1602 Display 🔧](Diaplay/LCD1602_Test.ino)
- [SH1106 OLED Display 🔧](Diaplay/oled_lcd_test.ino)
- [LCD ILI9341 display 🔧](Diaplay/lcd_ili9431_test.ino)

## Other components' example
- [Display pics in SD card 🔧](SDcard/ESP32_SDcard_jpeg.ino)
- [SG90 Micro Servo Motor (coming soon)]()
- [Buzzer Module (coming soon)]()
- [MOT-BRU-012 DC Motor (coming soon)]()
- [Relay Modules (MOD-REL-004 and MOD-REL-012) (coming soon)]()
- [L298N Dual H-Bridge Motor Driver (coming soon)]()
- [Hat SPK2 speaker](OtherExamples/speaker.ino)

## Demo Projects

- [Smart Bluetooth Speaker](Demo/BluetoothSpeaker.md)[🔧](Demo/bluetoothspeaker.ino)
- [Bluetooth Speaker with Microphone for ChatGPT Web Voice Interaction (Enhanced Version)](Demo/HomeMadeXIaozhi.md) [🔧](Demo/HomeMadeXiaozhi.ino)
- [Smart Curtain Control System](Demo/SmartCurtainControlSystem.md)
- *(More Demo projects coming soon)*

---

## GO Advanced with ESP-IDF and FreeRTOS

### Setting Up Development Environment
- [Go to part 1.0 - Setting Up Development Environment](Setting-up-Development-Enviroment/Setting-Up-Development-Environment.md)
  - [part 1.0.1 Installing Multiple Versions of ESP‐IDF](Setting-up-Development-Enviroment/InstallingMultipleVersionsofESP‐IDF.md)

### Hello World (Write, Compile & Flash)
- [Go to part 1.1 - Hello_world](Setting-up-Development-Enviroment/Hello_world.md)[🔧](Setting-up-Development-Enviroment/Hello_world_example)
  - [part 1.1.1 Understanding Basic Project Structure](Setting-up-Development-Enviroment/BasicProjectStructure.md)
  - [part 1.1.2 Using Flash Download Tool to Flash ESP32 Firmware](Setting-up-Development-Enviroment/UsingFlashDownloadTooltoFlash.md)

### GPIO with ESP-IDF
- [Go to part 2.1 - GPIO](GPIO_ESP_IDE/GPIO_key_input.md)
  - [part 2.1.0 ESP32 Blink Example](GPIO_ESP_IDE/blink_3led.md)[🔧](GPIO_ESP_IDE/blink)
  - [part 2.1.1 ESP32 GPIO_example Breakdown](GPIO_ESP_IDE/ESP32_GPIO_example.md) [🔧](GPIO_ESP_IDE/generic_gpio)

### Voice Wake‑Up with ESP‑SKAINet
- [How to Implement Voice Wake‑Up with ESP‑SKAINet](WakeUp/VoiceWakeUp.md)[🔧](WakeUp/esp-skainet-master)

## Demo Projects
- [Intelligent, Voice-interactive XiaoZhi](Demo/Xiaozhi.md)[🔧](Demo/xiaozhi-esp32)
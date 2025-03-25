### Welcome to Arduino Coding for ESP32 !

It's fantastic to have you here! You've got your ESP32 extension board ready, setting the stage for exciting creativity. Let's dive into Arduino programming and start building awesome ESP32 projects.

### Arduino Code Basics

Arduino coding for the ESP32 is intuitive and enjoyable. Every Arduino program includes two primary functions:

1. **setup()**: Executes once when your ESP32 starts.
2. **loop()**: Continuously runs after `setup()` finishes.

Here's a straightforward Arduino sketch for your ESP32:

```cpp
void setup() {
  Serial.begin(115200); // Start serial communication
  pinMode(2, OUTPUT);   // Set pin 2 as an output pin
}

void loop() {
  digitalWrite(2, HIGH); // Turn LED on
  delay(500);            // Wait half a second
  digitalWrite(2, LOW);  // Turn LED off
  delay(500);            // Wait half a second
}
```

### Understanding Common Functions

- **Serial.begin(115200);**: Initializes serial communication at a baud rate of 115200 for debugging and data monitoring.
- **pinMode(pin, mode);**: Defines pin mode as INPUT, OUTPUT, or INPUT\_PULLUP.
- **digitalWrite(pin, HIGH/LOW);**: Sets digital pins to HIGH or LOW (turns them on or off).
- **delay(milliseconds);**: Pauses the execution of code for the specified duration.

### Leveraging Your ESP32 Extension Board

Your custom-designed extension board makes connecting sensors and actuators straightforward and mess-free:

- Just plug sensors directly into the labeled connectors.
- Refer to the provided pin mapping documentation for quick guidance.

Here's how you can blink an onboard LED connected to pin `2`:

```cpp
void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);  // LED on
  delay(1000);            // Wait 1 second
  digitalWrite(2, LOW);   // LED off
  delay(1000);            // Wait 1 second
}
```

### Uploading Your Code

- Connect your ESP32 to your computer via USB.
- Select your ESP32 model (`ESP32 DEV Module`, `ESP32-S3`, or `ESP32-C3`) in the Arduino IDE board manager.
- Hit **Upload** (→) to flash your ESP32 with your code!

### What's Next?

You're now set with the basics! Move on to exciting tasks like sensor readings, motor control, or IoT connectivity using Wi-Fi. The opportunities with your ESP32 extension board are endless.

Happy coding! Enjoy exploring and bringing your ideas to life!


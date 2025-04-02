## ⚡ ESP32 Interrupt Handling – How to Use External Interrupts 

In this tutorial, you'll learn how to use **interrupts** with ESP32 in Arduino IDE to handle external events like **button presses**, **sensor signals**, or **pulse inputs** — **without constantly checking them in `loop()`**.

---

### 🧠 Principle: What is an Interrupt?

In a microcontroller, an **interrupt** is like someone tapping your shoulder while you're doing something important — asking you to quickly deal with a more urgent task.

Let’s imagine this:

> You’re washing clothes (main program), when suddenly your phone rings (an interrupt). You pause the washing, answer the phone (interrupt service), then return and continue washing (return from interrupt).  
>  
> If another more important call comes in while you’re still on the first call, you put the first call on hold to answer the new one. This is **nested interrupts**, and it relies on **interrupt priorities**.

### 📌 Key Concepts:
- **Interrupt**: A signal that tells the CPU to pause what it's doing and run a new function.
- **Interrupt Response**: The CPU stops its current task and jumps to the interrupt service routine (ISR).
- **Interrupt Return**: After the ISR is done, the CPU resumes the main program.
- **Nested Interrupts**: When a higher-priority interrupt interrupts a lower-priority one.
- **Hardware Interrupts**: Triggered by external hardware (e.g. GPIO, touch sensor)
- **Software Interrupts**: Triggered by internal events (e.g. timer overflow)

> In polling (no interrupts), your program constantly checks for changes, wasting CPU time. With interrupts, the CPU does other work and only reacts when the event occurs — more efficient, especially for rare or delayed inputs.

For example:  
In a button-controlled project, using interrupts means your ESP32 only responds **when the button is pressed**, rather than checking the button state every cycle.

> ⚠️ ESP32 supports **RISING**, **FALLING**, **CHANGE**, **HIGH**, and **LOW** level trigger modes for GPIO interrupts.


Awesome! Let’s move on to **interrupt handling** — a super useful and powerful concept when working with microcontrollers like the ESP32.

Here’s the next part of your tutorial series:

---


### 📌 Example: Button Triggered LED with Interrupt

Let’s create an example where:
- A button is connected to a GPIO pin
- Pressing the button toggles an LED
- We use an **interrupt** instead of checking the button in `loop()`

---

### 🔧 Circuit Setup

| Component | GPIO |
|----------|------|
| Button   | GPIO 14 |
| LED      | GPIO 27 |

- One side of the button goes to **GPIO 14**
- The other side goes to **GND**
- Add a **10k pull-up resistor** (or use internal pull-up)

---

### 📟 Arduino Code Example

```cpp
const int buttonPin = 14;
const int ledPin = 27;

volatile bool ledState = false;

void IRAM_ATTR handleInterrupt() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // use internal pull-up

  // Attach interrupt to pin 14, trigger on falling edge (button press)
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, FALLING);

  Serial.println("Interrupt demo started");
}

void loop() {
  // nothing to do here — everything is interrupt-driven!
}
```

---

### 📋 Explanation

| Part | Meaning |
|------|---------|
| `attachInterrupt()` | Links a GPIO pin to an ISR (interrupt service routine) |
| `digitalPinToInterrupt(pin)` | Converts a GPIO pin to its interrupt ID |
| `handleInterrupt()` | This function runs automatically when the pin changes |
| `IRAM_ATTR` | Required on ESP32 to place the ISR in RAM (for speed) |
| `FALLING` | Trigger the interrupt on falling edge (high → low) |

---

### 🧠 Interrupt Modes

| Mode | Triggered When |
|------|----------------|
| `RISING` | LOW → HIGH |
| `FALLING` | HIGH → LOW |
| `CHANGE` | Any change (HIGH ↔ LOW) |
| `HIGH` | Stays HIGH (less common) |
| `LOW` | Stays LOW (less common) |

---

### ⚠️ Tips & Warnings

- Keep ISR functions **short and fast** – avoid delays or `Serial.print()` inside!
- Use `volatile` for variables shared with interrupts
- Never use `delay()` inside an ISR
- Avoid accessing I2C/SPI or display inside interrupts

---

### 📚 Bonus: Detach an Interrupt

```cpp
detachInterrupt(digitalPinToInterrupt(buttonPin));
```

This stops the interrupt from firing (useful for power saving or mode switching).

---

### 🧪 Use Cases of Interrupts

- Button presses
- Motion sensors
- Rotary encoders
- IR receivers
- Tachometers / speed sensors
- Real-time control (e.g. stop motor immediately)

---

### 📚 References

- 🔗 [ESP32 attachInterrupt Reference](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/general.html#gpio)
- 🔗 [Arduino Interrupts Tutorial](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

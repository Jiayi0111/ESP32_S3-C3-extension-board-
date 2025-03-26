/*
software deboucing 


> "Only accept a button press if the signal stays the same for a short amount of time (e.g., 50 milliseconds)."

### 🧩 Step-by-Step Logic:

1. 🔍 **Read the button's current state** using `digitalRead()`.

2. 🧠 **Compare it to the previous reading** (`lastButtonState`):
   - If it's different, it might be a real press — **or just a bounce**.
   - So we **reset a timer** (`lastDebounceTime`) to note *when* the change was first seen.

3. ⏱ **Wait a short time** (e.g. 50 ms) to see if the new state stays the same.

4. ✅ If the state is still the same after the delay, **accept it as a real change**.

5. 🚀 Finally, if the new (debounced) state is `LOW` (button pressed), **perform the action**, like printing to serial or toggling an LED.
*/

const int buttonPin = 14;   // GPIO connected to button
const int ledPin = 2;       // LED pin (built-in or external)

int buttonState = HIGH;             // Current debounced state
int lastButtonState = HIGH;         // Last raw state
unsigned long lastDebounceTime = 0; // Timestamp of last change
const unsigned long debounceDelay = 50; // Delay in ms

bool ledOn = false; // LED state

void setup() {
  Serial.begin(115200);               // Start Serial Monitor
  pinMode(buttonPin, INPUT_PULLUP);   // Internal pull-up: HIGH when not pressed
  pinMode(ledPin, OUTPUT);            // LED output
}

void loop() {
  int reading = digitalRead(buttonPin); // Raw state

  // If state changed, reset timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // If stable for debounceDelay, accept new state
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Only toggle on button press (LOW = pressed due to pull-up)
      if (buttonState == LOW) {
        ledOn = !ledOn;
        digitalWrite(ledPin, ledOn ? HIGH : LOW);
        Serial.println(ledOn ? "LED ON" : "LED OFF");
      }
    }
  }

  lastButtonState = reading; // Save reading for next loop
}

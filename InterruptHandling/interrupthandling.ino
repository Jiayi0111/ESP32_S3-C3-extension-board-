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

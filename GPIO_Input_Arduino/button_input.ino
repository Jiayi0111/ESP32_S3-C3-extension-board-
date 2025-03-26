// SW pressed --> led off
// SW not pressed --> led on 


int buttonPin = 14;  // GPIO connected to the button
int ledPin = 2;      // Built-in LED (change if using external)

void setup() {
  Serial.begin(115200);              // UART Serial output
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor
    // pinMode(buttonPin, INPUT_PULLDOWN);     // Use internal pull-down resistor //uncomment to see what happens 
  pinMode(ledPin, OUTPUT);           // LED output
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Read button

  // Note: LOW = Pressed, because of pull-up logic
  Serial.print("Button is ");
  Serial.println(buttonState == LOW ? "PRESSED" : "RELEASED");

  // Turn on LED when button is pressed
  digitalWrite(ledPin, buttonState == LOW ? HIGH : LOW);

  delay(100);  // Avoid spamming output
}
